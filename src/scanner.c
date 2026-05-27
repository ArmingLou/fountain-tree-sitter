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
  DIALOGUE_BODY,
  PARENTHETICAL_LINE,
  INLINE_NOTE,
  INLINE_BONEYARD,
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

  // 如果不是在对话/插入语上下文中，重置状态标志
  if (!valid_symbols[DIALOGUE_LINE_START] && !valid_symbols[PARENTHETICAL_LINE]) {
    scanner->blank_seen_in_dialogue = false;
    scanner->continuation_active = false;
  }

  // Try title continuation (indented line: 3+ spaces or tab at start of line)
  if (valid_symbols[TITLE_CONTINUATION] && scanner->in_title_page) {
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

    if ((space_count >= 3 || has_tab) &&
        lexer->lookahead != '\n' &&
        lexer->lookahead != '\0') {
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
    if (lexer->lookahead == '.') {
      lexer->advance(lexer, false);

      // 检查中文特例：.(外景)、.(内景)、.(内外景)
      if (lexer->lookahead == '(') {
        lexer->advance(lexer, false);

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
        return false;
      }

      if (iswalnum(lexer->lookahead)) {
        scanner->in_title_page = false;
        lexer->result_symbol = SCENE_START;
        lexer->mark_end(lexer);
        return true;
      }
      return false;
    }

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

  // ============================================================
  // 最高优先级：检查 note [[ 和注释 /* 
  // 无论在action还是dialogue中，无论在什么位置，都优先匹配
  // 支持跨行
  // ============================================================

  // Try note start ([[) - 最高优先级，只消费 [[
  if (valid_symbols[NOTE_START] && lexer->lookahead == '[') {
    lexer->advance(lexer, false);
    if (lexer->lookahead == '[') {
      lexer->advance(lexer, false);
      lexer->result_symbol = NOTE_START;
      lexer->mark_end(lexer);
      return true;
    }
    lexer->lookahead = '[';
  }

  // Try boneyard (/*) - 最高优先级，只消费 /*
  if (valid_symbols[BONEYARD_START] && lexer->lookahead == '/') {
    lexer->advance(lexer, false);
    if (lexer->lookahead == '*') {
      lexer->advance(lexer, false);
      lexer->result_symbol = BONEYARD_START;
      lexer->mark_end(lexer);
      return true;
    }
    lexer->lookahead = '/';
  }

  // Try inline note ([[...]]) - 用于action行内
  if (valid_symbols[INLINE_NOTE]) {
    if (lexer->lookahead == '[') {
      lexer->advance(lexer, false);
      if (lexer->lookahead == '[') {
        while (lexer->lookahead != '\0') {
          if (lexer->lookahead == ']') {
            lexer->advance(lexer, false);
            if (lexer->lookahead == ']') {
              lexer->advance(lexer, false);
              lexer->result_symbol = INLINE_NOTE;
              lexer->mark_end(lexer);
              return true;
            }
            continue;
          }
          lexer->advance(lexer, false);
        }
        return false;
      }
    }
  }

  // Try inline boneyard (/*...*/) - 用于action行内
  if (valid_symbols[INLINE_BONEYARD]) {
    if (lexer->lookahead == '/') {
      lexer->advance(lexer, false);
      if (lexer->lookahead == '*') {
        while (lexer->lookahead != '\0') {
          if (lexer->lookahead == '*') {
            lexer->advance(lexer, false);
            if (lexer->lookahead == '/') {
              lexer->advance(lexer, false);
              lexer->result_symbol = INLINE_BONEYARD;
              lexer->mark_end(lexer);
              return true;
            }
            continue;
          }
          lexer->advance(lexer, false);
        }
        return false;
      }
    }
  }

  // ============================================================
  // DIALOGUE_BODY - 消费整个对话内容，消除GLR歧义
  // 逐行消费：内容行 + 2+空格延续标记 + 延续内容
  // 结束于：0-1空格空行 或 EOF
  // ============================================================
  if (valid_symbols[DIALOGUE_BODY]) {
    scanner->continuation_active = false;
    scanner->blank_seen_in_dialogue = false;
    bool started = false;
    
    while (1) {
      int indent = 0;
      while (lexer->lookahead == ' ' || lexer->lookahead == '\t') {
        indent++; lexer->advance(lexer, false);
      }
      
      // 空行处理
      if (lexer->lookahead == '\n') {
        if (started && indent >= 2) {
          lexer->advance(lexer, false); continue;  // 延续
        } else {
          break;  // 结束（0-1空格 或 尚未开始）
        }
      }
      if (lexer->lookahead == '\0') break;
      
      // 消费整行
      while (lexer->lookahead != '\n' && lexer->lookahead != '\0') lexer->advance(lexer, false);
      if (lexer->lookahead == '\n') lexer->advance(lexer, false);
      started = true;
      lexer->mark_end(lexer);
    }
    
    if (started) { lexer->result_symbol = DIALOGUE_BODY; return true; }
    return false;
  }

  // ============================================================
  // 对话块内部匹配（保留用于旧语法兼容）
  // ============================================================
  
  if (valid_symbols[DIALOGUE_LINE_START]) {
    int indent = 0;
    while (lexer->lookahead == ' ' || lexer->lookahead == '\t') {
      indent++;
      lexer->advance(lexer, false);
    }

    // 空行处理
    if (lexer->lookahead == '\n' || lexer->lookahead == '\0') {
      if (indent >= 2) {
        scanner->continuation_active = true;
        scanner->blank_seen_in_dialogue = false;
        lexer->result_symbol = DIALOGUE_LINE_START;
        lexer->mark_end(lexer);
        return true;
      } else {
        scanner->blank_seen_in_dialogue = true;
        scanner->continuation_active = false;
        return false;
      }
    }

    // 检查纯括号行 - 拒绝让PARENTHETICAL_LINE匹配
    {
      int32_t open_paren = 0, close_paren = 0;
      if (lexer->lookahead == '(') { open_paren = '('; close_paren = ')'; }
      else if (lexer->lookahead == 0xFF08) { open_paren = 0xFF08; close_paren = 0xFF09; }
      if (open_paren) {
        lexer->advance(lexer, false);
        while (lexer->lookahead != close_paren && lexer->lookahead != '\n' && lexer->lookahead != '\0')
          lexer->advance(lexer, false);
        if (lexer->lookahead == close_paren) {
          lexer->advance(lexer, false);
          while (lexer->lookahead == ' ' || lexer->lookahead == '\t') lexer->advance(lexer, false);
          if (lexer->lookahead == '\n' || lexer->lookahead == '\0') return false;
        }
      }
    }

    // 消费整行（不检查 @、>、#、. 等标记）
    while (lexer->lookahead != '\n' && lexer->lookahead != '\0') lexer->advance(lexer, false);
    lexer->result_symbol = DIALOGUE_LINE_START;
    lexer->mark_end(lexer);

    // 前瞻
    if (lexer->lookahead == '\n') {
      lexer->advance(lexer, false);
      int sc = 0;
      while (lexer->lookahead == ' ' || lexer->lookahead == '\t') { sc++; lexer->advance(lexer, false); }
      if (lexer->lookahead == '\n') {
        if (sc < 2) { scanner->blank_seen_in_dialogue = true; scanner->continuation_active = false; }
        else { scanner->continuation_active = true; scanner->blank_seen_in_dialogue = false; }
      }
    }
    return true;
  }

  // Try forced action (!)
  if (valid_symbols[FORCED_ACTION_START] && lexer->lookahead == '!') {
    // 延续模式下，! 不作为强制动作，让对话延续
    if (scanner->continuation_active) return false;
    lexer->advance(lexer, false);
    lexer->result_symbol = FORCED_ACTION_START;
    lexer->mark_end(lexer);
    return true;
  }

  // 3+空格开头的行在对话上下文中视为延续，不作为action
  if (valid_symbols[FORCED_ACTION_START]) {
    int space_count = 0;
    while (lexer->lookahead == ' ' || lexer->lookahead == '\t') {
      space_count++;
      lexer->advance(lexer, false);
    }
    if (space_count >= 3 && valid_symbols[DIALOGUE_LINE_START]) {
      // 在对话上下文中，3+空格行由DIALOGUE_LINE_START处理
      return false;
    }
  }

  // Try forced character (@)
  if (valid_symbols[FORCED_CHARACTER_START] && lexer->lookahead == '@') {
    // 延续模式下，@ 不作为新角色，让其作为对话内容
    if (scanner->continuation_active) return false;
    scanner->blank_seen_in_dialogue = false;
    scanner->continuation_active = false;
    lexer->advance(lexer, false);
    lexer->result_symbol = FORCED_CHARACTER_START;
    lexer->mark_end(lexer);
    return true;
  }

  // Try forced transition or centered (>)
  if ((valid_symbols[FORCED_TRANSITION_START] || valid_symbols[CENTERED_START]) && lexer->lookahead == '>') {
    // 延续模式下，> 不作为转场，让对话延续
    if (scanner->continuation_active) return false;
    lexer->advance(lexer, false);
    lexer->mark_end(lexer);

    bool has_closing_bracket = false;
    while (lexer->lookahead != '\n' && lexer->lookahead != '\0') {
      if (lexer->lookahead == '<') {
        has_closing_bracket = true;
        break;
      }
      lexer->advance(lexer, false);
    }

    if (has_closing_bracket && valid_symbols[CENTERED_START]) {
      lexer->result_symbol = CENTERED_START;
      return true;
    }
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

  // Try parenthetical_line - matches standalone (text) or （中文括号） lines
  if (valid_symbols[PARENTHETICAL_LINE]) {
    // Count leading whitespace
    while (lexer->lookahead == ' ' || lexer->lookahead == '\t') {
      lexer->advance(lexer, false);
    }

    int32_t open_paren = 0;
    int32_t close_paren = 0;

    if (lexer->lookahead == '(') {
      open_paren = '(';
      close_paren = ')';
    } else if (lexer->lookahead == 0xFF08) {
      open_paren = 0xFF08;
      close_paren = 0xFF09;
    }

    if (open_paren != 0) {
      lexer->advance(lexer, false);

      while (lexer->lookahead != close_paren && lexer->lookahead != '\n' && lexer->lookahead != '\0') {
        lexer->advance(lexer, false);
      }

      if (lexer->lookahead == close_paren) {
        lexer->advance(lexer, false);

        while (lexer->lookahead == ' ' || lexer->lookahead == '\t') {
          lexer->advance(lexer, false);
        }

        if (lexer->lookahead == '\n' || lexer->lookahead == '\0') {
          lexer->result_symbol = PARENTHETICAL_LINE;
          lexer->mark_end(lexer);
          return true;
        }
      }
    }
  }

  // Try blank line
  if (valid_symbols[BLANK_LINE]) {
    int space_count = 0;
    while (lexer->lookahead == ' ' || lexer->lookahead == '\t') {
      space_count++;
      lexer->advance(lexer, false);
    }

    int newline_seen = 0;
    while (lexer->lookahead == '\n') {
      newline_seen++;
      lexer->advance(lexer, false);
    }

    if (newline_seen >= 1) {
      if (space_count < 2) {
        // 0-1 space: always blank line
        if (valid_symbols[DIALOGUE_LINE_START]) {
          scanner->blank_seen_in_dialogue = true;
        }
        lexer->result_symbol = BLANK_LINE;
        lexer->mark_end(lexer);
        return true;
      } else if (!valid_symbols[DIALOGUE_LINE_START]) {
        // 2+ space but NOT in dialogue context: treat as blank line
        lexer->result_symbol = BLANK_LINE;
        lexer->mark_end(lexer);
        return true;
      }
      // 2+ space in dialogue context: return false so DIALOGUE_LINE_START can handle it
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