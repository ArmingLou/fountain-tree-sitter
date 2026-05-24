#include "tree_sitter/parser.h"

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

#define LANGUAGE_VERSION 14
#define STATE_COUNT 111
#define LARGE_STATE_COUNT 6
#define SYMBOL_COUNT 82
#define ALIAS_COUNT 0
#define TOKEN_COUNT 50
#define EXTERNAL_TOKEN_COUNT 14
#define FIELD_COUNT 0
#define MAX_ALIAS_SEQUENCE_LENGTH 7
#define PRODUCTION_ID_COUNT 1

enum ts_symbol_identifiers {
  anon_sym_LF = 1,
  sym_title_key = 2,
  sym_title_key_with_space = 3,
  anon_sym_SPACE = 4,
  anon_sym_DASH = 5,
  anon_sym_DOT = 6,
  sym_scene_location = 7,
  sym_scene_time = 8,
  anon_sym_POUND = 9,
  aux_sym_scene_number_token1 = 10,
  aux_sym_character_token1 = 11,
  aux_sym_character_token2 = 12,
  aux_sym_character_token3 = 13,
  anon_sym_LF2 = 14,
  aux_sym_parenthetical_token1 = 15,
  anon_sym_LPAREN = 16,
  aux_sym_parenthetical_token2 = 17,
  anon_sym_RPAREN = 18,
  aux_sym_transition_token1 = 19,
  anon_sym_RBRACK_RBRACK = 20,
  sym_note_content = 21,
  anon_sym_STAR_SLASH = 22,
  sym_boneyard_content = 23,
  sym_centered_text = 24,
  sym_centered_end = 25,
  sym_escaped_char = 26,
  sym_bold_italic = 27,
  sym_bold = 28,
  sym_italic = 29,
  sym_underline = 30,
  sym_uppercase_text = 31,
  sym_paren_text = 32,
  sym_literal_char = 33,
  sym_text = 34,
  sym_description = 35,
  sym_scene_start = 36,
  sym_section_start = 37,
  sym_note_start = 38,
  sym_forced_action_start = 39,
  sym_forced_character_start = 40,
  sym_forced_transition_start = 41,
  sym_lyric_start = 42,
  sym_centered_start = 43,
  sym_page_break_marker = 44,
  sym_synopsis_start = 45,
  sym_boneyard_start = 46,
  sym_title_continuation = 47,
  sym_blank_line = 48,
  sym_dialogue_line_start = 49,
  sym_document = 50,
  sym_title_page = 51,
  sym__element = 52,
  sym_section_block = 53,
  sym_scene_block = 54,
  sym__scene_content = 55,
  sym_title_page_field = 56,
  sym_scene_heading = 57,
  sym_scene_number = 58,
  sym_character = 59,
  sym_dialogue_block = 60,
  sym_dialogue = 61,
  sym_parenthetical = 62,
  sym_action = 63,
  sym_transition = 64,
  sym_section_heading = 65,
  sym_note = 66,
  sym_boneyard = 67,
  sym_page_break = 68,
  sym_synopsis = 69,
  sym_lyric = 70,
  sym_centered = 71,
  sym__action_inline_content = 72,
  sym__inline_content = 73,
  aux_sym_document_repeat1 = 74,
  aux_sym_title_page_repeat1 = 75,
  aux_sym_section_block_repeat1 = 76,
  aux_sym_scene_block_repeat1 = 77,
  aux_sym_title_page_field_repeat1 = 78,
  aux_sym_dialogue_block_repeat1 = 79,
  aux_sym_dialogue_repeat1 = 80,
  aux_sym_action_repeat1 = 81,
};

static const char * const ts_symbol_names[] = {
  [ts_builtin_sym_end] = "end",
  [anon_sym_LF] = "\n",
  [sym_title_key] = "title_key",
  [sym_title_key_with_space] = "title_key_with_space",
  [anon_sym_SPACE] = " ",
  [anon_sym_DASH] = "-",
  [anon_sym_DOT] = ".",
  [sym_scene_location] = "scene_location",
  [sym_scene_time] = "scene_time",
  [anon_sym_POUND] = "#",
  [aux_sym_scene_number_token1] = "scene_number_token1",
  [aux_sym_character_token1] = "character_token1",
  [aux_sym_character_token2] = "character_token2",
  [aux_sym_character_token3] = "character_token3",
  [anon_sym_LF2] = "\n",
  [aux_sym_parenthetical_token1] = "parenthetical_token1",
  [anon_sym_LPAREN] = "(",
  [aux_sym_parenthetical_token2] = "parenthetical_token2",
  [anon_sym_RPAREN] = ")",
  [aux_sym_transition_token1] = "transition_token1",
  [anon_sym_RBRACK_RBRACK] = "]]",
  [sym_note_content] = "note_content",
  [anon_sym_STAR_SLASH] = "*/",
  [sym_boneyard_content] = "boneyard_content",
  [sym_centered_text] = "centered_text",
  [sym_centered_end] = "centered_end",
  [sym_escaped_char] = "escaped_char",
  [sym_bold_italic] = "bold_italic",
  [sym_bold] = "bold",
  [sym_italic] = "italic",
  [sym_underline] = "underline",
  [sym_uppercase_text] = "uppercase_text",
  [sym_paren_text] = "paren_text",
  [sym_literal_char] = "literal_char",
  [sym_text] = "text",
  [sym_description] = "description",
  [sym_scene_start] = "scene_start",
  [sym_section_start] = "section_start",
  [sym_note_start] = "note_start",
  [sym_forced_action_start] = "forced_action_start",
  [sym_forced_character_start] = "forced_character_start",
  [sym_forced_transition_start] = "forced_transition_start",
  [sym_lyric_start] = "lyric_start",
  [sym_centered_start] = "centered_start",
  [sym_page_break_marker] = "page_break_marker",
  [sym_synopsis_start] = "synopsis_start",
  [sym_boneyard_start] = "boneyard_start",
  [sym_title_continuation] = "title_continuation",
  [sym_blank_line] = "blank_line",
  [sym_dialogue_line_start] = "dialogue_line_start",
  [sym_document] = "document",
  [sym_title_page] = "title_page",
  [sym__element] = "_element",
  [sym_section_block] = "section_block",
  [sym_scene_block] = "scene_block",
  [sym__scene_content] = "_scene_content",
  [sym_title_page_field] = "title_page_field",
  [sym_scene_heading] = "scene_heading",
  [sym_scene_number] = "scene_number",
  [sym_character] = "character",
  [sym_dialogue_block] = "dialogue_block",
  [sym_dialogue] = "dialogue",
  [sym_parenthetical] = "parenthetical",
  [sym_action] = "action",
  [sym_transition] = "transition",
  [sym_section_heading] = "section_heading",
  [sym_note] = "note",
  [sym_boneyard] = "boneyard",
  [sym_page_break] = "page_break",
  [sym_synopsis] = "synopsis",
  [sym_lyric] = "lyric",
  [sym_centered] = "centered",
  [sym__action_inline_content] = "_action_inline_content",
  [sym__inline_content] = "_inline_content",
  [aux_sym_document_repeat1] = "document_repeat1",
  [aux_sym_title_page_repeat1] = "title_page_repeat1",
  [aux_sym_section_block_repeat1] = "section_block_repeat1",
  [aux_sym_scene_block_repeat1] = "scene_block_repeat1",
  [aux_sym_title_page_field_repeat1] = "title_page_field_repeat1",
  [aux_sym_dialogue_block_repeat1] = "dialogue_block_repeat1",
  [aux_sym_dialogue_repeat1] = "dialogue_repeat1",
  [aux_sym_action_repeat1] = "action_repeat1",
};

static const TSSymbol ts_symbol_map[] = {
  [ts_builtin_sym_end] = ts_builtin_sym_end,
  [anon_sym_LF] = anon_sym_LF,
  [sym_title_key] = sym_title_key,
  [sym_title_key_with_space] = sym_title_key_with_space,
  [anon_sym_SPACE] = anon_sym_SPACE,
  [anon_sym_DASH] = anon_sym_DASH,
  [anon_sym_DOT] = anon_sym_DOT,
  [sym_scene_location] = sym_scene_location,
  [sym_scene_time] = sym_scene_time,
  [anon_sym_POUND] = anon_sym_POUND,
  [aux_sym_scene_number_token1] = aux_sym_scene_number_token1,
  [aux_sym_character_token1] = aux_sym_character_token1,
  [aux_sym_character_token2] = aux_sym_character_token2,
  [aux_sym_character_token3] = aux_sym_character_token3,
  [anon_sym_LF2] = anon_sym_LF,
  [aux_sym_parenthetical_token1] = aux_sym_parenthetical_token1,
  [anon_sym_LPAREN] = anon_sym_LPAREN,
  [aux_sym_parenthetical_token2] = aux_sym_parenthetical_token2,
  [anon_sym_RPAREN] = anon_sym_RPAREN,
  [aux_sym_transition_token1] = aux_sym_transition_token1,
  [anon_sym_RBRACK_RBRACK] = anon_sym_RBRACK_RBRACK,
  [sym_note_content] = sym_note_content,
  [anon_sym_STAR_SLASH] = anon_sym_STAR_SLASH,
  [sym_boneyard_content] = sym_boneyard_content,
  [sym_centered_text] = sym_centered_text,
  [sym_centered_end] = sym_centered_end,
  [sym_escaped_char] = sym_escaped_char,
  [sym_bold_italic] = sym_bold_italic,
  [sym_bold] = sym_bold,
  [sym_italic] = sym_italic,
  [sym_underline] = sym_underline,
  [sym_uppercase_text] = sym_uppercase_text,
  [sym_paren_text] = sym_paren_text,
  [sym_literal_char] = sym_literal_char,
  [sym_text] = sym_text,
  [sym_description] = sym_description,
  [sym_scene_start] = sym_scene_start,
  [sym_section_start] = sym_section_start,
  [sym_note_start] = sym_note_start,
  [sym_forced_action_start] = sym_forced_action_start,
  [sym_forced_character_start] = sym_forced_character_start,
  [sym_forced_transition_start] = sym_forced_transition_start,
  [sym_lyric_start] = sym_lyric_start,
  [sym_centered_start] = sym_centered_start,
  [sym_page_break_marker] = sym_page_break_marker,
  [sym_synopsis_start] = sym_synopsis_start,
  [sym_boneyard_start] = sym_boneyard_start,
  [sym_title_continuation] = sym_title_continuation,
  [sym_blank_line] = sym_blank_line,
  [sym_dialogue_line_start] = sym_dialogue_line_start,
  [sym_document] = sym_document,
  [sym_title_page] = sym_title_page,
  [sym__element] = sym__element,
  [sym_section_block] = sym_section_block,
  [sym_scene_block] = sym_scene_block,
  [sym__scene_content] = sym__scene_content,
  [sym_title_page_field] = sym_title_page_field,
  [sym_scene_heading] = sym_scene_heading,
  [sym_scene_number] = sym_scene_number,
  [sym_character] = sym_character,
  [sym_dialogue_block] = sym_dialogue_block,
  [sym_dialogue] = sym_dialogue,
  [sym_parenthetical] = sym_parenthetical,
  [sym_action] = sym_action,
  [sym_transition] = sym_transition,
  [sym_section_heading] = sym_section_heading,
  [sym_note] = sym_note,
  [sym_boneyard] = sym_boneyard,
  [sym_page_break] = sym_page_break,
  [sym_synopsis] = sym_synopsis,
  [sym_lyric] = sym_lyric,
  [sym_centered] = sym_centered,
  [sym__action_inline_content] = sym__action_inline_content,
  [sym__inline_content] = sym__inline_content,
  [aux_sym_document_repeat1] = aux_sym_document_repeat1,
  [aux_sym_title_page_repeat1] = aux_sym_title_page_repeat1,
  [aux_sym_section_block_repeat1] = aux_sym_section_block_repeat1,
  [aux_sym_scene_block_repeat1] = aux_sym_scene_block_repeat1,
  [aux_sym_title_page_field_repeat1] = aux_sym_title_page_field_repeat1,
  [aux_sym_dialogue_block_repeat1] = aux_sym_dialogue_block_repeat1,
  [aux_sym_dialogue_repeat1] = aux_sym_dialogue_repeat1,
  [aux_sym_action_repeat1] = aux_sym_action_repeat1,
};

static const TSSymbolMetadata ts_symbol_metadata[] = {
  [ts_builtin_sym_end] = {
    .visible = false,
    .named = true,
  },
  [anon_sym_LF] = {
    .visible = true,
    .named = false,
  },
  [sym_title_key] = {
    .visible = true,
    .named = true,
  },
  [sym_title_key_with_space] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_SPACE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_DASH] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_DOT] = {
    .visible = true,
    .named = false,
  },
  [sym_scene_location] = {
    .visible = true,
    .named = true,
  },
  [sym_scene_time] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_POUND] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_scene_number_token1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_character_token1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_character_token2] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_character_token3] = {
    .visible = false,
    .named = false,
  },
  [anon_sym_LF2] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_parenthetical_token1] = {
    .visible = false,
    .named = false,
  },
  [anon_sym_LPAREN] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_parenthetical_token2] = {
    .visible = false,
    .named = false,
  },
  [anon_sym_RPAREN] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_transition_token1] = {
    .visible = false,
    .named = false,
  },
  [anon_sym_RBRACK_RBRACK] = {
    .visible = true,
    .named = false,
  },
  [sym_note_content] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_STAR_SLASH] = {
    .visible = true,
    .named = false,
  },
  [sym_boneyard_content] = {
    .visible = true,
    .named = true,
  },
  [sym_centered_text] = {
    .visible = true,
    .named = true,
  },
  [sym_centered_end] = {
    .visible = true,
    .named = true,
  },
  [sym_escaped_char] = {
    .visible = true,
    .named = true,
  },
  [sym_bold_italic] = {
    .visible = true,
    .named = true,
  },
  [sym_bold] = {
    .visible = true,
    .named = true,
  },
  [sym_italic] = {
    .visible = true,
    .named = true,
  },
  [sym_underline] = {
    .visible = true,
    .named = true,
  },
  [sym_uppercase_text] = {
    .visible = true,
    .named = true,
  },
  [sym_paren_text] = {
    .visible = true,
    .named = true,
  },
  [sym_literal_char] = {
    .visible = true,
    .named = true,
  },
  [sym_text] = {
    .visible = true,
    .named = true,
  },
  [sym_description] = {
    .visible = true,
    .named = true,
  },
  [sym_scene_start] = {
    .visible = true,
    .named = true,
  },
  [sym_section_start] = {
    .visible = true,
    .named = true,
  },
  [sym_note_start] = {
    .visible = true,
    .named = true,
  },
  [sym_forced_action_start] = {
    .visible = true,
    .named = true,
  },
  [sym_forced_character_start] = {
    .visible = true,
    .named = true,
  },
  [sym_forced_transition_start] = {
    .visible = true,
    .named = true,
  },
  [sym_lyric_start] = {
    .visible = true,
    .named = true,
  },
  [sym_centered_start] = {
    .visible = true,
    .named = true,
  },
  [sym_page_break_marker] = {
    .visible = true,
    .named = true,
  },
  [sym_synopsis_start] = {
    .visible = true,
    .named = true,
  },
  [sym_boneyard_start] = {
    .visible = true,
    .named = true,
  },
  [sym_title_continuation] = {
    .visible = true,
    .named = true,
  },
  [sym_blank_line] = {
    .visible = true,
    .named = true,
  },
  [sym_dialogue_line_start] = {
    .visible = true,
    .named = true,
  },
  [sym_document] = {
    .visible = true,
    .named = true,
  },
  [sym_title_page] = {
    .visible = true,
    .named = true,
  },
  [sym__element] = {
    .visible = false,
    .named = true,
  },
  [sym_section_block] = {
    .visible = true,
    .named = true,
  },
  [sym_scene_block] = {
    .visible = true,
    .named = true,
  },
  [sym__scene_content] = {
    .visible = false,
    .named = true,
  },
  [sym_title_page_field] = {
    .visible = true,
    .named = true,
  },
  [sym_scene_heading] = {
    .visible = true,
    .named = true,
  },
  [sym_scene_number] = {
    .visible = true,
    .named = true,
  },
  [sym_character] = {
    .visible = true,
    .named = true,
  },
  [sym_dialogue_block] = {
    .visible = true,
    .named = true,
  },
  [sym_dialogue] = {
    .visible = true,
    .named = true,
  },
  [sym_parenthetical] = {
    .visible = true,
    .named = true,
  },
  [sym_action] = {
    .visible = true,
    .named = true,
  },
  [sym_transition] = {
    .visible = true,
    .named = true,
  },
  [sym_section_heading] = {
    .visible = true,
    .named = true,
  },
  [sym_note] = {
    .visible = true,
    .named = true,
  },
  [sym_boneyard] = {
    .visible = true,
    .named = true,
  },
  [sym_page_break] = {
    .visible = true,
    .named = true,
  },
  [sym_synopsis] = {
    .visible = true,
    .named = true,
  },
  [sym_lyric] = {
    .visible = true,
    .named = true,
  },
  [sym_centered] = {
    .visible = true,
    .named = true,
  },
  [sym__action_inline_content] = {
    .visible = false,
    .named = true,
  },
  [sym__inline_content] = {
    .visible = false,
    .named = true,
  },
  [aux_sym_document_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_title_page_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_section_block_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_scene_block_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_title_page_field_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_dialogue_block_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_dialogue_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_action_repeat1] = {
    .visible = false,
    .named = false,
  },
};

static const TSSymbol ts_alias_sequences[PRODUCTION_ID_COUNT][MAX_ALIAS_SEQUENCE_LENGTH] = {
  [0] = {0},
};

static const uint16_t ts_non_terminal_alias_map[] = {
  0,
};

