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
    // Check for forced scene heading (. followed by alphanumeric)
    if (lexer->lookahead == '.') {
      lexer->advance(lexer, false);
      // Must be followed by an alphanumeric character to be a forced scene heading
      if (iswalnum(lexer->lookahead)) {
        scanner->in_title_page = false;
        lexer->result_symbol = SCENE_START;
        lexer->mark_end(lexer);
        return true;
      }
      // Not a forced scene heading, backtrack would be needed but we can't,
      // so this will just fail to match
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
  if (lexer->lookahead == '>') {
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

  // Try dialogue_line_start - matches if we're at the start of a non-blank line
  // This prevents dialogue from matching blank lines or lines after blank lines
  if (valid_symbols[DIALOGUE_LINE_START]) {
    // Skip any whitespace (spaces/tabs)
    while (lexer->lookahead == ' ' || lexer->lookahead == '\t') {
      lexer->advance(lexer, false);
    }

    // If we hit a newline or EOF, this is NOT a dialogue line (it's blank)
    if (lexer->lookahead == '\n' || lexer->lookahead == '\0') {
      return false;
    }

    // Otherwise, it's a valid dialogue line start
    lexer->result_symbol = DIALOGUE_LINE_START;
    lexer->mark_end(lexer);
    return true;
  }

  // Try blank line - detects when we're at the start of an empty line (or EOF)
  // This ends dialogue blocks
  if (valid_symbols[BLANK_LINE]) {
    // Skip any whitespace (spaces/tabs)
    while (lexer->lookahead == ' ' || lexer->lookahead == '\t') {
      lexer->advance(lexer, false);
    }

    // If we're at a newline or EOF, this is a blank line
    if (lexer->lookahead == '\n') {
      lexer->advance(lexer, false);  // Consume the newline
      lexer->result_symbol = BLANK_LINE;
      lexer->mark_end(lexer);
      return true;
    }

    if (lexer->lookahead == '\0') {
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
