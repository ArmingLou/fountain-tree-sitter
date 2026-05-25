#include "tree_sitter/parser.h"
#include <string.h>
#include <wctype.h>
#include <stdlib.h>

enum TokenType {
  SCENE_START,
  SECTION_START,
  NOTE_START,
  FORCED_ACTION_START,
  FORCED_CHARACTER_START,
  FORCED_TRANSITION_START,
  LYRIC_START,
  CENTERED_START,
  PAGE_BREAK_MARKER,
  SYNOPSIS_START,
  BONEYARD_START,
  TITLE_CONTINUATION,
  BLANK_LINE,
  DIALOGUE_LINE_START,
  PARENTHETICAL_LINE,
};

typedef struct {
  bool in_title_page;
  bool blank_seen_in_dialogue;
  bool continuation_active;
} Scanner;

void *tree_sitter_fountain_external_scanner_create() {
  Scanner *scanner = (Scanner *)malloc(sizeof(Scanner));
  scanner->in_title_page = true;
  scanner->blank_seen_in_dialogue = false;
  scanner->continuation_active = false;
  return scanner;
}

static bool match_keyword(TSLexer *lexer, const char *keyword) {
  for (size_t i = 0; keyword[i] != '\0'; i++) {
    if (lexer->lookahead != keyword[i]) return false;
    lexer->advance(lexer, false);
  }
  return true;
}