static const TSStateId ts_primary_state_ids[STATE_COUNT] = {
  [0] = 0,
  [1] = 1,
  [2] = 2,
  [3] = 3,
  [4] = 4,
  [5] = 5,
  [6] = 6,
  [7] = 7,
  [8] = 8,
  [9] = 9,
  [10] = 10,
  [11] = 11,
  [12] = 12,
  [13] = 13,
  [14] = 14,
  [15] = 15,
  [16] = 16,
  [17] = 17,
  [18] = 18,
  [19] = 19,
  [20] = 20,
  [21] = 21,
  [22] = 22,
  [23] = 23,
  [24] = 24,
  [25] = 25,
  [26] = 26,
  [27] = 27,
  [28] = 28,
  [29] = 29,
  [30] = 30,
  [31] = 31,
  [32] = 32,
  [33] = 33,
  [34] = 34,
  [35] = 35,
  [36] = 36,
  [37] = 37,
  [38] = 38,
  [39] = 39,
  [40] = 40,
  [41] = 41,
  [42] = 42,
  [43] = 43,
  [44] = 44,
  [45] = 45,
  [46] = 46,
  [47] = 47,
  [48] = 48,
  [49] = 49,
  [50] = 50,
  [51] = 51,
  [52] = 52,
  [53] = 53,
  [54] = 54,
  [55] = 55,
  [56] = 56,
  [57] = 57,
  [58] = 58,
  [59] = 59,
  [60] = 60,
  [61] = 61,
  [62] = 62,
  [63] = 63,
  [64] = 64,
  [65] = 65,
  [66] = 66,
  [67] = 67,
  [68] = 68,
  [69] = 69,
  [70] = 70,
  [71] = 71,
  [72] = 72,
  [73] = 73,
  [74] = 74,
  [75] = 75,
  [76] = 76,
  [77] = 77,
  [78] = 78,
  [79] = 79,
  [80] = 80,
  [81] = 81,
  [82] = 82,
  [83] = 83,
  [84] = 84,
  [85] = 85,
  [86] = 86,
  [87] = 87,
  [88] = 88,
  [89] = 89,
  [90] = 90,
  [91] = 91,
  [92] = 92,
  [93] = 93,
  [94] = 94,
  [95] = 95,
  [96] = 96,
  [97] = 97,
  [98] = 98,
  [99] = 99,
  [100] = 100,
  [101] = 101,
  [102] = 102,
  [103] = 103,
  [104] = 104,
  [105] = 105,
  [106] = 106,
  [107] = 107,
  [108] = 108,
  [109] = 109,
  [110] = 110,
};

