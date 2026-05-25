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
} Scanner;

void *tree_sitter_fountain_external_scanner_create() {
  Scanner *scanner = (Scanner *)malloc(sizeof(Scanner));
  scanner->in_title_page = true;  // Start assuming we're in title page
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
    lexer->result_symbol = BONEYARD_START;
    lexer->mark_end(lexer);
    return true;
  }

  // Try parenthetical_line - matches standalone (text) lines within dialogue blocks
  // Consumes the entire parenthetical content to prevent paren_text from matching it
  if (valid_symbols[PARENTHETICAL_LINE]) {
    // Count leading whitespace
    while (lexer->lookahead == ' ' || lexer->lookahead == '\t') {
      lexer->advance(lexer, false);
    }

    // Must start with '('
    if (lexer->lookahead == '(') {
      lexer->advance(lexer, false);  // consume '('

      // Scan to find closing ')'
      while (lexer->lookahead != ')' && lexer->lookahead != '\n' && lexer->lookahead != '\0') {
        lexer->advance(lexer, false);
      }

      if (lexer->lookahead == ')') {
        lexer->advance(lexer, false);  // consume ')'

        // Skip trailing whitespace
        while (lexer->lookahead == ' ' || lexer->lookahead == '\t') {
          lexer->advance(lexer, false);
        }

        // Must be at end of line (pure parenthetical)
        if (lexer->lookahead == '\n' || lexer->lookahead == '\0') {
          // Don't consume the newline - grammar handles that
          lexer->result_symbol = PARENTHETICAL_LINE;
          lexer->mark_end(lexer);
          return true;
        }
      }
    }
    // 不是有效的插入语行，fall through 继续检查其他令牌类型
  }

  // Try dialogue_line_start - matches if we're at the start of a non-blank line
  // This prevents dialogue from matching blank lines or lines after blank lines
  // Consumes the entire line content so the dialogue block can't extend past non-dialogue markers
  if (valid_symbols[DIALOGUE_LINE_START]) {    // Count leading whitespace
    while (lexer->lookahead == ' ' || lexer->lookahead == '\t') {
      lexer->advance(lexer, false);
    }

    // If we hit a newline or EOF, this is NOT a dialogue line (it's blank)
    if (lexer->lookahead == '\n' || lexer->lookahead == '\0') {
      return false;
    }

    // 检查是否是Fountain特殊标记：场景、章节、强制角色、梗概、歌词、转场/居中、强制动作
    // 对话行不应以这些字符开头（备注[[和注释/*由语法层面的更高优先级来处理）
    if (lexer->lookahead == '.' || lexer->lookahead == '#' || lexer->lookahead == '@' ||
        lexer->lookahead == '=' || lexer->lookahead == '~' || lexer->lookahead == '>' ||
        lexer->lookahead == '!') {
      return false;
    }

    // 检查是否是独立括号行：排除纯插入语 `(text)` 开头且行尾无其他内容的行
    // 纯粹的插入语应由语法层面的 parenthetical 规则匹配
    // 括号后有其他文字的行（如 `(停顿) 继续说话`）仍作为对话行处理
    if (lexer->lookahead == '(') {
      lexer->advance(lexer, false);  // 跳过 '('

      // 扫描寻找匹配的 ')'
      while (lexer->lookahead != ')' && lexer->lookahead != '\n' && lexer->lookahead != '\0') {
        lexer->advance(lexer, false);
      }

      if (lexer->lookahead == ')') {
        lexer->advance(lexer, false);  // 跳过 ')'

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

    // Consume the entire line (but NOT the newline - grammar handles that)
    while (lexer->lookahead != '\n' && lexer->lookahead != '\0') {
      lexer->advance(lexer, false);
    }

    // It's a valid dialogue line - return the entire line content
    lexer->result_symbol = DIALOGUE_LINE_START;
    lexer->mark_end(lexer);
    return true;
  }

// Try blank line - detects when we're at the start of an empty line (or EOF)
// This ends dialogue blocks. Only 0 or 1 space ends dialogue (truly empty or single space).
// 2+ spaces means indented line (continuation or title continuation)
if (valid_symbols[BLANK_LINE]) {
    // Count leading whitespace (spaces/tabs)
    int space_count = 0;
    while (lexer->lookahead == ' ' || lexer->lookahead == '\t') {
      space_count++;
      lexer->advance(lexer, false);
    }

    // Only 0 or 1 spaces is a blank line (ends dialogue)
    // 2+ spaces means indented line, not blank
    if (space_count < 2 && lexer->lookahead == '\n') {
      lexer->advance(lexer, false);  // Consume the newline
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
    return 1;
  }
  return 0;
}

void tree_sitter_fountain_external_scanner_deserialize(void *payload, const char *buffer, unsigned length) {
  Scanner *scanner = (Scanner *)payload;
  if (scanner && buffer && length > 0) {
    scanner->in_title_page = buffer[0] != 0;
  } else if (scanner) {
    scanner->in_title_page = true;  // Default to true if no state
  }
}