bool tree_sitter_fountain_external_scanner_scan(void *payload, TSLexer *lexer, const bool *valid_symbols) {
  Scanner *scanner = (Scanner *)payload;

  // 如果不是在对话/插入语上下文中，重置空白行标志
  if (!valid_symbols[DIALOGUE_LINE_START] && !valid_symbols[PARENTHETICAL_LINE]) {
    scanner->blank_seen_in_dialogue = false;
    scanner->continuation_active = false;
  }

  // Try title continuation (indented line: 3+ spaces or tab at start of line)
  if (valid_symbols[TITLE_CONTINUATION] && scanner->in_title_page) {
    // Count leading whitespace
    int space_count = 0;
    bool has_tab = false;

    while (lexer->lookahead == ' ' || lexer->lookahead == '\t') {
      if (lexer->lookahead == '\t') {
        has_tab = true;
        lexer->advance(lexer, false);
        break;
      }
      space_count++;
      lexer->advance(lexer, false);
    }

    // Must have 3+ spaces or a tab, and not be an empty line
    if ((space_count >= 3 || has_tab) &&
        lexer->lookahead != '\n' &&
        lexer->lookahead != '\0') {

      // Consume the rest of the line (but NOT the newline - grammar handles that)
      while (lexer->lookahead != '\n' && lexer->lookahead != '\0') {
        lexer->advance(lexer, false);
      }

      lexer->result_symbol = TITLE_CONTINUATION;
      lexer->mark_end(lexer);
      return true;
    }
  }

  // Try section start (# markers) - this ends title page
  if (valid_symbols[SECTION_START] && lexer->lookahead == '#') {
    scanner->in_title_page = false;
    while (lexer->lookahead == '#') {
      lexer->advance(lexer, false);
    }
    lexer->result_symbol = SECTION_START;
    lexer->mark_end(lexer);
    return true;
  }

  // Try scene start (INT., EXT., etc. or forced scene heading with .) - this ends title page
  if (valid_symbols[SCENE_START]) {
    // Check for forced scene heading (. followed by alphanumeric or Chinese patterns)
    if (lexer->lookahead == '.') {
      lexer->advance(lexer, false);

      // 检查中文特例：.(外景)、.(内景)、.(内外景)
      if (lexer->lookahead == '(') {
        lexer->advance(lexer, false);  // 消费 '('

        if (lexer->lookahead == 0x5185) {  // '内'
          lexer->advance(lexer, false);
          if (lexer->lookahead == 0x5916) {  // '外' → 内外景
            lexer->advance(lexer, false);
            if (lexer->lookahead == 0x666F) {  // '景'
              lexer->advance(lexer, false);
              if (lexer->lookahead == ')') {
                lexer->advance(lexer, false);
                scanner->in_title_page = false;
                lexer->result_symbol = SCENE_START;
                lexer->mark_end(lexer);
                return true;
              }
            }
          } else if (lexer->lookahead == 0x666F) {  // '景' → 内景
            lexer->advance(lexer, false);
            if (lexer->lookahead == ')') {
              lexer->advance(lexer, false);
              scanner->in_title_page = false;
              lexer->result_symbol = SCENE_START;
              lexer->mark_end(lexer);
              return true;
            }
          }
        } else if (lexer->lookahead == 0x5916) {  // '外'
          lexer->advance(lexer, false);
          if (lexer->lookahead == 0x666F) {  // '景' → 外景
            lexer->advance(lexer, false);
            if (lexer->lookahead == ')') {
              lexer->advance(lexer, false);
              scanner->in_title_page = false;
              lexer->result_symbol = SCENE_START;
              lexer->mark_end(lexer);
              return true;
            }
          }
        }
        // 非中文场景头，无法匹配
        return false;
      }

      // Must be followed by an alphanumeric character to be a forced scene heading
      if (iswalnum(lexer->lookahead)) {
        scanner->in_title_page = false;
        lexer->result_symbol = SCENE_START;
        lexer->mark_end(lexer);
        return true;
      }
      // Not a forced scene heading, cannot backtrack
      return false;
    }

    // Check for standard scene headings
    if (match_keyword(lexer, "INT.") ||
        match_keyword(lexer, "EXT.") ||
        match_keyword(lexer, "INT./EXT.") ||
        match_keyword(lexer, "EST.")) {
      scanner->in_title_page = false;
      lexer->result_symbol = SCENE_START;
      lexer->mark_end(lexer);
      return true;
    }
  }

  // Try note start ([[)
  if (valid_symbols[NOTE_START] && match_keyword(lexer, "[[")) {
    // 对话块内遇到空行后，不应该再匹配备注（让其在外层匹配）
    if (scanner->blank_seen_in_dialogue) return false;
    lexer->result_symbol = NOTE_START;
    lexer->mark_end(lexer);
    return true;
  }

  // Try forced action (!)
  if (valid_symbols[FORCED_ACTION_START] && lexer->lookahead == '!') {
    lexer->advance(lexer, false);
    lexer->result_symbol = FORCED_ACTION_START;
    lexer->mark_end(lexer);
    return true;
  }

  // Try forced character (@)
  if (valid_symbols[FORCED_CHARACTER_START] && lexer->lookahead == '@') {
    // 延续模式下，@ 不作为新角色，让其作为对话内容
    if (scanner->continuation_active) return false;
    // 新角色开始，重置对话上下文标志
    scanner->blank_seen_in_dialogue = false;
    scanner->continuation_active = false;
    lexer->advance(lexer, false);
    lexer->result_symbol = FORCED_CHARACTER_START;
    lexer->mark_end(lexer);
    return true;
  }

  // Try forced transition or centered (>)
  if ((valid_symbols[FORCED_TRANSITION_START] || valid_symbols[CENTERED_START]) && lexer->lookahead == '>') {
    lexer->advance(lexer, false);
    // Mark the end right after the '>' symbol
    lexer->mark_end(lexer);

    // Look ahead to see if there's a closing '<' on this line
    // to distinguish between centered text (>text<) and forced transition (>text)
    bool has_closing_bracket = false;

    // Scan the rest of the line looking for '<' (don't modify mark_end)
    while (lexer->lookahead != '\n' && lexer->lookahead != '\0') {
      if (lexer->lookahead == '<') {
        has_closing_bracket = true;
        break;
      }
      lexer->advance(lexer, false);
    }

    // If we found a closing bracket, it's centered text
    if (has_closing_bracket && valid_symbols[CENTERED_START]) {
      lexer->result_symbol = CENTERED_START;
      return true;
    }
    // Otherwise, if no closing bracket, it's a forced transition
    else if (!has_closing_bracket && valid_symbols[FORCED_TRANSITION_START]) {
      lexer->result_symbol = FORCED_TRANSITION_START;
      return true;
    }
  }

  // Try lyric (~)
  if (valid_symbols[LYRIC_START] && lexer->lookahead == '~') {
    lexer->advance(lexer, false);
    lexer->result_symbol = LYRIC_START;
    lexer->mark_end(lexer);
    return true;
  }

  // Try synopsis (=)
  if (valid_symbols[SYNOPSIS_START] && lexer->lookahead == '=') {
    // Check if it's a page break (===)
    int equals_count = 0;
    while (lexer->lookahead == '=') {
      equals_count++;
      lexer->advance(lexer, false);
    }

    if (equals_count >= 3 && (lexer->lookahead == '\n' || lexer->lookahead == '\0')) {
      if (valid_symbols[PAGE_BREAK_MARKER]) {
        lexer->result_symbol = PAGE_BREAK_MARKER;
        lexer->mark_end(lexer);
        return true;
      }
    } else if (equals_count == 1) {
      lexer->result_symbol = SYNOPSIS_START;
      lexer->mark_end(lexer);
      return true;
    }
  }

  // Try boneyard (/*)
  if (valid_symbols[BONEYARD_START] && match_keyword(lexer, "/*")) {
    // 对话块内遇到空行后，不应该再匹配注释（让其在外层匹配）
    if (scanner->blank_seen_in_dialogue) return false;
    lexer->result_symbol = BONEYARD_START;
    lexer->mark_end(lexer);
    return true;
  }

  // Try parenthetical_line - matches standalone (text) or （中文括号） lines within dialogue blocks
  // 如果空白行标志已设置，拒绝匹配以终止对话块
  if (valid_symbols[PARENTHETICAL_LINE]) {
    if (scanner->blank_seen_in_dialogue) {
      return false;
    }
    // Count leading whitespace
    while (lexer->lookahead == ' ' || lexer->lookahead == '\t') {
      lexer->advance(lexer, false);
    }

    int32_t open_paren = 0;
    int32_t close_paren = 0;

    // 检查英文 () 或中文 （）
    if (lexer->lookahead == '(') {
      open_paren = '(';
      close_paren = ')';
    } else if (lexer->lookahead == 0xFF08) {  // U+FF08
      open_paren = 0xFF08;
      close_paren = 0xFF09;  // U+FF09
    }

    if (open_paren != 0) {
      lexer->advance(lexer, false);  // consume open paren

      // Scan to find closing paren
      while (lexer->lookahead != close_paren && lexer->lookahead != '\n' && lexer->lookahead != '\0') {
        lexer->advance(lexer, false);
      }

      if (lexer->lookahead == close_paren) {
        lexer->advance(lexer, false);  // consume close paren

        // Skip trailing whitespace
        while (lexer->lookahead == ' ' || lexer->lookahead == '\t') {
          lexer->advance(lexer, false);
        }

        // Must be at end of line (pure parenthetical)
        if (lexer->lookahead == '\n' || lexer->lookahead == '\0') {
          lexer->result_symbol = PARENTHETICAL_LINE;
          lexer->mark_end(lexer);
          return true;
        }
      }
    }
    // 不是有效的插入语行，fall through 继续检查其他令牌类型
  }

  // Try dialogue_line_start - matches if we're at the start of a non-blank line
  if (valid_symbols[DIALOGUE_LINE_START]) {
    // 计算行首缩进空格数
    int indent = 0;
    while (lexer->lookahead == ' ' || lexer->lookahead == '\t') {
      indent++;
      lexer->advance(lexer, false);
    }

    // 如果到行尾，判断是否为延续标记（2+空格）还是空行（0-1空格）
    if (lexer->lookahead == '\n' || lexer->lookahead == '\0') {
      if (indent >= 2) {
        // 2+空格后跟换行 = 对话延续标记，不消费换行（由语法规则处理）
        // 设置延续标志，使下一行的特殊字符被忽略
        scanner->continuation_active = true;
        scanner->blank_seen_in_dialogue = false;
        lexer->result_symbol = DIALOGUE_LINE_START;
        lexer->mark_end(lexer);
        return true;
      }
      // 0-1空格空行，设置标志以终止后续对话行匹配
      scanner->blank_seen_in_dialogue = true;
      scanner->continuation_active = false;
      return false;
    }

    // 非空行开始，重置空白行标志（新的对话上下文）
    scanner->blank_seen_in_dialogue = false;

    // 非缩进行（少于2个空格）：检查特殊字符和角色名
    // 缩进行（2+空格）或延续激活：直接作为对话延续，跳过所有特殊字符检查
    if (indent < 2 && !scanner->continuation_active) {
      // 检查是否是Fountain特殊标记：场景、章节、强制角色、梗概、歌词、转场/居中、强制动作
      // 对话行不应以这些字符开头（备注[[和注释/*由语法层面的更高优先级来处理）
      if (lexer->lookahead == '.' || lexer->lookahead == '#' || lexer->lookahead == '@' ||
          lexer->lookahead == '=' || lexer->lookahead == '~' || lexer->lookahead == '>' ||
          lexer->lookahead == '!') {
        return false;
      }

      // 检查是否是独立括号行：排除纯插入语 `(text)` 或中文 `（text）` 开头且行尾无其他内容的行
      // 纯粹的插入语应由 parenthetical_line 规则匹配
      // 括号后有其他文字的行（如 `(停顿) 继续说话`）仍作为对话行处理
      {
        int32_t open_paren = 0;
        int32_t close_paren = 0;
        if (lexer->lookahead == '(') {
          open_paren = '(';
          close_paren = ')';
    } else if (lexer->lookahead == 0xFF08) {  // fullwidth left parenthesis U+FF08
      open_paren = 0xFF08;
      close_paren = 0xFF09;  // fullwidth right parenthesis U+FF09
        }
        if (open_paren != 0) {
          lexer->advance(lexer, false);  // 跳过开括号

          // 扫描寻找匹配的闭括号
          while (lexer->lookahead != close_paren && lexer->lookahead != '\n' && lexer->lookahead != '\0') {
            lexer->advance(lexer, false);
          }

          if (lexer->lookahead == close_paren) {
            lexer->advance(lexer, false);  // 跳过闭括号

            // 跳过尾部空格
            while (lexer->lookahead == ' ' || lexer->lookahead == '\t') {
              lexer->advance(lexer, false);
            }

            // 如果到行尾（\n 或 \0），这是纯插入语，拒绝以让语法层匹配 parenthetical
            if (lexer->lookahead == '\n' || lexer->lookahead == '\0') {
              return false;
            }
          }
          // 不是纯插入语：括号后有其他内容 或 没有找到闭合括号
          // 此时 lexer 已前进了若干字符，继续 fall through 消费剩余行
        }
      }

      // Check if this line looks like a character name (all uppercase with valid chars)
      // Character pattern: [A-Z][A-Z0-9 ()\\.']*[A-Z0-9)\\.]
      // Reject so parent grammar can handle it as a new character starting a dialogue_block
      {
        int32_t first = lexer->lookahead;
        if (first >= 'A' && first <= 'Z') {
          // Scan the rest of the line to check character name pattern
          // Must contain only character-valid chars and end with character-valid ending
          bool all_valid_chars = true;
          int32_t last_char = first;
          int32_t ch;

          // We need to peek ahead without permanently consuming
          // Tree-sitter will rollback lexer position if we return false
          lexer->advance(lexer, false);

          while ((ch = lexer->lookahead) != '\n' && ch != '\0') {
            last_char = ch;
            if (!((ch >= 'A' && ch <= 'Z') ||
                  (ch >= '0' && ch <= '9') ||
                  ch == ' ' || ch == '(' || ch == ')' ||
                  ch == '.' || ch == '\'')) {
              all_valid_chars = false;
              break;
            }
            lexer->advance(lexer, false);
          }

          // Must end with uppercase letter, digit, ) or .
          if (all_valid_chars &&
              ((last_char >= 'A' && last_char <= 'Z') ||
               (last_char >= '0' && last_char <= '9') ||
               last_char == ')' || last_char == '.')) {
            return false;  // Looks like a character name, reject
          }
        }
      }
    }

    // 消费一行后重置延续标志
    scanner->continuation_active = false;

    // 消费整行内容（不消费行尾换行符，由语法规则处理）
    while (lexer->lookahead != '\n' && lexer->lookahead != '\0') {
      lexer->advance(lexer, false);
    }

    // It's a valid dialogue line - return the entire line content
    lexer->result_symbol = DIALOGUE_LINE_START;
    lexer->mark_end(lexer);

    // 前瞻窥探：mark_end后主动向前看，检测后续空白行类型
    // 此时extras尚未介入，\n字符可见
    if (lexer->lookahead == '\n') {
      lexer->advance(lexer, false);  // 跳过当前行尾的 \n

      int space_count = 0;
      while (lexer->lookahead == ' ' || lexer->lookahead == '\t') {
        space_count++;
        lexer->advance(lexer, false);
      }

      if (lexer->lookahead == '\n') {
        if (space_count < 2) {
          // 0-1空格空行：终止对话
          scanner->blank_seen_in_dialogue = true;
          scanner->continuation_active = false;
        } else {
          // 2+空格延续标记：保持对话开放
          scanner->continuation_active = true;
          scanner->blank_seen_in_dialogue = false;
        }
      }
      // tree-sitter会在函数返回后将lexer回滚到mark_end位罿
    }

    return true;
  }
// Try blank line - actively scan for blank lines (0-1 space then \n)
// Even when \n is in extras, the scanner can advance through it with skip=false
if (valid_symbols[BLANK_LINE]) {
    // Count leading whitespace including any unconsumed extras
    int space_count = 0;
    while (lexer->lookahead == ' ' || lexer->lookahead == '\t') {
      space_count++;
      lexer->advance(lexer, false);
    }

    // Actively scan for newline characters (they may be unconsumed extras)
    int newline_seen = 0;
    while (lexer->lookahead == '\n') {
      newline_seen++;
      lexer->advance(lexer, false);
    }

    // Match if we found a newline with 0-1 spaces
    if (newline_seen >= 1 && space_count < 2) {
      // 在对话上下文中设置空白行标志，阻止后续对话行匹配
      if (valid_symbols[DIALOGUE_LINE_START]) {
        scanner->blank_seen_in_dialogue = true;
        scanner->continuation_active = false;
      }
      lexer->result_symbol = BLANK_LINE;
      lexer->mark_end(lexer);
      return true;
    }
  }

  return false;
}

void tree_sitter_fountain_external_scanner_destroy(void *payload) {
  Scanner *scanner = (Scanner *)payload;
  if (scanner) {
    free(scanner);
  }
}

unsigned tree_sitter_fountain_external_scanner_serialize(void *payload, char *buffer) {
  Scanner *scanner = (Scanner *)payload;
  if (scanner && buffer) {
    buffer[0] = scanner->in_title_page ? 1 : 0;
    buffer[1] = scanner->blank_seen_in_dialogue ? 1 : 0;
    buffer[2] = scanner->continuation_active ? 1 : 0;
    return 3;
  }
  return 0;
}

void tree_sitter_fountain_external_scanner_deserialize(void *payload, const char *buffer, unsigned length) {
  Scanner *scanner = (Scanner *)payload;
  if (scanner && buffer && length >= 3) {
    scanner->in_title_page = buffer[0] != 0;
    scanner->blank_seen_in_dialogue = buffer[1] != 0;
    scanner->continuation_active = buffer[2] != 0;
  } else if (scanner) {
    scanner->in_title_page = true;
    scanner->blank_seen_in_dialogue = false;
    scanner->continuation_active = false;
  }
}