static bool ts_lex(TSLexer *lexer, TSStateId state) {
  START_LEXER();
  eof = lexer->eof(lexer);
  switch (state) {
    case 0:
      if (eof) ADVANCE(53);
      ADVANCE_MAP(
        ' ', 18,
        '#', 72,
        '(', 81,
        ')', 84,
        '*', 105,
        '-', 64,
        '.', 65,
        '<', 94,
        '\\', 46,
        ']', 39,
        '_', 106,
      );
      if (('\t' <= lookahead && lookahead <= '\r')) SKIP(0);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(20);
      END_STATE();
    case 1:
      if (lookahead == '\n') ADVANCE(74);
      END_STATE();
    case 2:
      if (lookahead == '\n') ADVANCE(74);
      if (lookahead == ' ') ADVANCE(40);
      if (lookahead == '\'' ||
          lookahead == '(') ADVANCE(42);
      if (lookahead == ')' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z')) ADVANCE(2);
      END_STATE();
    case 3:
      if (lookahead == '\n') ADVANCE(74);
      if (lookahead == ' ') ADVANCE(21);
      if (lookahead == ':') ADVANCE(85);
      if (lookahead == 'T') ADVANCE(4);
      if (lookahead == '\'' ||
          lookahead == '(') ADVANCE(42);
      if (lookahead == ')' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9')) ADVANCE(2);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(5);
      END_STATE();
    case 4:
      if (lookahead == '\n') ADVANCE(74);
      if (lookahead == ' ') ADVANCE(21);
      if (lookahead == 'O') ADVANCE(3);
      if (lookahead == 'T') ADVANCE(4);
      if (lookahead == '\'' ||
          lookahead == '(') ADVANCE(42);
      if (lookahead == ')' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9')) ADVANCE(2);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(5);
      END_STATE();
    case 5:
      if (lookahead == '\n') ADVANCE(74);
      if (lookahead == ' ') ADVANCE(21);
      if (lookahead == 'T') ADVANCE(4);
      if (lookahead == '\'' ||
          lookahead == '(') ADVANCE(42);
      if (lookahead == ')' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9')) ADVANCE(2);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(5);
      END_STATE();
    case 6:
      if (lookahead == '\n') SKIP(6);
      if (lookahead == ' ') ADVANCE(80);
      if (lookahead == '(') ADVANCE(81);
      if (lookahead == '*') ADVANCE(105);
      if (lookahead == '\\') ADVANCE(46);
      if (lookahead == '_') ADVANCE(106);
      if (('\t' <= lookahead && lookahead <= '\r')) ADVANCE(111);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(47);
      if (lookahead != 0 &&
          (lookahead < '(' || '*' < lookahead)) ADVANCE(118);
      END_STATE();
    case 7:
      if (lookahead == '\n') ADVANCE(54);
      if (lookahead == '(') ADVANCE(48);
      if (lookahead == '*') ADVANCE(105);
      if (lookahead == '\\') ADVANCE(46);
      if (lookahead == '_') ADVANCE(106);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') ADVANCE(109);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(47);
      if (lookahead != 0 &&
          (lookahead < '(' || '*' < lookahead)) ADVANCE(118);
      END_STATE();
    case 8:
      if (lookahead == '\n') ADVANCE(78);
      if (lookahead == '*') ADVANCE(105);
      if (lookahead == '\\') ADVANCE(46);
      if (lookahead == '_') ADVANCE(106);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') ADVANCE(117);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(47);
      if (lookahead != 0 &&
          (lookahead < '(' || '*' < lookahead)) ADVANCE(118);
      END_STATE();
    case 9:
      if (lookahead == '\n') ADVANCE(55);
      if (lookahead == ' ') ADVANCE(62);
      if (lookahead == '#') ADVANCE(72);
      if (lookahead == '-') ADVANCE(64);
      if (('\t' <= lookahead && lookahead <= '\r')) ADVANCE(67);
      if (lookahead != 0) ADVANCE(69);
      END_STATE();
    case 10:
      if (lookahead == '\n') ADVANCE(56);
      if (lookahead == ' ') ADVANCE(10);
      if (lookahead == '#') ADVANCE(72);
      if (lookahead == '-') ADVANCE(64);
      if (lookahead == '^') ADVANCE(77);
      if (('\t' <= lookahead && lookahead <= '\r')) SKIP(11);
      END_STATE();
    case 11:
      if (lookahead == '\n') ADVANCE(56);
      if (lookahead == ' ') ADVANCE(10);
      if (lookahead == '#') ADVANCE(72);
      if (lookahead == '-') ADVANCE(64);
      if (('\t' <= lookahead && lookahead <= '\r')) SKIP(11);
      END_STATE();
    case 12:
      if (lookahead == '\n') SKIP(12);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') ADVANCE(70);
      if (lookahead != 0 &&
          lookahead != '#') ADVANCE(71);
      END_STATE();
    case 13:
      if (lookahead == '\n') SKIP(13);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') ADVANCE(75);
      if (lookahead != 0) ADVANCE(76);
      END_STATE();
    case 14:
      if (lookahead == '\n') SKIP(14);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') ADVANCE(92);
      if (lookahead != 0 &&
          lookahead != '<') ADVANCE(93);
      END_STATE();
    case 15:
      if (lookahead == '\n') ADVANCE(57);
      if (lookahead == '#') ADVANCE(72);
      if (lookahead == '-') ADVANCE(64);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') ADVANCE(68);
      if (lookahead != 0) ADVANCE(69);
      END_STATE();
    case 16:
      if (lookahead == '\n') ADVANCE(58);
      if (lookahead == ' ') ADVANCE(63);
      if (('\t' <= lookahead && lookahead <= '\r')) SKIP(16);
      END_STATE();
    case 17:
      if (lookahead == '\n') ADVANCE(59);
      if (lookahead == ' ') ADVANCE(79);
      if (('\t' <= lookahead && lookahead <= '\r')) SKIP(17);
      END_STATE();
    case 18:
      ADVANCE_MAP(
        ' ', 18,
        '#', 72,
        '(', 81,
        ')', 84,
        '*', 105,
        '-', 64,
        '.', 65,
        '<', 94,
        '\\', 46,
        ']', 39,
        '^', 77,
        '_', 106,
      );
      if (('\t' <= lookahead && lookahead <= '\r')) SKIP(19);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(20);
      END_STATE();
    case 19:
      ADVANCE_MAP(
        ' ', 18,
        '#', 72,
        '(', 81,
        ')', 84,
        '*', 105,
        '-', 64,
        '.', 65,
        '<', 94,
        '\\', 46,
        ']', 39,
        '_', 106,
      );
      if (('\t' <= lookahead && lookahead <= '\r')) SKIP(19);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(20);
      END_STATE();
    case 20:
      if (lookahead == ' ') ADVANCE(22);
      if (lookahead == 'T') ADVANCE(101);
      if (lookahead == '\'' ||
          lookahead == '(') ADVANCE(42);
      if (lookahead == ')' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9')) ADVANCE(2);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(102);
      if (('a' <= lookahead && lookahead <= 'z')) ADVANCE(38);
      END_STATE();
    case 21:
      if (lookahead == ' ') ADVANCE(22);
      if (lookahead == 'T') ADVANCE(4);
      if (lookahead == '^') ADVANCE(1);
      if (lookahead == '\'' ||
          lookahead == '(') ADVANCE(42);
      if (lookahead == ')' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9')) ADVANCE(2);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(5);
      END_STATE();
    case 22:
      if (lookahead == ' ') ADVANCE(22);
      if (lookahead == 'T') ADVANCE(4);
      if (lookahead == '\'' ||
          lookahead == '(') ADVANCE(42);
      if (lookahead == ')' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9')) ADVANCE(2);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(5);
      END_STATE();
    case 23:
      if (lookahead == ' ') ADVANCE(110);
      if (lookahead == '\'') ADVANCE(113);
      if (lookahead == '(') ADVANCE(42);
      if (lookahead == ')') ADVANCE(2);
      if (lookahead == 'T') ADVANCE(101);
      if (lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9')) ADVANCE(107);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(102);
      if (('a' <= lookahead && lookahead <= 'z')) ADVANCE(116);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          (lookahead < '\'' || '*' < lookahead) &&
          lookahead != '\\' &&
          lookahead != '_') ADVANCE(118);
      END_STATE();
    case 24:
      if (lookahead == ' ') ADVANCE(110);
      if (lookahead == '\'') ADVANCE(113);
      if (lookahead == '(') ADVANCE(42);
      if (lookahead == ')') ADVANCE(2);
      if (lookahead == 'T') ADVANCE(101);
      if (lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9')) ADVANCE(107);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(102);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          (lookahead < '\'' || '*' < lookahead) &&
          lookahead != '\\' &&
          lookahead != '_') ADVANCE(118);
      END_STATE();
    case 25:
      if (lookahead == ' ') ADVANCE(25);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(103);
      END_STATE();
    case 26:
      if (lookahead == ' ') ADVANCE(27);
      if (lookahead == 'T') ADVANCE(101);
      if (lookahead == '^') ADVANCE(1);
      if (lookahead == '\'' ||
          lookahead == '(') ADVANCE(42);
      if (lookahead == ')' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9')) ADVANCE(2);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(102);
      END_STATE();
    case 27:
      if (lookahead == ' ') ADVANCE(27);
      if (lookahead == 'T') ADVANCE(101);
      if (lookahead == '\'' ||
          lookahead == '(') ADVANCE(42);
      if (lookahead == ')' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9')) ADVANCE(2);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(102);
      END_STATE();
    case 28:
      if (lookahead == ')') ADVANCE(104);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(28);
      END_STATE();
    case 29:
      if (lookahead == '*') ADVANCE(49);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(31);
      END_STATE();
    case 30:
      if (lookahead == '*') ADVANCE(98);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(30);
      END_STATE();
    case 31:
      if (lookahead == '*') ADVANCE(32);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(31);
      END_STATE();
    case 32:
      if (lookahead == '*') ADVANCE(97);
      END_STATE();
    case 33:
      if (lookahead == '*') ADVANCE(96);
      END_STATE();
    case 34:
      if (lookahead == '*') ADVANCE(37);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(34);
      if (lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(73);
      END_STATE();
    case 35:
      if (lookahead == '*') ADVANCE(36);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(35);
      END_STATE();
    case 36:
      if (lookahead == '*') ADVANCE(33);
      END_STATE();
    case 37:
      if (lookahead == '/') ADVANCE(89);
      END_STATE();
    case 38:
      if (lookahead == ':') ADVANCE(60);
      if (lookahead == ' ' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(38);
      END_STATE();
    case 39:
      if (lookahead == ']') ADVANCE(86);
      END_STATE();
    case 40:
      if (lookahead == '^') ADVANCE(1);
      if (lookahead == ' ' ||
          lookahead == '\'' ||
          lookahead == '(') ADVANCE(42);
      if (lookahead == ')' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z')) ADVANCE(2);
      END_STATE();
    case 41:
      if (lookahead == '_') ADVANCE(99);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(41);
      END_STATE();
    case 42:
      if (lookahead == ' ' ||
          lookahead == '\'' ||
          lookahead == '(') ADVANCE(42);
      if (lookahead == ')' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z')) ADVANCE(2);
      END_STATE();
    case 43:
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == ' ') SKIP(43);
      if ((0x0b <= lookahead && lookahead <= '\r')) ADVANCE(119);
      if (lookahead != 0) ADVANCE(120);
      END_STATE();
    case 44:
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') ADVANCE(82);
      if (lookahead != 0 &&
          lookahead != ')') ADVANCE(83);
      END_STATE();
    case 45:
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') ADVANCE(87);
      if (lookahead != 0 &&
          lookahead != ']') ADVANCE(88);
      END_STATE();
    case 46:
      if (('(' <= lookahead && lookahead <= '*') ||
          ('[' <= lookahead && lookahead <= ']') ||
          lookahead == '_') ADVANCE(95);
      END_STATE();
    case 47:
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(103);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          (lookahead < '(' || '*' < lookahead) &&
          lookahead != '\\' &&
          lookahead != '_') ADVANCE(118);
      END_STATE();
    case 48:
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != ')') ADVANCE(28);
      END_STATE();
    case 49:
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '*') ADVANCE(35);
      END_STATE();
    case 50:
      if (lookahead != 0 &&
          lookahead != '/') ADVANCE(91);
      END_STATE();
    case 51:
      if (eof) ADVANCE(53);
      if (lookahead == '\n') SKIP(51);
      if (lookahead == '(') ADVANCE(48);
      if (lookahead == '*') ADVANCE(105);
      if (lookahead == '.') ADVANCE(66);
      if (lookahead == '\\') ADVANCE(46);
      if (lookahead == '_') ADVANCE(106);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') ADVANCE(114);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(23);
      if (lookahead != 0 &&
          (lookahead < '(' || '*' < lookahead)) ADVANCE(118);
      END_STATE();
    case 52:
      if (eof) ADVANCE(53);
      if (lookahead == '\n') SKIP(52);
      if (lookahead == '(') ADVANCE(48);
      if (lookahead == '*') ADVANCE(105);
      if (lookahead == '.') ADVANCE(66);
      if (lookahead == '\\') ADVANCE(46);
      if (lookahead == '_') ADVANCE(106);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') ADVANCE(115);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(24);
      if (lookahead != 0 &&
          (lookahead < '(' || '*' < lookahead)) ADVANCE(118);
      END_STATE();
    case 53:
      ACCEPT_TOKEN(ts_builtin_sym_end);
      END_STATE();
    case 54:
      ACCEPT_TOKEN(anon_sym_LF);
      if (lookahead == '\n') ADVANCE(54);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') ADVANCE(109);
      END_STATE();
    case 55:
      ACCEPT_TOKEN(anon_sym_LF);
      if (lookahead == '\n') ADVANCE(55);
      if (lookahead == ' ') ADVANCE(62);
      if (('\t' <= lookahead && lookahead <= '\r')) ADVANCE(67);
      END_STATE();
    case 56:
      ACCEPT_TOKEN(anon_sym_LF);
      if (lookahead == '\n') ADVANCE(56);
      if (lookahead == ' ') ADVANCE(10);
      END_STATE();
    case 57:
      ACCEPT_TOKEN(anon_sym_LF);
      if (lookahead == '\n') ADVANCE(57);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') ADVANCE(68);
      END_STATE();
    case 58:
      ACCEPT_TOKEN(anon_sym_LF);
      if (lookahead == '\n') ADVANCE(58);
      if (lookahead == ' ') ADVANCE(63);
      END_STATE();
    case 59:
      ACCEPT_TOKEN(anon_sym_LF);
      if (lookahead == '\n') ADVANCE(59);
      if (lookahead == ' ') ADVANCE(79);
      END_STATE();
    case 60:
      ACCEPT_TOKEN(sym_title_key);
      if (lookahead == ' ') ADVANCE(61);
      END_STATE();
    case 61:
      ACCEPT_TOKEN(sym_title_key_with_space);
      END_STATE();
    case 62:
      ACCEPT_TOKEN(anon_sym_SPACE);
      if (lookahead == '\n') ADVANCE(55);
      if (lookahead == ' ') ADVANCE(62);
      if (('\t' <= lookahead && lookahead <= '\r')) ADVANCE(67);
      END_STATE();
    case 63:
      ACCEPT_TOKEN(anon_sym_SPACE);
      if (lookahead == '\n') ADVANCE(58);
      if (lookahead == ' ') ADVANCE(63);
      END_STATE();
    case 64:
      ACCEPT_TOKEN(anon_sym_DASH);
      END_STATE();
    case 65:
      ACCEPT_TOKEN(anon_sym_DOT);
      END_STATE();
    case 66:
      ACCEPT_TOKEN(anon_sym_DOT);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          (lookahead < '(' || '*' < lookahead) &&
          (lookahead < 'A' || 'Z' < lookahead) &&
          lookahead != '\\' &&
          lookahead != '_') ADVANCE(118);
      END_STATE();
    case 67:
      ACCEPT_TOKEN(sym_scene_location);
      if (lookahead == '\n') ADVANCE(55);
      if (lookahead == ' ') ADVANCE(62);
      if (('\t' <= lookahead && lookahead <= '\r')) ADVANCE(67);
      if (lookahead != 0 &&
          lookahead != '#' &&
          lookahead != '-') ADVANCE(69);
      END_STATE();
    case 68:
      ACCEPT_TOKEN(sym_scene_location);
      if (lookahead == '\n') ADVANCE(57);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') ADVANCE(68);
      if (lookahead != 0 &&
          lookahead != '#' &&
          lookahead != '-') ADVANCE(69);
      END_STATE();
    case 69:
      ACCEPT_TOKEN(sym_scene_location);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '#' &&
          lookahead != '-') ADVANCE(69);
      END_STATE();
    case 70:
      ACCEPT_TOKEN(sym_scene_time);
      if (lookahead == '\t' ||
          (0x0b <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') ADVANCE(70);
      if (lookahead != 0 &&
          (lookahead < '\t' || '\r' < lookahead) &&
          lookahead != '#') ADVANCE(71);
      END_STATE();
    case 71:
      ACCEPT_TOKEN(sym_scene_time);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '#') ADVANCE(71);
      END_STATE();
    case 72:
      ACCEPT_TOKEN(anon_sym_POUND);
      END_STATE();
    case 73:
      ACCEPT_TOKEN(aux_sym_scene_number_token1);
      if (lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(73);
      END_STATE();
    case 74:
      ACCEPT_TOKEN(aux_sym_character_token1);
      END_STATE();
    case 75:
      ACCEPT_TOKEN(aux_sym_character_token2);
      if (lookahead == '\t' ||
          (0x0b <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') ADVANCE(75);
      if (lookahead != 0 &&
          (lookahead < '\t' || '\r' < lookahead)) ADVANCE(76);
      END_STATE();
    case 76:
      ACCEPT_TOKEN(aux_sym_character_token2);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(76);
      END_STATE();
    case 77:
      ACCEPT_TOKEN(aux_sym_character_token3);
      END_STATE();
    case 78:
      ACCEPT_TOKEN(anon_sym_LF2);
      END_STATE();
    case 79:
      ACCEPT_TOKEN(aux_sym_parenthetical_token1);
      if (lookahead == '\n') ADVANCE(59);
      if (lookahead == ' ') ADVANCE(79);
      END_STATE();
    case 80:
      ACCEPT_TOKEN(aux_sym_parenthetical_token1);
      if (lookahead == ' ') ADVANCE(80);
      if (lookahead == '\t' ||
          (0x0b <= lookahead && lookahead <= '\r')) ADVANCE(111);
      END_STATE();
    case 81:
      ACCEPT_TOKEN(anon_sym_LPAREN);
      END_STATE();
    case 82:
      ACCEPT_TOKEN(aux_sym_parenthetical_token2);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') ADVANCE(82);
      if (lookahead != 0 &&
          lookahead != ')') ADVANCE(83);
      END_STATE();
    case 83:
      ACCEPT_TOKEN(aux_sym_parenthetical_token2);
      if (lookahead != 0 &&
          lookahead != ')') ADVANCE(83);
      END_STATE();
    case 84:
      ACCEPT_TOKEN(anon_sym_RPAREN);
      END_STATE();
    case 85:
      ACCEPT_TOKEN(aux_sym_transition_token1);
      END_STATE();
    case 86:
      ACCEPT_TOKEN(anon_sym_RBRACK_RBRACK);
      END_STATE();
    case 87:
      ACCEPT_TOKEN(sym_note_content);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') ADVANCE(87);
      if (lookahead != 0 &&
          lookahead != ']') ADVANCE(88);
      END_STATE();
    case 88:
      ACCEPT_TOKEN(sym_note_content);
      if (lookahead != 0 &&
          lookahead != ']') ADVANCE(88);
      END_STATE();
    case 89:
      ACCEPT_TOKEN(anon_sym_STAR_SLASH);
      END_STATE();
    case 90:
      ACCEPT_TOKEN(sym_boneyard_content);
      if (lookahead == '*') ADVANCE(50);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') ADVANCE(90);
      if (lookahead != 0) ADVANCE(91);
      END_STATE();
    case 91:
      ACCEPT_TOKEN(sym_boneyard_content);
      if (lookahead == '*') ADVANCE(50);
      if (lookahead != 0) ADVANCE(91);
      END_STATE();
    case 92:
      ACCEPT_TOKEN(sym_centered_text);
      if (lookahead == '\t' ||
          (0x0b <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') ADVANCE(92);
      if (lookahead != 0 &&
          (lookahead < '\t' || '\r' < lookahead) &&
          lookahead != '<') ADVANCE(93);
      END_STATE();
    case 93:
      ACCEPT_TOKEN(sym_centered_text);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '<') ADVANCE(93);
      END_STATE();
    case 94:
      ACCEPT_TOKEN(sym_centered_end);
      END_STATE();
    case 95:
      ACCEPT_TOKEN(sym_escaped_char);
      END_STATE();
    case 96:
      ACCEPT_TOKEN(sym_bold_italic);
      END_STATE();
    case 97:
      ACCEPT_TOKEN(sym_bold);
      END_STATE();
    case 98:
      ACCEPT_TOKEN(sym_italic);
      END_STATE();
    case 99:
      ACCEPT_TOKEN(sym_underline);
      END_STATE();
    case 100:
      ACCEPT_TOKEN(sym_uppercase_text);
      if (lookahead == '\n') ADVANCE(74);
      if (lookahead == ' ') ADVANCE(26);
      if (lookahead == ':') ADVANCE(85);
      if (lookahead == 'T') ADVANCE(101);
      if (lookahead == '\'' ||
          lookahead == '(') ADVANCE(42);
      if (lookahead == ')' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9')) ADVANCE(2);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(102);
      END_STATE();
    case 101:
      ACCEPT_TOKEN(sym_uppercase_text);
      if (lookahead == '\n') ADVANCE(74);
      if (lookahead == ' ') ADVANCE(26);
      if (lookahead == 'O') ADVANCE(100);
      if (lookahead == 'T') ADVANCE(101);
      if (lookahead == '\'' ||
          lookahead == '(') ADVANCE(42);
      if (lookahead == ')' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9')) ADVANCE(2);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(102);
      END_STATE();
    case 102:
      ACCEPT_TOKEN(sym_uppercase_text);
      if (lookahead == '\n') ADVANCE(74);
      if (lookahead == ' ') ADVANCE(26);
      if (lookahead == 'T') ADVANCE(101);
      if (lookahead == '\'' ||
          lookahead == '(') ADVANCE(42);
      if (lookahead == ')' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9')) ADVANCE(2);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(102);
      END_STATE();
    case 103:
      ACCEPT_TOKEN(sym_uppercase_text);
      if (lookahead == ' ') ADVANCE(25);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(103);
      END_STATE();
    case 104:
      ACCEPT_TOKEN(sym_paren_text);
      END_STATE();
    case 105:
      ACCEPT_TOKEN(sym_literal_char);
      if (lookahead == '*') ADVANCE(29);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(30);
      END_STATE();
    case 106:
      ACCEPT_TOKEN(sym_literal_char);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '_') ADVANCE(41);
      END_STATE();
    case 107:
      ACCEPT_TOKEN(sym_text);
      if (lookahead == '\n') ADVANCE(74);
      if (lookahead == ' ') ADVANCE(112);
      if (lookahead == '\'') ADVANCE(113);
      if (lookahead == '(') ADVANCE(42);
      if (lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9')) ADVANCE(107);
      if (lookahead == ')' ||
          ('A' <= lookahead && lookahead <= 'Z')) ADVANCE(2);
      if (lookahead != 0 &&
          (lookahead < '\'' || '*' < lookahead) &&
          lookahead != '\\' &&
          lookahead != '_') ADVANCE(118);
      END_STATE();
    case 108:
      ACCEPT_TOKEN(sym_text);
      if (lookahead == '\n') ADVANCE(74);
      if (lookahead != 0 &&
          (lookahead < '(' || '*' < lookahead) &&
          (lookahead < 'A' || 'Z' < lookahead) &&
          lookahead != '\\' &&
          lookahead != '_') ADVANCE(118);
      END_STATE();
    case 109:
      ACCEPT_TOKEN(sym_text);
      if (lookahead == '\n') ADVANCE(54);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') ADVANCE(109);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(47);
      if (lookahead != 0 &&
          (lookahead < '(' || '*' < lookahead) &&
          lookahead != '\\' &&
          lookahead != '_') ADVANCE(118);
      END_STATE();
    case 110:
      ACCEPT_TOKEN(sym_text);
      if (lookahead == ' ') ADVANCE(110);
      if (lookahead == '\'') ADVANCE(113);
      if (lookahead == '(') ADVANCE(42);
      if (lookahead == ')') ADVANCE(2);
      if (lookahead == 'T') ADVANCE(4);
      if (lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9')) ADVANCE(107);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(5);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          (lookahead < '\'' || '*' < lookahead) &&
          lookahead != '\\' &&
          lookahead != '_') ADVANCE(118);
      END_STATE();
    case 111:
      ACCEPT_TOKEN(sym_text);
      if (lookahead == ' ') ADVANCE(80);
      if (lookahead == '\t' ||
          (0x0b <= lookahead && lookahead <= '\r')) ADVANCE(111);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(47);
      if (lookahead != 0 &&
          (lookahead < '\t' || '\r' < lookahead) &&
          (lookahead < '(' || '*' < lookahead) &&
          lookahead != '\\' &&
          lookahead != '_') ADVANCE(118);
      END_STATE();
    case 112:
      ACCEPT_TOKEN(sym_text);
      if (lookahead == '(') ADVANCE(42);
      if (lookahead == '^') ADVANCE(108);
      if (lookahead == ' ' ||
          lookahead == '\'') ADVANCE(113);
      if (lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9')) ADVANCE(107);
      if (lookahead == ')' ||
          ('A' <= lookahead && lookahead <= 'Z')) ADVANCE(2);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          (lookahead < '\'' || '*' < lookahead) &&
          lookahead != '\\' &&
          lookahead != '^' &&
          lookahead != '_') ADVANCE(118);
      END_STATE();
    case 113:
      ACCEPT_TOKEN(sym_text);
      if (lookahead == '(') ADVANCE(42);
      if (lookahead == ' ' ||
          lookahead == '\'') ADVANCE(113);
      if (lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9')) ADVANCE(107);
      if (lookahead == ')' ||
          ('A' <= lookahead && lookahead <= 'Z')) ADVANCE(2);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          (lookahead < '\'' || '*' < lookahead) &&
          lookahead != '\\' &&
          lookahead != '_') ADVANCE(118);
      END_STATE();
    case 114:
      ACCEPT_TOKEN(sym_text);
      if (lookahead == '.') ADVANCE(66);
      if (lookahead == '\t' ||
          (0x0b <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') ADVANCE(114);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(23);
      if (lookahead != 0 &&
          (lookahead < '\t' || '\r' < lookahead) &&
          (lookahead < '(' || '*' < lookahead) &&
          lookahead != '\\' &&
          lookahead != '_') ADVANCE(118);
      END_STATE();
    case 115:
      ACCEPT_TOKEN(sym_text);
      if (lookahead == '.') ADVANCE(66);
      if (lookahead == '\t' ||
          (0x0b <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') ADVANCE(115);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(24);
      if (lookahead != 0 &&
          (lookahead < '\t' || '\r' < lookahead) &&
          (lookahead < '(' || '*' < lookahead) &&
          lookahead != '\\' &&
          lookahead != '_') ADVANCE(118);
      END_STATE();
    case 116:
      ACCEPT_TOKEN(sym_text);
      if (lookahead == ':') ADVANCE(60);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(38);
      if (lookahead == ' ' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(116);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          (lookahead < '(' || '*' < lookahead) &&
          lookahead != '\\' &&
          lookahead != '_') ADVANCE(118);
      END_STATE();
    case 117:
      ACCEPT_TOKEN(sym_text);
      if (lookahead == '\t' ||
          (0x0b <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') ADVANCE(117);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(47);
      if (lookahead != 0 &&
          (lookahead < '\t' || '\r' < lookahead) &&
          (lookahead < '(' || '*' < lookahead) &&
          lookahead != '\\' &&
          lookahead != '_') ADVANCE(118);
      END_STATE();
    case 118:
      ACCEPT_TOKEN(sym_text);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          (lookahead < '(' || '*' < lookahead) &&
          (lookahead < 'A' || 'Z' < lookahead) &&
          lookahead != '\\' &&
          lookahead != '_') ADVANCE(118);
      END_STATE();
    case 119:
      ACCEPT_TOKEN(sym_description);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(119);
      if ((0x0b <= lookahead && lookahead <= '\r')) ADVANCE(119);
      if (lookahead != 0 &&
          (lookahead < '\t' || '\r' < lookahead)) ADVANCE(120);
      END_STATE();
    case 120:
      ACCEPT_TOKEN(sym_description);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(120);
      END_STATE();
    default:
      return false;
  }
}

static const TSLexMode ts_lex_modes[STATE_COUNT] = {
  [0] = {.lex_state = 0, .external_lex_state = 1},
  [1] = {.lex_state = 51, .external_lex_state = 2},
  [2] = {.lex_state = 52, .external_lex_state = 2},
  [3] = {.lex_state = 52, .external_lex_state = 2},
  [4] = {.lex_state = 52, .external_lex_state = 2},
  [5] = {.lex_state = 52, .external_lex_state = 2},
  [6] = {.lex_state = 52, .external_lex_state = 2},
  [7] = {.lex_state = 52, .external_lex_state = 2},
  [8] = {.lex_state = 52, .external_lex_state = 2},
  [9] = {.lex_state = 52, .external_lex_state = 2},
  [10] = {.lex_state = 52, .external_lex_state = 2},
  [11] = {.lex_state = 52, .external_lex_state = 2},
  [12] = {.lex_state = 51, .external_lex_state = 3},
  [13] = {.lex_state = 51, .external_lex_state = 3},
  [14] = {.lex_state = 51, .external_lex_state = 3},
  [15] = {.lex_state = 51, .external_lex_state = 3},
  [16] = {.lex_state = 51, .external_lex_state = 2},
  [17] = {.lex_state = 51, .external_lex_state = 2},
  [18] = {.lex_state = 51, .external_lex_state = 3},
  [19] = {.lex_state = 52, .external_lex_state = 4},
  [20] = {.lex_state = 52, .external_lex_state = 4},
  [21] = {.lex_state = 52, .external_lex_state = 4},
  [22] = {.lex_state = 52, .external_lex_state = 4},
  [23] = {.lex_state = 52, .external_lex_state = 4},
  [24] = {.lex_state = 52, .external_lex_state = 4},
  [25] = {.lex_state = 52, .external_lex_state = 4},
  [26] = {.lex_state = 52, .external_lex_state = 2},
  [27] = {.lex_state = 52, .external_lex_state = 2},
  [28] = {.lex_state = 52, .external_lex_state = 2},
  [29] = {.lex_state = 52, .external_lex_state = 2},
  [30] = {.lex_state = 52, .external_lex_state = 2},
  [31] = {.lex_state = 52, .external_lex_state = 2},
  [32] = {.lex_state = 52, .external_lex_state = 2},
  [33] = {.lex_state = 52, .external_lex_state = 2},
  [34] = {.lex_state = 52, .external_lex_state = 2},
  [35] = {.lex_state = 52, .external_lex_state = 2},
  [36] = {.lex_state = 52, .external_lex_state = 2},
  [37] = {.lex_state = 52, .external_lex_state = 2},
  [38] = {.lex_state = 52, .external_lex_state = 2},
  [39] = {.lex_state = 52, .external_lex_state = 2},
  [40] = {.lex_state = 52, .external_lex_state = 2},
  [41] = {.lex_state = 52, .external_lex_state = 2},
  [42] = {.lex_state = 52, .external_lex_state = 2},
  [43] = {.lex_state = 52, .external_lex_state = 2},
  [44] = {.lex_state = 6},
  [45] = {.lex_state = 7},
  [46] = {.lex_state = 7},
  [47] = {.lex_state = 8},
  [48] = {.lex_state = 8},
  [49] = {.lex_state = 9},
  [50] = {.lex_state = 15},
  [51] = {.lex_state = 11},
  [52] = {.lex_state = 11},
  [53] = {.lex_state = 11},
  [54] = {.lex_state = 11},
  [55] = {.lex_state = 11},
  [56] = {.lex_state = 16},
  [57] = {.lex_state = 0, .external_lex_state = 5},
  [58] = {.lex_state = 17},
  [59] = {.lex_state = 17},
  [60] = {.lex_state = 0, .external_lex_state = 6},
  [61] = {.lex_state = 11},
  [62] = {.lex_state = 34},
  [63] = {.lex_state = 0, .external_lex_state = 6},
  [64] = {.lex_state = 0, .external_lex_state = 6},
  [65] = {.lex_state = 11},
  [66] = {.lex_state = 11},
  [67] = {.lex_state = 0},
  [68] = {.lex_state = 11},
  [69] = {.lex_state = 11},
  [70] = {.lex_state = 11},
  [71] = {.lex_state = 11},
  [72] = {.lex_state = 11},
  [73] = {.lex_state = 11},
  [74] = {.lex_state = 0},
  [75] = {.lex_state = 44},
  [76] = {.lex_state = 0},
  [77] = {.lex_state = 43},
  [78] = {.lex_state = 11},
  [79] = {.lex_state = 34},
  [80] = {.lex_state = 11},
  [81] = {.lex_state = 12},
  [82] = {.lex_state = 12},
  [83] = {.lex_state = 11},
  [84] = {.lex_state = 11},
  [85] = {.lex_state = 11},
  [86] = {.lex_state = 0},
  [87] = {.lex_state = 11},
  [88] = {.lex_state = 11},
  [89] = {.lex_state = 0, .external_lex_state = 6},
  [90] = {.lex_state = 43},
  [91] = {.lex_state = 11},
  [92] = {.lex_state = 90},
  [93] = {.lex_state = 44},
  [94] = {.lex_state = 0},
  [95] = {.lex_state = 13},
  [96] = {.lex_state = 11},
  [97] = {.lex_state = 14},
  [98] = {.lex_state = 11},
  [99] = {.lex_state = 0},
  [100] = {.lex_state = 0},
  [101] = {.lex_state = 11},
  [102] = {.lex_state = 13},
  [103] = {.lex_state = 11},
  [104] = {.lex_state = 12},
  [105] = {.lex_state = 13},
  [106] = {.lex_state = 11},
  [107] = {.lex_state = 13},
  [108] = {.lex_state = 13},
  [109] = {.lex_state = 11},
  [110] = {.lex_state = 45},
};

static const uint16_t ts_parse_table[LARGE_STATE_COUNT][SYMBOL_COUNT] = {
  [0] = {
    [ts_builtin_sym_end] = ACTIONS(1),
    [sym_title_key] = ACTIONS(1),
    [sym_title_key_with_space] = ACTIONS(1),
    [anon_sym_DASH] = ACTIONS(1),
    [anon_sym_DOT] = ACTIONS(1),
    [anon_sym_POUND] = ACTIONS(1),
    [aux_sym_character_token1] = ACTIONS(1),
    [aux_sym_character_token3] = ACTIONS(1),
    [anon_sym_LPAREN] = ACTIONS(1),
    [anon_sym_RPAREN] = ACTIONS(1),
    [aux_sym_transition_token1] = ACTIONS(1),
    [anon_sym_RBRACK_RBRACK] = ACTIONS(1),
    [sym_centered_end] = ACTIONS(1),
    [sym_escaped_char] = ACTIONS(1),
    [sym_bold_italic] = ACTIONS(1),
    [sym_bold] = ACTIONS(1),
    [sym_italic] = ACTIONS(1),
    [sym_underline] = ACTIONS(1),
    [sym_uppercase_text] = ACTIONS(1),
    [sym_literal_char] = ACTIONS(1),
    [sym_scene_start] = ACTIONS(1),
    [sym_section_start] = ACTIONS(1),
    [sym_note_start] = ACTIONS(1),
    [sym_forced_action_start] = ACTIONS(1),
    [sym_forced_character_start] = ACTIONS(1),
    [sym_forced_transition_start] = ACTIONS(1),
    [sym_lyric_start] = ACTIONS(1),
    [sym_centered_start] = ACTIONS(1),
    [sym_page_break_marker] = ACTIONS(1),
    [sym_synopsis_start] = ACTIONS(1),
    [sym_boneyard_start] = ACTIONS(1),
    [sym_title_continuation] = ACTIONS(1),
    [sym_blank_line] = ACTIONS(1),
    [sym_dialogue_line_start] = ACTIONS(1),
  },
  [1] = {
    [sym_document] = STATE(86),
    [sym_title_page] = STATE(5),
    [sym__element] = STATE(3),
    [sym_section_block] = STATE(3),
    [sym_scene_block] = STATE(3),
    [sym_title_page_field] = STATE(16),
    [sym_scene_heading] = STATE(9),
    [sym_character] = STATE(60),
    [sym_dialogue_block] = STATE(3),
    [sym_action] = STATE(3),
    [sym_transition] = STATE(3),
    [sym_section_heading] = STATE(8),
    [sym_note] = STATE(3),
    [sym_boneyard] = STATE(3),
    [sym_page_break] = STATE(3),
    [sym_synopsis] = STATE(3),
    [sym_lyric] = STATE(3),
    [sym_centered] = STATE(3),
    [sym__action_inline_content] = STATE(46),
    [aux_sym_document_repeat1] = STATE(3),
    [aux_sym_title_page_repeat1] = STATE(16),
    [aux_sym_action_repeat1] = STATE(46),
    [ts_builtin_sym_end] = ACTIONS(3),
    [sym_title_key] = ACTIONS(5),
    [sym_title_key_with_space] = ACTIONS(7),
    [anon_sym_DOT] = ACTIONS(9),
    [aux_sym_character_token1] = ACTIONS(11),
    [aux_sym_transition_token1] = ACTIONS(13),
    [sym_escaped_char] = ACTIONS(15),
    [sym_bold_italic] = ACTIONS(15),
    [sym_bold] = ACTIONS(15),
    [sym_italic] = ACTIONS(15),
    [sym_underline] = ACTIONS(15),
    [sym_uppercase_text] = ACTIONS(15),
    [sym_paren_text] = ACTIONS(15),
    [sym_literal_char] = ACTIONS(15),
    [sym_text] = ACTIONS(15),
    [sym_scene_start] = ACTIONS(17),
    [sym_section_start] = ACTIONS(19),
    [sym_note_start] = ACTIONS(21),
    [sym_forced_action_start] = ACTIONS(23),
    [sym_forced_character_start] = ACTIONS(25),
    [sym_forced_transition_start] = ACTIONS(27),
    [sym_lyric_start] = ACTIONS(29),
    [sym_centered_start] = ACTIONS(31),
    [sym_page_break_marker] = ACTIONS(33),
    [sym_synopsis_start] = ACTIONS(35),
    [sym_boneyard_start] = ACTIONS(37),
  },
  [2] = {
    [sym__element] = STATE(2),
    [sym_section_block] = STATE(2),
    [sym_scene_block] = STATE(2),
    [sym_scene_heading] = STATE(9),
    [sym_character] = STATE(60),
    [sym_dialogue_block] = STATE(2),
    [sym_action] = STATE(2),
    [sym_transition] = STATE(2),
    [sym_section_heading] = STATE(8),
    [sym_note] = STATE(2),
    [sym_boneyard] = STATE(2),
    [sym_page_break] = STATE(2),
    [sym_synopsis] = STATE(2),
    [sym_lyric] = STATE(2),
    [sym_centered] = STATE(2),
    [sym__action_inline_content] = STATE(46),
    [aux_sym_document_repeat1] = STATE(2),
    [aux_sym_action_repeat1] = STATE(46),
    [ts_builtin_sym_end] = ACTIONS(39),
    [anon_sym_DOT] = ACTIONS(41),
    [aux_sym_character_token1] = ACTIONS(44),
    [aux_sym_transition_token1] = ACTIONS(47),
    [sym_escaped_char] = ACTIONS(50),
    [sym_bold_italic] = ACTIONS(50),
    [sym_bold] = ACTIONS(50),
    [sym_italic] = ACTIONS(50),
    [sym_underline] = ACTIONS(50),
    [sym_uppercase_text] = ACTIONS(50),
    [sym_paren_text] = ACTIONS(50),
    [sym_literal_char] = ACTIONS(50),
    [sym_text] = ACTIONS(50),
    [sym_scene_start] = ACTIONS(53),
    [sym_section_start] = ACTIONS(56),
    [sym_note_start] = ACTIONS(59),
    [sym_forced_action_start] = ACTIONS(62),
    [sym_forced_character_start] = ACTIONS(65),
    [sym_forced_transition_start] = ACTIONS(68),
    [sym_lyric_start] = ACTIONS(71),
    [sym_centered_start] = ACTIONS(74),
    [sym_page_break_marker] = ACTIONS(77),
    [sym_synopsis_start] = ACTIONS(80),
    [sym_boneyard_start] = ACTIONS(83),
  },
  [3] = {
    [sym__element] = STATE(2),
    [sym_section_block] = STATE(2),
    [sym_scene_block] = STATE(2),
    [sym_scene_heading] = STATE(9),
    [sym_character] = STATE(60),
    [sym_dialogue_block] = STATE(2),
    [sym_action] = STATE(2),
    [sym_transition] = STATE(2),
    [sym_section_heading] = STATE(8),
    [sym_note] = STATE(2),
    [sym_boneyard] = STATE(2),
    [sym_page_break] = STATE(2),
    [sym_synopsis] = STATE(2),
    [sym_lyric] = STATE(2),
    [sym_centered] = STATE(2),
    [sym__action_inline_content] = STATE(46),
    [aux_sym_document_repeat1] = STATE(2),
    [aux_sym_action_repeat1] = STATE(46),
    [ts_builtin_sym_end] = ACTIONS(86),
    [anon_sym_DOT] = ACTIONS(9),
    [aux_sym_character_token1] = ACTIONS(11),
    [aux_sym_transition_token1] = ACTIONS(13),
    [sym_escaped_char] = ACTIONS(15),
    [sym_bold_italic] = ACTIONS(15),
    [sym_bold] = ACTIONS(15),
    [sym_italic] = ACTIONS(15),
    [sym_underline] = ACTIONS(15),
    [sym_uppercase_text] = ACTIONS(15),
    [sym_paren_text] = ACTIONS(15),
    [sym_literal_char] = ACTIONS(15),
    [sym_text] = ACTIONS(15),
    [sym_scene_start] = ACTIONS(17),
    [sym_section_start] = ACTIONS(19),
    [sym_note_start] = ACTIONS(21),
    [sym_forced_action_start] = ACTIONS(23),
    [sym_forced_character_start] = ACTIONS(25),
    [sym_forced_transition_start] = ACTIONS(27),
    [sym_lyric_start] = ACTIONS(29),
    [sym_centered_start] = ACTIONS(31),
    [sym_page_break_marker] = ACTIONS(33),
    [sym_synopsis_start] = ACTIONS(35),
    [sym_boneyard_start] = ACTIONS(37),
  },
  [4] = {
    [sym__element] = STATE(2),
    [sym_section_block] = STATE(2),
    [sym_scene_block] = STATE(2),
    [sym_scene_heading] = STATE(9),
    [sym_character] = STATE(60),
    [sym_dialogue_block] = STATE(2),
    [sym_action] = STATE(2),
    [sym_transition] = STATE(2),
    [sym_section_heading] = STATE(8),
    [sym_note] = STATE(2),
    [sym_boneyard] = STATE(2),
    [sym_page_break] = STATE(2),
    [sym_synopsis] = STATE(2),
    [sym_lyric] = STATE(2),
    [sym_centered] = STATE(2),
    [sym__action_inline_content] = STATE(46),
    [aux_sym_document_repeat1] = STATE(2),
    [aux_sym_action_repeat1] = STATE(46),
    [ts_builtin_sym_end] = ACTIONS(88),
    [anon_sym_DOT] = ACTIONS(9),
    [aux_sym_character_token1] = ACTIONS(11),
    [aux_sym_transition_token1] = ACTIONS(13),
    [sym_escaped_char] = ACTIONS(15),
    [sym_bold_italic] = ACTIONS(15),
    [sym_bold] = ACTIONS(15),
    [sym_italic] = ACTIONS(15),
    [sym_underline] = ACTIONS(15),
    [sym_uppercase_text] = ACTIONS(15),
    [sym_paren_text] = ACTIONS(15),
    [sym_literal_char] = ACTIONS(15),
    [sym_text] = ACTIONS(15),
    [sym_scene_start] = ACTIONS(17),
    [sym_section_start] = ACTIONS(19),
    [sym_note_start] = ACTIONS(21),
    [sym_forced_action_start] = ACTIONS(23),
    [sym_forced_character_start] = ACTIONS(25),
    [sym_forced_transition_start] = ACTIONS(27),
    [sym_lyric_start] = ACTIONS(29),
    [sym_centered_start] = ACTIONS(31),
    [sym_page_break_marker] = ACTIONS(33),
    [sym_synopsis_start] = ACTIONS(35),
    [sym_boneyard_start] = ACTIONS(37),
  },
  [5] = {
    [sym__element] = STATE(4),
    [sym_section_block] = STATE(4),
    [sym_scene_block] = STATE(4),
    [sym_scene_heading] = STATE(9),
    [sym_character] = STATE(60),
    [sym_dialogue_block] = STATE(4),
    [sym_action] = STATE(4),
    [sym_transition] = STATE(4),
    [sym_section_heading] = STATE(8),
    [sym_note] = STATE(4),
    [sym_boneyard] = STATE(4),
    [sym_page_break] = STATE(4),
    [sym_synopsis] = STATE(4),
    [sym_lyric] = STATE(4),
    [sym_centered] = STATE(4),
    [sym__action_inline_content] = STATE(46),
    [aux_sym_document_repeat1] = STATE(4),
    [aux_sym_action_repeat1] = STATE(46),
    [ts_builtin_sym_end] = ACTIONS(86),
    [anon_sym_DOT] = ACTIONS(9),
    [aux_sym_character_token1] = ACTIONS(11),
    [aux_sym_transition_token1] = ACTIONS(13),
    [sym_escaped_char] = ACTIONS(15),
    [sym_bold_italic] = ACTIONS(15),
    [sym_bold] = ACTIONS(15),
    [sym_italic] = ACTIONS(15),
    [sym_underline] = ACTIONS(15),
    [sym_uppercase_text] = ACTIONS(15),
    [sym_paren_text] = ACTIONS(15),
    [sym_literal_char] = ACTIONS(15),
    [sym_text] = ACTIONS(15),
    [sym_scene_start] = ACTIONS(17),
    [sym_section_start] = ACTIONS(19),
    [sym_note_start] = ACTIONS(21),
    [sym_forced_action_start] = ACTIONS(23),
    [sym_forced_character_start] = ACTIONS(25),
    [sym_forced_transition_start] = ACTIONS(27),
    [sym_lyric_start] = ACTIONS(29),
    [sym_centered_start] = ACTIONS(31),
    [sym_page_break_marker] = ACTIONS(33),
    [sym_synopsis_start] = ACTIONS(35),
    [sym_boneyard_start] = ACTIONS(37),
  },
};

static const uint16_t ts_small_parse_table[] = {
  [0] = 19,
    ACTIONS(92), 1,
      anon_sym_DOT,
    ACTIONS(95), 1,
      aux_sym_character_token1,
    ACTIONS(98), 1,
      aux_sym_transition_token1,
    ACTIONS(104), 1,
      sym_scene_start,
    ACTIONS(107), 1,
      sym_note_start,
    ACTIONS(110), 1,
      sym_forced_action_start,
    ACTIONS(113), 1,
      sym_forced_character_start,
    ACTIONS(116), 1,
      sym_forced_transition_start,
    ACTIONS(119), 1,
      sym_lyric_start,
    ACTIONS(122), 1,
      sym_centered_start,
    ACTIONS(125), 1,
      sym_page_break_marker,
    ACTIONS(128), 1,
      sym_synopsis_start,
    ACTIONS(131), 1,
      sym_boneyard_start,
    STATE(9), 1,
      sym_scene_heading,
    STATE(60), 1,
      sym_character,
    ACTIONS(90), 2,
      sym_section_start,
      ts_builtin_sym_end,
    STATE(46), 2,
      sym__action_inline_content,
      aux_sym_action_repeat1,
    ACTIONS(101), 9,
      sym_escaped_char,
      sym_bold_italic,
      sym_bold,
      sym_italic,
      sym_underline,
      sym_uppercase_text,
      sym_paren_text,
      sym_literal_char,
      sym_text,
    STATE(6), 11,
      sym_scene_block,
      sym_dialogue_block,
      sym_action,
      sym_transition,
      sym_note,
      sym_boneyard,
      sym_page_break,
      sym_synopsis,
      sym_lyric,
      sym_centered,
      aux_sym_section_block_repeat1,
  [78] = 19,
    ACTIONS(9), 1,
      anon_sym_DOT,
    ACTIONS(11), 1,
      aux_sym_character_token1,
    ACTIONS(13), 1,
      aux_sym_transition_token1,
    ACTIONS(17), 1,
      sym_scene_start,
    ACTIONS(21), 1,
      sym_note_start,
    ACTIONS(23), 1,
      sym_forced_action_start,
    ACTIONS(25), 1,
      sym_forced_character_start,
    ACTIONS(27), 1,
      sym_forced_transition_start,
    ACTIONS(29), 1,
      sym_lyric_start,
    ACTIONS(31), 1,
      sym_centered_start,
    ACTIONS(33), 1,
      sym_page_break_marker,
    ACTIONS(35), 1,
      sym_synopsis_start,
    ACTIONS(37), 1,
      sym_boneyard_start,
    STATE(9), 1,
      sym_scene_heading,
    STATE(60), 1,
      sym_character,
    ACTIONS(134), 2,
      sym_section_start,
      ts_builtin_sym_end,
    STATE(46), 2,
      sym__action_inline_content,
      aux_sym_action_repeat1,
    ACTIONS(15), 9,
      sym_escaped_char,
      sym_bold_italic,
      sym_bold,
      sym_italic,
      sym_underline,
      sym_uppercase_text,
      sym_paren_text,
      sym_literal_char,
      sym_text,
    STATE(6), 11,
      sym_scene_block,
      sym_dialogue_block,
      sym_action,
      sym_transition,
      sym_note,
      sym_boneyard,
      sym_page_break,
      sym_synopsis,
      sym_lyric,
      sym_centered,
      aux_sym_section_block_repeat1,
  [156] = 19,
    ACTIONS(9), 1,
      anon_sym_DOT,
    ACTIONS(11), 1,
      aux_sym_character_token1,
    ACTIONS(13), 1,
      aux_sym_transition_token1,
    ACTIONS(17), 1,
      sym_scene_start,
    ACTIONS(21), 1,
      sym_note_start,
    ACTIONS(23), 1,
      sym_forced_action_start,
    ACTIONS(25), 1,
      sym_forced_character_start,
    ACTIONS(27), 1,
      sym_forced_transition_start,
    ACTIONS(29), 1,
      sym_lyric_start,
    ACTIONS(31), 1,
      sym_centered_start,
    ACTIONS(33), 1,
      sym_page_break_marker,
    ACTIONS(35), 1,
      sym_synopsis_start,
    ACTIONS(37), 1,
      sym_boneyard_start,
    STATE(9), 1,
      sym_scene_heading,
    STATE(60), 1,
      sym_character,
    ACTIONS(136), 2,
      sym_section_start,
      ts_builtin_sym_end,
    STATE(46), 2,
      sym__action_inline_content,
      aux_sym_action_repeat1,
    ACTIONS(15), 9,
      sym_escaped_char,
      sym_bold_italic,
      sym_bold,
      sym_italic,
      sym_underline,
      sym_uppercase_text,
      sym_paren_text,
      sym_literal_char,
      sym_text,
    STATE(7), 11,
      sym_scene_block,
      sym_dialogue_block,
      sym_action,
      sym_transition,
      sym_note,
      sym_boneyard,
      sym_page_break,
      sym_synopsis,
      sym_lyric,
      sym_centered,
      aux_sym_section_block_repeat1,
  [234] = 16,
    ACTIONS(140), 1,
      anon_sym_DOT,
    ACTIONS(142), 1,
      aux_sym_character_token1,
    ACTIONS(145), 1,
      aux_sym_transition_token1,
    ACTIONS(151), 1,
      sym_note_start,
    ACTIONS(154), 1,
      sym_forced_action_start,
    ACTIONS(157), 1,
      sym_forced_character_start,
    ACTIONS(160), 1,
      sym_forced_transition_start,
    ACTIONS(163), 1,
      sym_lyric_start,
    ACTIONS(166), 1,
      sym_centered_start,
    ACTIONS(169), 1,
      sym_synopsis_start,
    ACTIONS(172), 1,
      sym_boneyard_start,
    STATE(60), 1,
      sym_character,
    STATE(46), 2,
      sym__action_inline_content,
      aux_sym_action_repeat1,
    ACTIONS(138), 4,
      sym_scene_start,
      sym_section_start,
      sym_page_break_marker,
      ts_builtin_sym_end,
    ACTIONS(148), 9,
      sym_escaped_char,
      sym_bold_italic,
      sym_bold,
      sym_italic,
      sym_underline,
      sym_uppercase_text,
      sym_paren_text,
      sym_literal_char,
      sym_text,
    STATE(10), 10,
      sym__scene_content,
      sym_dialogue_block,
      sym_action,
      sym_transition,
      sym_note,
      sym_boneyard,
      sym_synopsis,
      sym_lyric,
      sym_centered,
      aux_sym_scene_block_repeat1,
  [304] = 16,
    ACTIONS(177), 1,
      anon_sym_DOT,
    ACTIONS(179), 1,
      aux_sym_character_token1,
    ACTIONS(182), 1,
      aux_sym_transition_token1,
    ACTIONS(188), 1,
      sym_note_start,
    ACTIONS(191), 1,
      sym_forced_action_start,
    ACTIONS(194), 1,
      sym_forced_character_start,
    ACTIONS(197), 1,
      sym_forced_transition_start,
    ACTIONS(200), 1,
      sym_lyric_start,
    ACTIONS(203), 1,
      sym_centered_start,
    ACTIONS(206), 1,
      sym_synopsis_start,
    ACTIONS(209), 1,
      sym_boneyard_start,
    STATE(60), 1,
      sym_character,
    STATE(46), 2,
      sym__action_inline_content,
      aux_sym_action_repeat1,
    ACTIONS(175), 4,
      sym_scene_start,
      sym_section_start,
      sym_page_break_marker,
      ts_builtin_sym_end,
    ACTIONS(185), 9,
      sym_escaped_char,
      sym_bold_italic,
      sym_bold,
      sym_italic,
      sym_underline,
      sym_uppercase_text,
      sym_paren_text,
      sym_literal_char,
      sym_text,
    STATE(11), 10,
      sym__scene_content,
      sym_dialogue_block,
      sym_action,
      sym_transition,
      sym_note,
      sym_boneyard,
      sym_synopsis,
      sym_lyric,
      sym_centered,
      aux_sym_scene_block_repeat1,
  [374] = 16,
    ACTIONS(214), 1,
      anon_sym_DOT,
    ACTIONS(216), 1,
      aux_sym_character_token1,
    ACTIONS(219), 1,
      aux_sym_transition_token1,
    ACTIONS(225), 1,
      sym_note_start,
    ACTIONS(228), 1,
      sym_forced_action_start,
    ACTIONS(231), 1,
      sym_forced_character_start,
    ACTIONS(234), 1,
      sym_forced_transition_start,
    ACTIONS(237), 1,
      sym_lyric_start,
    ACTIONS(240), 1,
      sym_centered_start,
    ACTIONS(243), 1,
      sym_synopsis_start,
    ACTIONS(246), 1,
      sym_boneyard_start,
    STATE(60), 1,
      sym_character,
    STATE(46), 2,
      sym__action_inline_content,
      aux_sym_action_repeat1,
    ACTIONS(212), 4,
      sym_scene_start,
      sym_section_start,
      sym_page_break_marker,
      ts_builtin_sym_end,
    ACTIONS(222), 9,
      sym_escaped_char,
      sym_bold_italic,
      sym_bold,
      sym_italic,
      sym_underline,
      sym_uppercase_text,
      sym_paren_text,
      sym_literal_char,
      sym_text,
    STATE(11), 10,
      sym__scene_content,
      sym_dialogue_block,
      sym_action,
      sym_transition,
      sym_note,
      sym_boneyard,
      sym_synopsis,
      sym_lyric,
      sym_centered,
      aux_sym_scene_block_repeat1,
  [444] = 4,
    ACTIONS(253), 1,
      sym_title_continuation,
    STATE(12), 1,
      aux_sym_title_page_field_repeat1,
    ACTIONS(249), 12,
      sym_scene_start,
      sym_section_start,
      sym_note_start,
      sym_forced_action_start,
      sym_forced_character_start,
      sym_forced_transition_start,
      sym_lyric_start,
      sym_centered_start,
      sym_page_break_marker,
      sym_synopsis_start,
      sym_boneyard_start,
      ts_builtin_sym_end,
    ACTIONS(251), 14,
      sym_title_key,
      sym_title_key_with_space,
      anon_sym_DOT,
      aux_sym_character_token1,
      aux_sym_transition_token1,
      sym_escaped_char,
      sym_bold_italic,
      sym_bold,
      sym_italic,
      sym_underline,
      sym_uppercase_text,
      sym_paren_text,
      sym_literal_char,
      sym_text,
  [481] = 4,
    ACTIONS(260), 1,
      sym_title_continuation,
    STATE(12), 1,
      aux_sym_title_page_field_repeat1,
    ACTIONS(256), 12,
      sym_scene_start,
      sym_section_start,
      sym_note_start,
      sym_forced_action_start,
      sym_forced_character_start,
      sym_forced_transition_start,
      sym_lyric_start,
      sym_centered_start,
      sym_page_break_marker,
      sym_synopsis_start,
      sym_boneyard_start,
      ts_builtin_sym_end,
    ACTIONS(258), 14,
      sym_title_key,
      sym_title_key_with_space,
      anon_sym_DOT,
      aux_sym_character_token1,
      aux_sym_transition_token1,
      sym_escaped_char,
      sym_bold_italic,
      sym_bold,
      sym_italic,
      sym_underline,
      sym_uppercase_text,
      sym_paren_text,
      sym_literal_char,
      sym_text,
  [518] = 4,
    ACTIONS(260), 1,
      sym_title_continuation,
    STATE(15), 1,
      aux_sym_title_page_field_repeat1,
    ACTIONS(256), 12,
      sym_scene_start,
      sym_section_start,
      sym_note_start,
      sym_forced_action_start,
      sym_forced_character_start,
      sym_forced_transition_start,
      sym_lyric_start,
      sym_centered_start,
      sym_page_break_marker,
      sym_synopsis_start,
      sym_boneyard_start,
      ts_builtin_sym_end,
    ACTIONS(258), 14,
      sym_title_key,
      sym_title_key_with_space,
      anon_sym_DOT,
      aux_sym_character_token1,
      aux_sym_transition_token1,
      sym_escaped_char,
      sym_bold_italic,
      sym_bold,
      sym_italic,
      sym_underline,
      sym_uppercase_text,
      sym_paren_text,
      sym_literal_char,
      sym_text,
  [555] = 4,
    ACTIONS(260), 1,
      sym_title_continuation,
    STATE(12), 1,
      aux_sym_title_page_field_repeat1,
    ACTIONS(262), 12,
      sym_scene_start,
      sym_section_start,
      sym_note_start,
      sym_forced_action_start,
      sym_forced_character_start,
      sym_forced_transition_start,
      sym_lyric_start,
      sym_centered_start,
      sym_page_break_marker,
      sym_synopsis_start,
      sym_boneyard_start,
      ts_builtin_sym_end,
    ACTIONS(264), 14,
      sym_title_key,
      sym_title_key_with_space,
      anon_sym_DOT,
      aux_sym_character_token1,
      aux_sym_transition_token1,
      sym_escaped_char,
      sym_bold_italic,
      sym_bold,
      sym_italic,
      sym_underline,
      sym_uppercase_text,
      sym_paren_text,
      sym_literal_char,
      sym_text,
  [592] = 5,
    ACTIONS(5), 1,
      sym_title_key,
    ACTIONS(7), 1,
      sym_title_key_with_space,
    STATE(17), 2,
      sym_title_page_field,
      aux_sym_title_page_repeat1,
    ACTIONS(266), 12,
      sym_scene_start,
      sym_section_start,
      sym_note_start,
      sym_forced_action_start,
      sym_forced_character_start,
      sym_forced_transition_start,
      sym_lyric_start,
      sym_centered_start,
      sym_page_break_marker,
      sym_synopsis_start,
      sym_boneyard_start,
      ts_builtin_sym_end,
    ACTIONS(268), 12,
      anon_sym_DOT,
      aux_sym_character_token1,
      aux_sym_transition_token1,
      sym_escaped_char,
      sym_bold_italic,
      sym_bold,
      sym_italic,
      sym_underline,
      sym_uppercase_text,
      sym_paren_text,
      sym_literal_char,
      sym_text,
  [631] = 5,
    ACTIONS(272), 1,
      sym_title_key,
    ACTIONS(275), 1,
      sym_title_key_with_space,
    STATE(17), 2,
      sym_title_page_field,
      aux_sym_title_page_repeat1,
    ACTIONS(270), 12,
      sym_scene_start,
      sym_section_start,
      sym_note_start,
      sym_forced_action_start,
      sym_forced_character_start,
      sym_forced_transition_start,
      sym_lyric_start,
      sym_centered_start,
      sym_page_break_marker,
      sym_synopsis_start,
      sym_boneyard_start,
      ts_builtin_sym_end,
    ACTIONS(278), 12,
      anon_sym_DOT,
      aux_sym_character_token1,
      aux_sym_transition_token1,
      sym_escaped_char,
      sym_bold_italic,
      sym_bold,
      sym_italic,
      sym_underline,
      sym_uppercase_text,
      sym_paren_text,
      sym_literal_char,
      sym_text,
  [670] = 2,
    ACTIONS(249), 13,
      sym_scene_start,
      sym_section_start,
      sym_note_start,
      sym_forced_action_start,
      sym_forced_character_start,
      sym_forced_transition_start,
      sym_lyric_start,
      sym_centered_start,
      sym_page_break_marker,
      sym_synopsis_start,
      sym_boneyard_start,
      sym_title_continuation,
      ts_builtin_sym_end,
    ACTIONS(251), 14,
      sym_title_key,
      sym_title_key_with_space,
      anon_sym_DOT,
      aux_sym_character_token1,
      aux_sym_transition_token1,
      sym_escaped_char,
      sym_bold_italic,
      sym_bold,
      sym_italic,
      sym_underline,
      sym_uppercase_text,
      sym_paren_text,
      sym_literal_char,
      sym_text,
  [702] = 4,
    ACTIONS(284), 1,
      sym_dialogue_line_start,
    STATE(19), 1,
      aux_sym_dialogue_block_repeat1,
    ACTIONS(280), 12,
      sym_scene_start,
      sym_section_start,
      sym_note_start,
      sym_forced_action_start,
      sym_forced_character_start,
      sym_forced_transition_start,
      sym_lyric_start,
      sym_centered_start,
      sym_page_break_marker,
      sym_synopsis_start,
      sym_boneyard_start,
      ts_builtin_sym_end,
    ACTIONS(282), 12,
      anon_sym_DOT,
      aux_sym_character_token1,
      aux_sym_transition_token1,
      sym_escaped_char,
      sym_bold_italic,
      sym_bold,
      sym_italic,
      sym_underline,
      sym_uppercase_text,
      sym_paren_text,
      sym_literal_char,
      sym_text,
  [737] = 4,
    ACTIONS(291), 1,
      sym_dialogue_line_start,
    STATE(19), 1,
      aux_sym_dialogue_block_repeat1,
    ACTIONS(287), 12,
      sym_scene_start,
      sym_section_start,
      sym_note_start,
      sym_forced_action_start,
      sym_forced_character_start,
      sym_forced_transition_start,
      sym_lyric_start,
      sym_centered_start,
      sym_page_break_marker,
      sym_synopsis_start,
      sym_boneyard_start,
      ts_builtin_sym_end,
    ACTIONS(289), 12,
      anon_sym_DOT,
      aux_sym_character_token1,
      aux_sym_transition_token1,
      sym_escaped_char,
      sym_bold_italic,
      sym_bold,
      sym_italic,
      sym_underline,
      sym_uppercase_text,
      sym_paren_text,
      sym_literal_char,
      sym_text,
  [772] = 2,
    ACTIONS(295), 12,
      anon_sym_DOT,
      aux_sym_character_token1,
      aux_sym_transition_token1,
      sym_escaped_char,
      sym_bold_italic,
      sym_bold,
      sym_italic,
      sym_underline,
      sym_uppercase_text,
      sym_paren_text,
      sym_literal_char,
      sym_text,
    ACTIONS(293), 13,
      sym_scene_start,
      sym_section_start,
      sym_note_start,
      sym_forced_action_start,
      sym_forced_character_start,
      sym_forced_transition_start,
      sym_lyric_start,
      sym_centered_start,
      sym_page_break_marker,
      sym_synopsis_start,
      sym_boneyard_start,
      sym_dialogue_line_start,
      ts_builtin_sym_end,
  [802] = 2,
    ACTIONS(282), 12,
      anon_sym_DOT,
      aux_sym_character_token1,
      aux_sym_transition_token1,
      sym_escaped_char,
      sym_bold_italic,
      sym_bold,
      sym_italic,
      sym_underline,
      sym_uppercase_text,
      sym_paren_text,
      sym_literal_char,
      sym_text,
    ACTIONS(280), 13,
      sym_scene_start,
      sym_section_start,
      sym_note_start,
      sym_forced_action_start,
      sym_forced_character_start,
      sym_forced_transition_start,
      sym_lyric_start,
      sym_centered_start,
      sym_page_break_marker,
      sym_synopsis_start,
      sym_boneyard_start,
      sym_dialogue_line_start,
      ts_builtin_sym_end,
  [832] = 2,
    ACTIONS(299), 12,
      anon_sym_DOT,
      aux_sym_character_token1,
      aux_sym_transition_token1,
      sym_escaped_char,
      sym_bold_italic,
      sym_bold,
      sym_italic,
      sym_underline,
      sym_uppercase_text,
      sym_paren_text,
      sym_literal_char,
      sym_text,
    ACTIONS(297), 13,
      sym_scene_start,
      sym_section_start,
      sym_note_start,
      sym_forced_action_start,
      sym_forced_character_start,
      sym_forced_transition_start,
      sym_lyric_start,
      sym_centered_start,
      sym_page_break_marker,
      sym_synopsis_start,
      sym_boneyard_start,
      sym_dialogue_line_start,
      ts_builtin_sym_end,
  [862] = 2,
    ACTIONS(303), 12,
      anon_sym_DOT,
      aux_sym_character_token1,
      aux_sym_transition_token1,
      sym_escaped_char,
      sym_bold_italic,
      sym_bold,
      sym_italic,
      sym_underline,
      sym_uppercase_text,
      sym_paren_text,
      sym_literal_char,
      sym_text,
    ACTIONS(301), 13,
      sym_scene_start,
      sym_section_start,
      sym_note_start,
      sym_forced_action_start,
      sym_forced_character_start,
      sym_forced_transition_start,
      sym_lyric_start,
      sym_centered_start,
      sym_page_break_marker,
      sym_synopsis_start,
      sym_boneyard_start,
      sym_dialogue_line_start,
      ts_builtin_sym_end,
  [892] = 2,
    ACTIONS(307), 12,
      anon_sym_DOT,
      aux_sym_character_token1,
      aux_sym_transition_token1,
      sym_escaped_char,
      sym_bold_italic,
      sym_bold,
      sym_italic,
      sym_underline,
      sym_uppercase_text,
      sym_paren_text,
      sym_literal_char,
      sym_text,
    ACTIONS(305), 13,
      sym_scene_start,
      sym_section_start,
      sym_note_start,
      sym_forced_action_start,
      sym_forced_character_start,
      sym_forced_transition_start,
      sym_lyric_start,
      sym_centered_start,
      sym_page_break_marker,
      sym_synopsis_start,
      sym_boneyard_start,
      sym_dialogue_line_start,
      ts_builtin_sym_end,
  [922] = 2,
    ACTIONS(309), 12,
      sym_scene_start,
      sym_section_start,
      sym_note_start,
      sym_forced_action_start,
      sym_forced_character_start,
      sym_forced_transition_start,
      sym_lyric_start,
      sym_centered_start,
      sym_page_break_marker,
      sym_synopsis_start,
      sym_boneyard_start,
      ts_builtin_sym_end,
    ACTIONS(311), 12,
      anon_sym_DOT,
      aux_sym_character_token1,
      aux_sym_transition_token1,
      sym_escaped_char,
      sym_bold_italic,
      sym_bold,
      sym_italic,
      sym_underline,
      sym_uppercase_text,
      sym_paren_text,
      sym_literal_char,
      sym_text,
  [951] = 2,
    ACTIONS(313), 12,
      sym_scene_start,
      sym_section_start,
      sym_note_start,
      sym_forced_action_start,
      sym_forced_character_start,
      sym_forced_transition_start,
      sym_lyric_start,
      sym_centered_start,
      sym_page_break_marker,
      sym_synopsis_start,
      sym_boneyard_start,
      ts_builtin_sym_end,
    ACTIONS(315), 12,
      anon_sym_DOT,
      aux_sym_character_token1,
      aux_sym_transition_token1,
      sym_escaped_char,
      sym_bold_italic,
      sym_bold,
      sym_italic,
      sym_underline,
      sym_uppercase_text,
      sym_paren_text,
      sym_literal_char,
      sym_text,
  [980] = 2,
    ACTIONS(317), 12,
      sym_scene_start,
      sym_section_start,
      sym_note_start,
      sym_forced_action_start,
      sym_forced_character_start,
      sym_forced_transition_start,
      sym_lyric_start,
      sym_centered_start,
      sym_page_break_marker,
      sym_synopsis_start,
      sym_boneyard_start,
      ts_builtin_sym_end,
    ACTIONS(319), 12,
      anon_sym_DOT,
      aux_sym_character_token1,
      aux_sym_transition_token1,
      sym_escaped_char,
      sym_bold_italic,
      sym_bold,
      sym_italic,
      sym_underline,
      sym_uppercase_text,
      sym_paren_text,
      sym_literal_char,
      sym_text,
  [1009] = 2,
    ACTIONS(321), 12,
      sym_scene_start,
      sym_section_start,
      sym_note_start,
      sym_forced_action_start,
      sym_forced_character_start,
      sym_forced_transition_start,
      sym_lyric_start,
      sym_centered_start,
      sym_page_break_marker,
      sym_synopsis_start,
      sym_boneyard_start,
      ts_builtin_sym_end,
    ACTIONS(323), 12,
      anon_sym_DOT,
      aux_sym_character_token1,
      aux_sym_transition_token1,
      sym_escaped_char,
      sym_bold_italic,
      sym_bold,
      sym_italic,
      sym_underline,
      sym_uppercase_text,
      sym_paren_text,
      sym_literal_char,
      sym_text,
  [1038] = 2,
    ACTIONS(325), 12,
      sym_scene_start,
      sym_section_start,
      sym_note_start,
      sym_forced_action_start,
      sym_forced_character_start,
      sym_forced_transition_start,
      sym_lyric_start,
      sym_centered_start,
      sym_page_break_marker,
      sym_synopsis_start,
      sym_boneyard_start,
      ts_builtin_sym_end,
    ACTIONS(327), 12,
      anon_sym_DOT,
      aux_sym_character_token1,
      aux_sym_transition_token1,
      sym_escaped_char,
      sym_bold_italic,
      sym_bold,
      sym_italic,
      sym_underline,
      sym_uppercase_text,
      sym_paren_text,
      sym_literal_char,
      sym_text,
  [1067] = 2,
    ACTIONS(329), 12,
      sym_scene_start,
      sym_section_start,
      sym_note_start,
      sym_forced_action_start,
      sym_forced_character_start,
      sym_forced_transition_start,
      sym_lyric_start,
      sym_centered_start,
      sym_page_break_marker,
      sym_synopsis_start,
      sym_boneyard_start,
      ts_builtin_sym_end,
    ACTIONS(331), 12,
      anon_sym_DOT,
      aux_sym_character_token1,
      aux_sym_transition_token1,
      sym_escaped_char,
      sym_bold_italic,
      sym_bold,
      sym_italic,
      sym_underline,
      sym_uppercase_text,
      sym_paren_text,
      sym_literal_char,
      sym_text,
  [1096] = 2,
    ACTIONS(333), 12,
      sym_scene_start,
      sym_section_start,
      sym_note_start,
      sym_forced_action_start,
      sym_forced_character_start,
      sym_forced_transition_start,
      sym_lyric_start,
      sym_centered_start,
      sym_page_break_marker,
      sym_synopsis_start,
      sym_boneyard_start,
      ts_builtin_sym_end,
    ACTIONS(335), 12,
      anon_sym_DOT,
      aux_sym_character_token1,
      aux_sym_transition_token1,
      sym_escaped_char,
      sym_bold_italic,
      sym_bold,
      sym_italic,
      sym_underline,
      sym_uppercase_text,
      sym_paren_text,
      sym_literal_char,
      sym_text,
  [1125] = 2,
    ACTIONS(337), 12,
      sym_scene_start,
      sym_section_start,
      sym_note_start,
      sym_forced_action_start,
      sym_forced_character_start,
      sym_forced_transition_start,
      sym_lyric_start,
      sym_centered_start,
      sym_page_break_marker,
      sym_synopsis_start,
      sym_boneyard_start,
      ts_builtin_sym_end,
    ACTIONS(339), 12,
      anon_sym_DOT,
      aux_sym_character_token1,
      aux_sym_transition_token1,
      sym_escaped_char,
      sym_bold_italic,
      sym_bold,
      sym_italic,
      sym_underline,
      sym_uppercase_text,
      sym_paren_text,
      sym_literal_char,
      sym_text,
  [1154] = 2,
    ACTIONS(341), 12,
      sym_scene_start,
      sym_section_start,
      sym_note_start,
      sym_forced_action_start,
      sym_forced_character_start,
      sym_forced_transition_start,
      sym_lyric_start,
      sym_centered_start,
      sym_page_break_marker,
      sym_synopsis_start,
      sym_boneyard_start,
      ts_builtin_sym_end,
    ACTIONS(343), 12,
      anon_sym_DOT,
      aux_sym_character_token1,
      aux_sym_transition_token1,
      sym_escaped_char,
      sym_bold_italic,
      sym_bold,
      sym_italic,
      sym_underline,
      sym_uppercase_text,
      sym_paren_text,
      sym_literal_char,
      sym_text,
  [1183] = 2,
    ACTIONS(345), 12,
      sym_scene_start,
      sym_section_start,
      sym_note_start,
      sym_forced_action_start,
      sym_forced_character_start,
      sym_forced_transition_start,
      sym_lyric_start,
      sym_centered_start,
      sym_page_break_marker,
      sym_synopsis_start,
      sym_boneyard_start,
      ts_builtin_sym_end,
    ACTIONS(347), 12,
      anon_sym_DOT,
      aux_sym_character_token1,
      aux_sym_transition_token1,
      sym_escaped_char,
      sym_bold_italic,
      sym_bold,
      sym_italic,
      sym_underline,
      sym_uppercase_text,
      sym_paren_text,
      sym_literal_char,
      sym_text,
  [1212] = 2,
    ACTIONS(349), 12,
      sym_scene_start,
      sym_section_start,
      sym_note_start,
      sym_forced_action_start,
      sym_forced_character_start,
      sym_forced_transition_start,
      sym_lyric_start,
      sym_centered_start,
      sym_page_break_marker,
      sym_synopsis_start,
      sym_boneyard_start,
      ts_builtin_sym_end,
    ACTIONS(351), 12,
      anon_sym_DOT,
      aux_sym_character_token1,
      aux_sym_transition_token1,
      sym_escaped_char,
      sym_bold_italic,
      sym_bold,
      sym_italic,
      sym_underline,
      sym_uppercase_text,
      sym_paren_text,
      sym_literal_char,
      sym_text,
  [1241] = 2,
    ACTIONS(353), 12,
      sym_scene_start,
      sym_section_start,
      sym_note_start,
      sym_forced_action_start,
      sym_forced_character_start,
      sym_forced_transition_start,
      sym_lyric_start,
      sym_centered_start,
      sym_page_break_marker,
      sym_synopsis_start,
      sym_boneyard_start,
      ts_builtin_sym_end,
    ACTIONS(355), 12,
      anon_sym_DOT,
      aux_sym_character_token1,
      aux_sym_transition_token1,
      sym_escaped_char,
      sym_bold_italic,
      sym_bold,
      sym_italic,
      sym_underline,
      sym_uppercase_text,
      sym_paren_text,
      sym_literal_char,
      sym_text,
  [1270] = 2,
    ACTIONS(357), 12,
      sym_scene_start,
      sym_section_start,
      sym_note_start,
      sym_forced_action_start,
      sym_forced_character_start,
      sym_forced_transition_start,
      sym_lyric_start,
      sym_centered_start,
      sym_page_break_marker,
      sym_synopsis_start,
      sym_boneyard_start,
      ts_builtin_sym_end,
    ACTIONS(359), 12,
      anon_sym_DOT,
      aux_sym_character_token1,
      aux_sym_transition_token1,
      sym_escaped_char,
      sym_bold_italic,
      sym_bold,
      sym_italic,
      sym_underline,
      sym_uppercase_text,
      sym_paren_text,
      sym_literal_char,
      sym_text,
  [1299] = 2,
    ACTIONS(361), 12,
      sym_scene_start,
      sym_section_start,
      sym_note_start,
      sym_forced_action_start,
      sym_forced_character_start,
      sym_forced_transition_start,
      sym_lyric_start,
      sym_centered_start,
      sym_page_break_marker,
      sym_synopsis_start,
      sym_boneyard_start,
      ts_builtin_sym_end,
    ACTIONS(363), 12,
      anon_sym_DOT,
      aux_sym_character_token1,
      aux_sym_transition_token1,
      sym_escaped_char,
      sym_bold_italic,
      sym_bold,
      sym_italic,
      sym_underline,
      sym_uppercase_text,
      sym_paren_text,
      sym_literal_char,
      sym_text,
  [1328] = 2,
    ACTIONS(365), 12,
      sym_scene_start,
      sym_section_start,
      sym_note_start,
      sym_forced_action_start,
      sym_forced_character_start,
      sym_forced_transition_start,
      sym_lyric_start,
      sym_centered_start,
      sym_page_break_marker,
      sym_synopsis_start,
      sym_boneyard_start,
      ts_builtin_sym_end,
    ACTIONS(367), 12,
      anon_sym_DOT,
      aux_sym_character_token1,
      aux_sym_transition_token1,
      sym_escaped_char,
      sym_bold_italic,
      sym_bold,
      sym_italic,
      sym_underline,
      sym_uppercase_text,
      sym_paren_text,
      sym_literal_char,
      sym_text,
  [1357] = 2,
    ACTIONS(369), 12,
      sym_scene_start,
      sym_section_start,
      sym_note_start,
      sym_forced_action_start,
      sym_forced_character_start,
      sym_forced_transition_start,
      sym_lyric_start,
      sym_centered_start,
      sym_page_break_marker,
      sym_synopsis_start,
      sym_boneyard_start,
      ts_builtin_sym_end,
    ACTIONS(371), 12,
      anon_sym_DOT,
      aux_sym_character_token1,
      aux_sym_transition_token1,
      sym_escaped_char,
      sym_bold_italic,
      sym_bold,
      sym_italic,
      sym_underline,
      sym_uppercase_text,
      sym_paren_text,
      sym_literal_char,
      sym_text,
  [1386] = 2,
    ACTIONS(373), 12,
      sym_scene_start,
      sym_section_start,
      sym_note_start,
      sym_forced_action_start,
      sym_forced_character_start,
      sym_forced_transition_start,
      sym_lyric_start,
      sym_centered_start,
      sym_page_break_marker,
      sym_synopsis_start,
      sym_boneyard_start,
      ts_builtin_sym_end,
    ACTIONS(375), 12,
      anon_sym_DOT,
      aux_sym_character_token1,
      aux_sym_transition_token1,
      sym_escaped_char,
      sym_bold_italic,
      sym_bold,
      sym_italic,
      sym_underline,
      sym_uppercase_text,
      sym_paren_text,
      sym_literal_char,
      sym_text,
  [1415] = 2,
    ACTIONS(377), 12,
      sym_scene_start,
      sym_section_start,
      sym_note_start,
      sym_forced_action_start,
      sym_forced_character_start,
      sym_forced_transition_start,
      sym_lyric_start,
      sym_centered_start,
      sym_page_break_marker,
      sym_synopsis_start,
      sym_boneyard_start,
      ts_builtin_sym_end,
    ACTIONS(379), 12,
      anon_sym_DOT,
      aux_sym_character_token1,
      aux_sym_transition_token1,
      sym_escaped_char,
      sym_bold_italic,
      sym_bold,
      sym_italic,
      sym_underline,
      sym_uppercase_text,
      sym_paren_text,
      sym_literal_char,
      sym_text,
  [1444] = 5,
    ACTIONS(381), 1,
      aux_sym_parenthetical_token1,
    ACTIONS(383), 1,
      anon_sym_LPAREN,
    STATE(22), 2,
      sym_dialogue,
      sym_parenthetical,
    STATE(48), 2,
      sym__inline_content,
      aux_sym_dialogue_repeat1,
    ACTIONS(385), 8,
      sym_escaped_char,
      sym_bold_italic,
      sym_bold,
      sym_italic,
      sym_underline,
      sym_uppercase_text,
      sym_literal_char,
      sym_text,
  [1469] = 3,
    ACTIONS(387), 1,
      anon_sym_LF,
    STATE(45), 2,
      sym__action_inline_content,
      aux_sym_action_repeat1,
    ACTIONS(389), 9,
      sym_escaped_char,
      sym_bold_italic,
      sym_bold,
      sym_italic,
      sym_underline,
      sym_uppercase_text,
      sym_paren_text,
      sym_literal_char,
      sym_text,
  [1488] = 3,
    ACTIONS(392), 1,
      anon_sym_LF,
    STATE(45), 2,
      sym__action_inline_content,
      aux_sym_action_repeat1,
    ACTIONS(394), 9,
      sym_escaped_char,
      sym_bold_italic,
      sym_bold,
      sym_italic,
      sym_underline,
      sym_uppercase_text,
      sym_paren_text,
      sym_literal_char,
      sym_text,
  [1507] = 3,
    ACTIONS(396), 1,
      anon_sym_LF2,
    STATE(47), 2,
      sym__inline_content,
      aux_sym_dialogue_repeat1,
    ACTIONS(398), 8,
      sym_escaped_char,
      sym_bold_italic,
      sym_bold,
      sym_italic,
      sym_underline,
      sym_uppercase_text,
      sym_literal_char,
      sym_text,
  [1525] = 3,
    ACTIONS(401), 1,
      anon_sym_LF2,
    STATE(47), 2,
      sym__inline_content,
      aux_sym_dialogue_repeat1,
    ACTIONS(403), 8,
      sym_escaped_char,
      sym_bold_italic,
      sym_bold,
      sym_italic,
      sym_underline,
      sym_uppercase_text,
      sym_literal_char,
      sym_text,
  [1543] = 6,
    ACTIONS(405), 1,
      anon_sym_LF,
    ACTIONS(407), 1,
      anon_sym_SPACE,
    ACTIONS(409), 1,
      anon_sym_DASH,
    ACTIONS(411), 1,
      sym_scene_location,
    ACTIONS(413), 1,
      anon_sym_POUND,
    STATE(78), 1,
      sym_scene_number,
  [1562] = 5,
    ACTIONS(413), 1,
      anon_sym_POUND,
    ACTIONS(415), 1,
      anon_sym_LF,
    ACTIONS(417), 1,
      anon_sym_DASH,
    ACTIONS(419), 1,
      sym_scene_location,
    STATE(101), 1,
      sym_scene_number,
  [1578] = 4,
    ACTIONS(413), 1,
      anon_sym_POUND,
    ACTIONS(417), 1,
      anon_sym_DASH,
    ACTIONS(421), 1,
      anon_sym_LF,
    STATE(101), 1,
      sym_scene_number,
  [1591] = 4,
    ACTIONS(413), 1,
      anon_sym_POUND,
    ACTIONS(423), 1,
      anon_sym_LF,
    ACTIONS(425), 1,
      anon_sym_DASH,
    STATE(83), 1,
      sym_scene_number,
  [1604] = 3,
    ACTIONS(413), 1,
      anon_sym_POUND,
    ACTIONS(427), 1,
      anon_sym_LF,
    STATE(103), 1,
      sym_scene_number,
  [1614] = 3,
    ACTIONS(413), 1,
      anon_sym_POUND,
    ACTIONS(423), 1,
      anon_sym_LF,
    STATE(83), 1,
      sym_scene_number,
  [1624] = 3,
    ACTIONS(413), 1,
      anon_sym_POUND,
    ACTIONS(429), 1,
      anon_sym_LF,
    STATE(98), 1,
      sym_scene_number,
  [1634] = 2,
    ACTIONS(431), 1,
      anon_sym_LF,
    ACTIONS(433), 1,
      anon_sym_SPACE,
  [1641] = 2,
    ACTIONS(260), 1,
      sym_title_continuation,
    STATE(13), 1,
      aux_sym_title_page_field_repeat1,
  [1648] = 2,
    ACTIONS(435), 1,
      anon_sym_LF,
    ACTIONS(437), 1,
      aux_sym_parenthetical_token1,
  [1655] = 2,
    ACTIONS(439), 1,
      anon_sym_LF,
    ACTIONS(441), 1,
      aux_sym_parenthetical_token1,
  [1662] = 2,
    ACTIONS(291), 1,
      sym_dialogue_line_start,
    STATE(20), 1,
      aux_sym_dialogue_block_repeat1,
  [1669] = 2,
    ACTIONS(443), 1,
      anon_sym_LF,
    ACTIONS(445), 1,
      aux_sym_character_token3,
  [1676] = 1,
    ACTIONS(447), 1,
      aux_sym_scene_number_token1,
  [1680] = 1,
    ACTIONS(449), 1,
      sym_dialogue_line_start,
  [1684] = 1,
    ACTIONS(451), 1,
      sym_dialogue_line_start,
  [1688] = 1,
    ACTIONS(453), 1,
      anon_sym_LF,
  [1692] = 1,
    ACTIONS(455), 1,
      anon_sym_LF,
  [1696] = 1,
    ACTIONS(457), 1,
      sym_centered_end,
  [1700] = 1,
    ACTIONS(459), 1,
      anon_sym_LF,
  [1704] = 1,
    ACTIONS(461), 1,
      anon_sym_LF,
  [1708] = 1,
    ACTIONS(463), 1,
      anon_sym_LF,
  [1712] = 1,
    ACTIONS(465), 1,
      anon_sym_LF,
  [1716] = 1,
    ACTIONS(467), 1,
      anon_sym_LF,
  [1720] = 1,
    ACTIONS(469), 1,
      anon_sym_LF,
  [1724] = 1,
    ACTIONS(471), 1,
      anon_sym_LPAREN,
  [1728] = 1,
    ACTIONS(473), 1,
      aux_sym_parenthetical_token2,
  [1732] = 1,
    ACTIONS(475), 1,
      anon_sym_RBRACK_RBRACK,
  [1736] = 1,
    ACTIONS(477), 1,
      sym_description,
  [1740] = 1,
    ACTIONS(421), 1,
      anon_sym_LF,
  [1744] = 1,
    ACTIONS(479), 1,
      anon_sym_STAR_SLASH,
  [1748] = 1,
    ACTIONS(481), 1,
      anon_sym_LF,
  [1752] = 1,
    ACTIONS(483), 1,
      sym_scene_time,
  [1756] = 1,
    ACTIONS(485), 1,
      sym_scene_time,
  [1760] = 1,
    ACTIONS(429), 1,
      anon_sym_LF,
  [1764] = 1,
    ACTIONS(487), 1,
      anon_sym_LF,
  [1768] = 1,
    ACTIONS(489), 1,
      anon_sym_LF,
  [1772] = 1,
    ACTIONS(491), 1,
      ts_builtin_sym_end,
  [1776] = 1,
    ACTIONS(493), 1,
      anon_sym_LF,
  [1780] = 1,
    ACTIONS(495), 1,
      anon_sym_LF,
  [1784] = 1,
    ACTIONS(497), 1,
      sym_dialogue_line_start,
  [1788] = 1,
    ACTIONS(499), 1,
      sym_description,
  [1792] = 1,
    ACTIONS(501), 1,
      anon_sym_LF,
  [1796] = 1,
    ACTIONS(503), 1,
      sym_boneyard_content,
  [1800] = 1,
    ACTIONS(505), 1,
      aux_sym_parenthetical_token2,
  [1804] = 1,
    ACTIONS(507), 1,
      anon_sym_RPAREN,
  [1808] = 1,
    ACTIONS(509), 1,
      aux_sym_character_token2,
  [1812] = 1,
    ACTIONS(511), 1,
      anon_sym_LF,
  [1816] = 1,
    ACTIONS(513), 1,
      sym_centered_text,
  [1820] = 1,
    ACTIONS(427), 1,
      anon_sym_LF,
  [1824] = 1,
    ACTIONS(515), 1,
      anon_sym_POUND,
  [1828] = 1,
    ACTIONS(517), 1,
      anon_sym_RPAREN,
  [1832] = 1,
    ACTIONS(423), 1,
      anon_sym_LF,
  [1836] = 1,
    ACTIONS(519), 1,
      aux_sym_character_token2,
  [1840] = 1,
    ACTIONS(521), 1,
      anon_sym_LF,
  [1844] = 1,
    ACTIONS(523), 1,
      sym_scene_time,
  [1848] = 1,
    ACTIONS(525), 1,
      aux_sym_character_token2,
  [1852] = 1,
    ACTIONS(527), 1,
      anon_sym_LF,
  [1856] = 1,
    ACTIONS(529), 1,
      aux_sym_character_token2,
  [1860] = 1,
    ACTIONS(531), 1,
      aux_sym_character_token2,
  [1864] = 1,
    ACTIONS(533), 1,
      anon_sym_LF,
  [1868] = 1,
    ACTIONS(535), 1,
      sym_note_content,
};

static const uint32_t ts_small_parse_table_map[] = {
  [SMALL_STATE(6)] = 0,
  [SMALL_STATE(7)] = 78,
  [SMALL_STATE(8)] = 156,
  [SMALL_STATE(9)] = 234,
  [SMALL_STATE(10)] = 304,
  [SMALL_STATE(11)] = 374,
  [SMALL_STATE(12)] = 444,
  [SMALL_STATE(13)] = 481,
  [SMALL_STATE(14)] = 518,
  [SMALL_STATE(15)] = 555,
  [SMALL_STATE(16)] = 592,
  [SMALL_STATE(17)] = 631,
  [SMALL_STATE(18)] = 670,
  [SMALL_STATE(19)] = 702,
  [SMALL_STATE(20)] = 737,
  [SMALL_STATE(21)] = 772,
  [SMALL_STATE(22)] = 802,
  [SMALL_STATE(23)] = 832,
  [SMALL_STATE(24)] = 862,
  [SMALL_STATE(25)] = 892,
  [SMALL_STATE(26)] = 922,
  [SMALL_STATE(27)] = 951,
  [SMALL_STATE(28)] = 980,
  [SMALL_STATE(29)] = 1009,
  [SMALL_STATE(30)] = 1038,
  [SMALL_STATE(31)] = 1067,
  [SMALL_STATE(32)] = 1096,
  [SMALL_STATE(33)] = 1125,
  [SMALL_STATE(34)] = 1154,
  [SMALL_STATE(35)] = 1183,
  [SMALL_STATE(36)] = 1212,
  [SMALL_STATE(37)] = 1241,
  [SMALL_STATE(38)] = 1270,
  [SMALL_STATE(39)] = 1299,
  [SMALL_STATE(40)] = 1328,
  [SMALL_STATE(41)] = 1357,
  [SMALL_STATE(42)] = 1386,
  [SMALL_STATE(43)] = 1415,
  [SMALL_STATE(44)] = 1444,
  [SMALL_STATE(45)] = 1469,
  [SMALL_STATE(46)] = 1488,
  [SMALL_STATE(47)] = 1507,
  [SMALL_STATE(48)] = 1525,
  [SMALL_STATE(49)] = 1543,
  [SMALL_STATE(50)] = 1562,
  [SMALL_STATE(51)] = 1578,
  [SMALL_STATE(52)] = 1591,
  [SMALL_STATE(53)] = 1604,
  [SMALL_STATE(54)] = 1614,
  [SMALL_STATE(55)] = 1624,
  [SMALL_STATE(56)] = 1634,
  [SMALL_STATE(57)] = 1641,
  [SMALL_STATE(58)] = 1648,
  [SMALL_STATE(59)] = 1655,
  [SMALL_STATE(60)] = 1662,
  [SMALL_STATE(61)] = 1669,
  [SMALL_STATE(62)] = 1676,
  [SMALL_STATE(63)] = 1680,
  [SMALL_STATE(64)] = 1684,
  [SMALL_STATE(65)] = 1688,
  [SMALL_STATE(66)] = 1692,
  [SMALL_STATE(67)] = 1696,
  [SMALL_STATE(68)] = 1700,
  [SMALL_STATE(69)] = 1704,
  [SMALL_STATE(70)] = 1708,
  [SMALL_STATE(71)] = 1712,
  [SMALL_STATE(72)] = 1716,
  [SMALL_STATE(73)] = 1720,
  [SMALL_STATE(74)] = 1724,
  [SMALL_STATE(75)] = 1728,
  [SMALL_STATE(76)] = 1732,
  [SMALL_STATE(77)] = 1736,
  [SMALL_STATE(78)] = 1740,
  [SMALL_STATE(79)] = 1744,
  [SMALL_STATE(80)] = 1748,
  [SMALL_STATE(81)] = 1752,
  [SMALL_STATE(82)] = 1756,
  [SMALL_STATE(83)] = 1760,
  [SMALL_STATE(84)] = 1764,
  [SMALL_STATE(85)] = 1768,
  [SMALL_STATE(86)] = 1772,
  [SMALL_STATE(87)] = 1776,
  [SMALL_STATE(88)] = 1780,
  [SMALL_STATE(89)] = 1784,
  [SMALL_STATE(90)] = 1788,
  [SMALL_STATE(91)] = 1792,
  [SMALL_STATE(92)] = 1796,
  [SMALL_STATE(93)] = 1800,
  [SMALL_STATE(94)] = 1804,
  [SMALL_STATE(95)] = 1808,
  [SMALL_STATE(96)] = 1812,
  [SMALL_STATE(97)] = 1816,
  [SMALL_STATE(98)] = 1820,
  [SMALL_STATE(99)] = 1824,
  [SMALL_STATE(100)] = 1828,
  [SMALL_STATE(101)] = 1832,
  [SMALL_STATE(102)] = 1836,
  [SMALL_STATE(103)] = 1840,
  [SMALL_STATE(104)] = 1844,
  [SMALL_STATE(105)] = 1848,
  [SMALL_STATE(106)] = 1852,
  [SMALL_STATE(107)] = 1856,
  [SMALL_STATE(108)] = 1860,
  [SMALL_STATE(109)] = 1864,
  [SMALL_STATE(110)] = 1868,
};

static const TSParseActionEntry ts_parse_actions[] = {
  [0] = {.entry = {.count = 0, .reusable = false}},
  [1] = {.entry = {.count = 1, .reusable = false}}, RECOVER(),
  [3] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_document, 0, 0, 0),
  [5] = {.entry = {.count = 1, .reusable = false}}, SHIFT(91),
  [7] = {.entry = {.count = 1, .reusable = false}}, SHIFT(90),
  [9] = {.entry = {.count = 1, .reusable = false}}, SHIFT(49),
  [11] = {.entry = {.count = 1, .reusable = false}}, SHIFT(89),
  [13] = {.entry = {.count = 1, .reusable = false}}, SHIFT(88),
  [15] = {.entry = {.count = 1, .reusable = false}}, SHIFT(46),
  [17] = {.entry = {.count = 1, .reusable = true}}, SHIFT(49),
  [19] = {.entry = {.count = 1, .reusable = true}}, SHIFT(56),
  [21] = {.entry = {.count = 1, .reusable = true}}, SHIFT(110),
  [23] = {.entry = {.count = 1, .reusable = true}}, SHIFT(108),
  [25] = {.entry = {.count = 1, .reusable = true}}, SHIFT(107),
  [27] = {.entry = {.count = 1, .reusable = true}}, SHIFT(105),
  [29] = {.entry = {.count = 1, .reusable = true}}, SHIFT(102),
  [31] = {.entry = {.count = 1, .reusable = true}}, SHIFT(97),
  [33] = {.entry = {.count = 1, .reusable = true}}, SHIFT(96),
  [35] = {.entry = {.count = 1, .reusable = true}}, SHIFT(95),
  [37] = {.entry = {.count = 1, .reusable = true}}, SHIFT(92),
  [39] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_document_repeat1, 2, 0, 0),
  [41] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_document_repeat1, 2, 0, 0), SHIFT_REPEAT(49),
  [44] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_document_repeat1, 2, 0, 0), SHIFT_REPEAT(89),
  [47] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_document_repeat1, 2, 0, 0), SHIFT_REPEAT(88),
  [50] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_document_repeat1, 2, 0, 0), SHIFT_REPEAT(46),
  [53] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_document_repeat1, 2, 0, 0), SHIFT_REPEAT(49),
  [56] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_document_repeat1, 2, 0, 0), SHIFT_REPEAT(56),
  [59] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_document_repeat1, 2, 0, 0), SHIFT_REPEAT(110),
  [62] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_document_repeat1, 2, 0, 0), SHIFT_REPEAT(108),
  [65] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_document_repeat1, 2, 0, 0), SHIFT_REPEAT(107),
  [68] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_document_repeat1, 2, 0, 0), SHIFT_REPEAT(105),
  [71] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_document_repeat1, 2, 0, 0), SHIFT_REPEAT(102),
  [74] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_document_repeat1, 2, 0, 0), SHIFT_REPEAT(97),
  [77] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_document_repeat1, 2, 0, 0), SHIFT_REPEAT(96),
  [80] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_document_repeat1, 2, 0, 0), SHIFT_REPEAT(95),
  [83] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_document_repeat1, 2, 0, 0), SHIFT_REPEAT(92),
  [86] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_document, 1, 0, 0),
  [88] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_document, 2, 0, 0),
  [90] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_section_block_repeat1, 2, 0, 0),
  [92] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_section_block_repeat1, 2, 0, 0), SHIFT_REPEAT(49),
  [95] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_section_block_repeat1, 2, 0, 0), SHIFT_REPEAT(89),
  [98] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_section_block_repeat1, 2, 0, 0), SHIFT_REPEAT(88),
  [101] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_section_block_repeat1, 2, 0, 0), SHIFT_REPEAT(46),
  [104] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_section_block_repeat1, 2, 0, 0), SHIFT_REPEAT(49),
  [107] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_section_block_repeat1, 2, 0, 0), SHIFT_REPEAT(110),
  [110] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_section_block_repeat1, 2, 0, 0), SHIFT_REPEAT(108),
  [113] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_section_block_repeat1, 2, 0, 0), SHIFT_REPEAT(107),
  [116] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_section_block_repeat1, 2, 0, 0), SHIFT_REPEAT(105),
  [119] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_section_block_repeat1, 2, 0, 0), SHIFT_REPEAT(102),
  [122] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_section_block_repeat1, 2, 0, 0), SHIFT_REPEAT(97),
  [125] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_section_block_repeat1, 2, 0, 0), SHIFT_REPEAT(96),
  [128] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_section_block_repeat1, 2, 0, 0), SHIFT_REPEAT(95),
  [131] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_section_block_repeat1, 2, 0, 0), SHIFT_REPEAT(92),
  [134] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_section_block, 2, 0, 0),
  [136] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_section_block, 1, 0, 0),
  [138] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_scene_block, 1, 0, 0),
  [140] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_scene_block, 1, 0, 0),
  [142] = {.entry = {.count = 2, .reusable = false}}, REDUCE(sym_scene_block, 1, 0, 0), SHIFT(89),
  [145] = {.entry = {.count = 2, .reusable = false}}, REDUCE(sym_scene_block, 1, 0, 0), SHIFT(88),
  [148] = {.entry = {.count = 2, .reusable = false}}, REDUCE(sym_scene_block, 1, 0, 0), SHIFT(46),
  [151] = {.entry = {.count = 2, .reusable = true}}, REDUCE(sym_scene_block, 1, 0, 0), SHIFT(110),
  [154] = {.entry = {.count = 2, .reusable = true}}, REDUCE(sym_scene_block, 1, 0, 0), SHIFT(108),
  [157] = {.entry = {.count = 2, .reusable = true}}, REDUCE(sym_scene_block, 1, 0, 0), SHIFT(107),
  [160] = {.entry = {.count = 2, .reusable = true}}, REDUCE(sym_scene_block, 1, 0, 0), SHIFT(105),
  [163] = {.entry = {.count = 2, .reusable = true}}, REDUCE(sym_scene_block, 1, 0, 0), SHIFT(102),
  [166] = {.entry = {.count = 2, .reusable = true}}, REDUCE(sym_scene_block, 1, 0, 0), SHIFT(97),
  [169] = {.entry = {.count = 2, .reusable = true}}, REDUCE(sym_scene_block, 1, 0, 0), SHIFT(95),
  [172] = {.entry = {.count = 2, .reusable = true}}, REDUCE(sym_scene_block, 1, 0, 0), SHIFT(92),
  [175] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_scene_block, 2, 0, 0),
  [177] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_scene_block, 2, 0, 0),
  [179] = {.entry = {.count = 2, .reusable = false}}, REDUCE(sym_scene_block, 2, 0, 0), SHIFT(89),
  [182] = {.entry = {.count = 2, .reusable = false}}, REDUCE(sym_scene_block, 2, 0, 0), SHIFT(88),
  [185] = {.entry = {.count = 2, .reusable = false}}, REDUCE(sym_scene_block, 2, 0, 0), SHIFT(46),
  [188] = {.entry = {.count = 2, .reusable = true}}, REDUCE(sym_scene_block, 2, 0, 0), SHIFT(110),
  [191] = {.entry = {.count = 2, .reusable = true}}, REDUCE(sym_scene_block, 2, 0, 0), SHIFT(108),
  [194] = {.entry = {.count = 2, .reusable = true}}, REDUCE(sym_scene_block, 2, 0, 0), SHIFT(107),
  [197] = {.entry = {.count = 2, .reusable = true}}, REDUCE(sym_scene_block, 2, 0, 0), SHIFT(105),
  [200] = {.entry = {.count = 2, .reusable = true}}, REDUCE(sym_scene_block, 2, 0, 0), SHIFT(102),
  [203] = {.entry = {.count = 2, .reusable = true}}, REDUCE(sym_scene_block, 2, 0, 0), SHIFT(97),
  [206] = {.entry = {.count = 2, .reusable = true}}, REDUCE(sym_scene_block, 2, 0, 0), SHIFT(95),
  [209] = {.entry = {.count = 2, .reusable = true}}, REDUCE(sym_scene_block, 2, 0, 0), SHIFT(92),
  [212] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_scene_block_repeat1, 2, 0, 0),
  [214] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_scene_block_repeat1, 2, 0, 0),
  [216] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_scene_block_repeat1, 2, 0, 0), SHIFT_REPEAT(89),
  [219] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_scene_block_repeat1, 2, 0, 0), SHIFT_REPEAT(88),
  [222] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_scene_block_repeat1, 2, 0, 0), SHIFT_REPEAT(46),
  [225] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_scene_block_repeat1, 2, 0, 0), SHIFT_REPEAT(110),
  [228] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_scene_block_repeat1, 2, 0, 0), SHIFT_REPEAT(108),
  [231] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_scene_block_repeat1, 2, 0, 0), SHIFT_REPEAT(107),
  [234] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_scene_block_repeat1, 2, 0, 0), SHIFT_REPEAT(105),
  [237] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_scene_block_repeat1, 2, 0, 0), SHIFT_REPEAT(102),
  [240] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_scene_block_repeat1, 2, 0, 0), SHIFT_REPEAT(97),
  [243] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_scene_block_repeat1, 2, 0, 0), SHIFT_REPEAT(95),
  [246] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_scene_block_repeat1, 2, 0, 0), SHIFT_REPEAT(92),
  [249] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_title_page_field_repeat1, 2, 0, 0),
  [251] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_title_page_field_repeat1, 2, 0, 0),
  [253] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_title_page_field_repeat1, 2, 0, 0), SHIFT_REPEAT(71),
  [256] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_title_page_field, 3, 0, 0),
  [258] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_title_page_field, 3, 0, 0),
  [260] = {.entry = {.count = 1, .reusable = true}}, SHIFT(71),
  [262] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_title_page_field, 4, 0, 0),
  [264] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_title_page_field, 4, 0, 0),
  [266] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_title_page, 1, 0, 0),
  [268] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_title_page, 1, 0, 0),
  [270] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_title_page_repeat1, 2, 0, 0),
  [272] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_title_page_repeat1, 2, 0, 0), SHIFT_REPEAT(91),
  [275] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_title_page_repeat1, 2, 0, 0), SHIFT_REPEAT(90),
  [278] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_title_page_repeat1, 2, 0, 0),
  [280] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_dialogue_block_repeat1, 2, 0, 0),
  [282] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_dialogue_block_repeat1, 2, 0, 0),
  [284] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_dialogue_block_repeat1, 2, 0, 0), SHIFT_REPEAT(44),
  [287] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_dialogue_block, 2, 0, 0),
  [289] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_dialogue_block, 2, 0, 0),
  [291] = {.entry = {.count = 1, .reusable = true}}, SHIFT(44),
  [293] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_parenthetical, 6, 0, 0),
  [295] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_parenthetical, 6, 0, 0),
  [297] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_dialogue, 2, 0, 0),
  [299] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_dialogue, 2, 0, 0),
  [301] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_parenthetical, 4, 0, 0),
  [303] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_parenthetical, 4, 0, 0),
  [305] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_parenthetical, 5, 0, 0),
  [307] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_parenthetical, 5, 0, 0),
  [309] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_scene_heading, 2, 0, 0),
  [311] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_scene_heading, 2, 0, 0),
  [313] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_page_break, 2, 0, 0),
  [315] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_page_break, 2, 0, 0),
  [317] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_scene_heading, 7, 0, 0),
  [319] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_scene_heading, 7, 0, 0),
  [321] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_scene_heading, 6, 0, 0),
  [323] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_scene_heading, 6, 0, 0),
  [325] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_scene_heading, 5, 0, 0),
  [327] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_scene_heading, 5, 0, 0),
  [329] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_section_heading, 2, 0, 0),
  [331] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_section_heading, 2, 0, 0),
  [333] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_scene_heading, 4, 0, 0),
  [335] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_scene_heading, 4, 0, 0),
  [337] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_section_heading, 4, 0, 0),
  [339] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_section_heading, 4, 0, 0),
  [341] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_note, 4, 0, 0),
  [343] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_note, 4, 0, 0),
  [345] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_centered, 4, 0, 0),
  [347] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_centered, 4, 0, 0),
  [349] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_synopsis, 3, 0, 0),
  [351] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_synopsis, 3, 0, 0),
  [353] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_lyric, 3, 0, 0),
  [355] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_lyric, 3, 0, 0),
  [357] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_transition, 3, 0, 0),
  [359] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_transition, 3, 0, 0),
  [361] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_boneyard, 4, 0, 0),
  [363] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_boneyard, 4, 0, 0),
  [365] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_action, 3, 0, 0),
  [367] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_action, 3, 0, 0),
  [369] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_action, 2, 0, 0),
  [371] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_action, 2, 0, 0),
  [373] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_transition, 2, 0, 0),
  [375] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_transition, 2, 0, 0),
  [377] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_scene_heading, 3, 0, 0),
  [379] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_scene_heading, 3, 0, 0),
  [381] = {.entry = {.count = 1, .reusable = false}}, SHIFT(74),
  [383] = {.entry = {.count = 1, .reusable = false}}, SHIFT(75),
  [385] = {.entry = {.count = 1, .reusable = false}}, SHIFT(48),
  [387] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_action_repeat1, 2, 0, 0),
  [389] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_action_repeat1, 2, 0, 0), SHIFT_REPEAT(45),
  [392] = {.entry = {.count = 1, .reusable = false}}, SHIFT(41),
  [394] = {.entry = {.count = 1, .reusable = false}}, SHIFT(45),
  [396] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_dialogue_repeat1, 2, 0, 0),
  [398] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_dialogue_repeat1, 2, 0, 0), SHIFT_REPEAT(47),
  [401] = {.entry = {.count = 1, .reusable = true}}, SHIFT(23),
  [403] = {.entry = {.count = 1, .reusable = false}}, SHIFT(47),
  [405] = {.entry = {.count = 1, .reusable = false}}, SHIFT(26),
  [407] = {.entry = {.count = 1, .reusable = false}}, SHIFT(50),
  [409] = {.entry = {.count = 1, .reusable = false}}, SHIFT(81),
  [411] = {.entry = {.count = 1, .reusable = false}}, SHIFT(51),
  [413] = {.entry = {.count = 1, .reusable = false}}, SHIFT(62),
  [415] = {.entry = {.count = 1, .reusable = false}}, SHIFT(43),
  [417] = {.entry = {.count = 1, .reusable = false}}, SHIFT(104),
  [419] = {.entry = {.count = 1, .reusable = false}}, SHIFT(52),
  [421] = {.entry = {.count = 1, .reusable = true}}, SHIFT(43),
  [423] = {.entry = {.count = 1, .reusable = true}}, SHIFT(32),
  [425] = {.entry = {.count = 1, .reusable = false}}, SHIFT(82),
  [427] = {.entry = {.count = 1, .reusable = true}}, SHIFT(29),
  [429] = {.entry = {.count = 1, .reusable = true}}, SHIFT(30),
  [431] = {.entry = {.count = 1, .reusable = false}}, SHIFT(31),
  [433] = {.entry = {.count = 1, .reusable = false}}, SHIFT(77),
  [435] = {.entry = {.count = 1, .reusable = false}}, SHIFT(25),
  [437] = {.entry = {.count = 1, .reusable = false}}, SHIFT(109),
  [439] = {.entry = {.count = 1, .reusable = false}}, SHIFT(24),
  [441] = {.entry = {.count = 1, .reusable = false}}, SHIFT(106),
  [443] = {.entry = {.count = 1, .reusable = true}}, SHIFT(64),
  [445] = {.entry = {.count = 1, .reusable = false}}, SHIFT(65),
  [447] = {.entry = {.count = 1, .reusable = true}}, SHIFT(99),
  [449] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_character, 4, 0, 0),
  [451] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_character, 3, 0, 0),
  [453] = {.entry = {.count = 1, .reusable = true}}, SHIFT(63),
  [455] = {.entry = {.count = 1, .reusable = true}}, SHIFT(36),
  [457] = {.entry = {.count = 1, .reusable = true}}, SHIFT(68),
  [459] = {.entry = {.count = 1, .reusable = true}}, SHIFT(35),
  [461] = {.entry = {.count = 1, .reusable = true}}, SHIFT(37),
  [463] = {.entry = {.count = 1, .reusable = true}}, SHIFT(39),
  [465] = {.entry = {.count = 1, .reusable = true}}, SHIFT(18),
  [467] = {.entry = {.count = 1, .reusable = true}}, SHIFT(38),
  [469] = {.entry = {.count = 1, .reusable = true}}, SHIFT(40),
  [471] = {.entry = {.count = 1, .reusable = true}}, SHIFT(93),
  [473] = {.entry = {.count = 1, .reusable = true}}, SHIFT(94),
  [475] = {.entry = {.count = 1, .reusable = true}}, SHIFT(87),
  [477] = {.entry = {.count = 1, .reusable = true}}, SHIFT(85),
  [479] = {.entry = {.count = 1, .reusable = true}}, SHIFT(70),
  [481] = {.entry = {.count = 1, .reusable = true}}, SHIFT(14),
  [483] = {.entry = {.count = 1, .reusable = true}}, SHIFT(54),
  [485] = {.entry = {.count = 1, .reusable = true}}, SHIFT(53),
  [487] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_scene_number, 3, 0, 0),
  [489] = {.entry = {.count = 1, .reusable = true}}, SHIFT(33),
  [491] = {.entry = {.count = 1, .reusable = true}},  ACCEPT_INPUT(),
  [493] = {.entry = {.count = 1, .reusable = true}}, SHIFT(34),
  [495] = {.entry = {.count = 1, .reusable = true}}, SHIFT(42),
  [497] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_character, 1, 0, 0),
  [499] = {.entry = {.count = 1, .reusable = true}}, SHIFT(80),
  [501] = {.entry = {.count = 1, .reusable = true}}, SHIFT(57),
  [503] = {.entry = {.count = 1, .reusable = true}}, SHIFT(79),
  [505] = {.entry = {.count = 1, .reusable = true}}, SHIFT(100),
  [507] = {.entry = {.count = 1, .reusable = true}}, SHIFT(59),
  [509] = {.entry = {.count = 1, .reusable = true}}, SHIFT(66),
  [511] = {.entry = {.count = 1, .reusable = true}}, SHIFT(27),
  [513] = {.entry = {.count = 1, .reusable = true}}, SHIFT(67),
  [515] = {.entry = {.count = 1, .reusable = true}}, SHIFT(84),
  [517] = {.entry = {.count = 1, .reusable = true}}, SHIFT(58),
  [519] = {.entry = {.count = 1, .reusable = true}}, SHIFT(69),
  [521] = {.entry = {.count = 1, .reusable = true}}, SHIFT(28),
  [523] = {.entry = {.count = 1, .reusable = true}}, SHIFT(55),
  [525] = {.entry = {.count = 1, .reusable = true}}, SHIFT(72),
  [527] = {.entry = {.count = 1, .reusable = true}}, SHIFT(25),
  [529] = {.entry = {.count = 1, .reusable = true}}, SHIFT(61),
  [531] = {.entry = {.count = 1, .reusable = true}}, SHIFT(73),
  [533] = {.entry = {.count = 1, .reusable = true}}, SHIFT(21),
  [535] = {.entry = {.count = 1, .reusable = true}}, SHIFT(76),
};

enum ts_external_scanner_symbol_identifiers {
  ts_external_token_scene_start = 0,
  ts_external_token_section_start = 1,
  ts_external_token_note_start = 2,
  ts_external_token_forced_action_start = 3,
  ts_external_token_forced_character_start = 4,
  ts_external_token_forced_transition_start = 5,
  ts_external_token_lyric_start = 6,
  ts_external_token_centered_start = 7,
  ts_external_token_page_break_marker = 8,
  ts_external_token_synopsis_start = 9,
  ts_external_token_boneyard_start = 10,
  ts_external_token_title_continuation = 11,
  ts_external_token_blank_line = 12,
  ts_external_token_dialogue_line_start = 13,
};

static const TSSymbol ts_external_scanner_symbol_map[EXTERNAL_TOKEN_COUNT] = {
  [ts_external_token_scene_start] = sym_scene_start,
  [ts_external_token_section_start] = sym_section_start,
  [ts_external_token_note_start] = sym_note_start,
  [ts_external_token_forced_action_start] = sym_forced_action_start,
  [ts_external_token_forced_character_start] = sym_forced_character_start,
  [ts_external_token_forced_transition_start] = sym_forced_transition_start,
  [ts_external_token_lyric_start] = sym_lyric_start,
  [ts_external_token_centered_start] = sym_centered_start,
  [ts_external_token_page_break_marker] = sym_page_break_marker,
  [ts_external_token_synopsis_start] = sym_synopsis_start,
  [ts_external_token_boneyard_start] = sym_boneyard_start,
  [ts_external_token_title_continuation] = sym_title_continuation,
  [ts_external_token_blank_line] = sym_blank_line,
  [ts_external_token_dialogue_line_start] = sym_dialogue_line_start,
};

static const bool ts_external_scanner_states[7][EXTERNAL_TOKEN_COUNT] = {
  [1] = {
    [ts_external_token_scene_start] = true,
    [ts_external_token_section_start] = true,
    [ts_external_token_note_start] = true,
    [ts_external_token_forced_action_start] = true,
    [ts_external_token_forced_character_start] = true,
    [ts_external_token_forced_transition_start] = true,
    [ts_external_token_lyric_start] = true,
    [ts_external_token_centered_start] = true,
    [ts_external_token_page_break_marker] = true,
    [ts_external_token_synopsis_start] = true,
    [ts_external_token_boneyard_start] = true,
    [ts_external_token_title_continuation] = true,
    [ts_external_token_blank_line] = true,
    [ts_external_token_dialogue_line_start] = true,
  },
  [2] = {
    [ts_external_token_scene_start] = true,
    [ts_external_token_section_start] = true,
    [ts_external_token_note_start] = true,
    [ts_external_token_forced_action_start] = true,
    [ts_external_token_forced_character_start] = true,
    [ts_external_token_forced_transition_start] = true,
    [ts_external_token_lyric_start] = true,
    [ts_external_token_centered_start] = true,
    [ts_external_token_page_break_marker] = true,
    [ts_external_token_synopsis_start] = true,
    [ts_external_token_boneyard_start] = true,
  },
  [3] = {
    [ts_external_token_scene_start] = true,
    [ts_external_token_section_start] = true,
    [ts_external_token_note_start] = true,
    [ts_external_token_forced_action_start] = true,
    [ts_external_token_forced_character_start] = true,
    [ts_external_token_forced_transition_start] = true,
    [ts_external_token_lyric_start] = true,
    [ts_external_token_centered_start] = true,
    [ts_external_token_page_break_marker] = true,
    [ts_external_token_synopsis_start] = true,
    [ts_external_token_boneyard_start] = true,
    [ts_external_token_title_continuation] = true,
  },
  [4] = {
    [ts_external_token_scene_start] = true,
    [ts_external_token_section_start] = true,
    [ts_external_token_note_start] = true,
    [ts_external_token_forced_action_start] = true,
    [ts_external_token_forced_character_start] = true,
    [ts_external_token_forced_transition_start] = true,
    [ts_external_token_lyric_start] = true,
    [ts_external_token_centered_start] = true,
    [ts_external_token_page_break_marker] = true,
    [ts_external_token_synopsis_start] = true,
    [ts_external_token_boneyard_start] = true,
    [ts_external_token_dialogue_line_start] = true,
  },
  [5] = {
    [ts_external_token_title_continuation] = true,
  },
  [6] = {
    [ts_external_token_dialogue_line_start] = true,
  },
};

#ifdef __cplusplus
extern "C" {
#endif
void *tree_sitter_fountain_external_scanner_create(void);
void tree_sitter_fountain_external_scanner_destroy(void *);
bool tree_sitter_fountain_external_scanner_scan(void *, TSLexer *, const bool *);
unsigned tree_sitter_fountain_external_scanner_serialize(void *, char *);
void tree_sitter_fountain_external_scanner_deserialize(void *, const char *, unsigned);

#ifdef TREE_SITTER_HIDE_SYMBOLS
#define TS_PUBLIC
#elif defined(_WIN32)
#define TS_PUBLIC __declspec(dllexport)
#else
#define TS_PUBLIC __attribute__((visibility("default")))
#endif

TS_PUBLIC const TSLanguage *tree_sitter_fountain(void) {
  static const TSLanguage language = {
    .version = LANGUAGE_VERSION,
    .symbol_count = SYMBOL_COUNT,
    .alias_count = ALIAS_COUNT,
    .token_count = TOKEN_COUNT,
    .external_token_count = EXTERNAL_TOKEN_COUNT,
    .state_count = STATE_COUNT,
    .large_state_count = LARGE_STATE_COUNT,
    .production_id_count = PRODUCTION_ID_COUNT,
    .field_count = FIELD_COUNT,
    .max_alias_sequence_length = MAX_ALIAS_SEQUENCE_LENGTH,
    .parse_table = &ts_parse_table[0][0],
    .small_parse_table = ts_small_parse_table,
    .small_parse_table_map = ts_small_parse_table_map,
    .parse_actions = ts_parse_actions,
    .symbol_names = ts_symbol_names,
    .symbol_metadata = ts_symbol_metadata,
    .public_symbol_map = ts_symbol_map,
    .alias_map = ts_non_terminal_alias_map,
    .alias_sequences = &ts_alias_sequences[0][0],
    .lex_modes = ts_lex_modes,
    .lex_fn = ts_lex,
    .external_scanner = {
      &ts_external_scanner_states[0][0],
      ts_external_scanner_symbol_map,
      tree_sitter_fountain_external_scanner_create,
      tree_sitter_fountain_external_scanner_destroy,
      tree_sitter_fountain_external_scanner_scan,
      tree_sitter_fountain_external_scanner_serialize,
      tree_sitter_fountain_external_scanner_deserialize,
    },
    .primary_state_ids = ts_primary_state_ids,
  };
  return &language;
}
#ifdef __cplusplus
}
#endif
