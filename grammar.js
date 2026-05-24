/// <reference types="tree-sitter-cli/dsl" />
// @ts-check

module.exports = grammar({
  name: "fountain",
  conflicts: $ => [
    [$.title_page_field, $.action],
    [$.scene_block],
    [$.section_block]
  ],

  externals: $ => [
    $.scene_start,
    $.section_start,
    $.note_start,
    $.forced_action_start,
    $.forced_character_start,
    $.forced_transition_start,
    $.lyric_start,
    $.centered_start,
    $.page_break_marker,
    $.synopsis_start,
    $.boneyard_start,
    $.title_continuation,
    $.blank_line,
    $.dialogue_line_start
  ],

  rules: {
    document: $ => seq(
      optional($.title_page),
      repeat($._element)
    ),

    // Title page: consume all key:value pairs and indented lines
    // until we hit a blank line or EOF or a scene/section start
    title_page: $ => prec(20, repeat1($.title_page_field)),

    // Top-level elements: sections, scenes, and standalone items
    _element: $ => choice(
      $.section_block,
      $.scene_block,
      $.dialogue_block,
      $.action,
      $.transition,
      $.centered,
      $.lyric,
      $.boneyard,
      $.page_break,
      $.synopsis,
      $.note
    ),

    // Section block: section heading followed by scenes and content
    // Continues until the next section heading or EOF
    section_block: $ => prec.right(seq(
      $.section_heading,
      repeat(choice(
        $.scene_block,
        $.dialogue_block,
        $.action,
        $.transition,
        $.centered,
        $.lyric,
        $.boneyard,
        $.page_break,
        $.synopsis,
        $.note
      ))
    )),

    // Scene block: scene heading followed by scene content
    scene_block: $ => seq(
      $.scene_heading,
      repeat($._scene_content)
    ),

    // Content that can appear within a scene
    _scene_content: $ => choice(
      $.dialogue_block,
      $.action,
      $.transition,
      $.centered,
      $.lyric,
      $.note,
      $.boneyard,
      $.synopsis
    ),

    // Title page field supports multi-line values via indented continuation lines
    title_page_field: $ => choice(
      // Form 1: Key with inline value (space is part of the key token)
      seq(
        $.title_key_with_space,
        $.description,
        '\n',
        repeat(seq($.title_continuation, '\n'))
      ),
      // Form 2: Key without inline value, followed by continuations
      seq(
        $.title_key,
        '\n',
        repeat1(seq($.title_continuation, '\n'))
      )
    ),

    title_key: $ => token(prec(1, seq(
      /[A-Z][a-z][A-Za-z0-9 ]*/,  // Must start with capital then lowercase (Title case)
      ':'
    ))),

    title_key_with_space: $ => token(prec(1, seq(
      /[A-Z][a-z][A-Za-z0-9 ]*/,  // Must start with capital then lowercase (Title case)
      ':',
      ' '
    ))),

    scene_heading: $ => prec(5, choice(
      seq(
        $.scene_start,
        optional(' '),
        optional($.scene_location),
        optional(seq(
          '-',
          $.scene_time
        )),
        optional($.scene_number),
        '\n'
      ),
      seq(
        '.',
        optional(' '),
        optional($.scene_location),
        optional(seq(
          '-',
          $.scene_time
        )),
        optional($.scene_number),
        '\n'
      )
    )),

    scene_location: $ => /[^-#\n]+/,

    scene_time: $ => /[^#\n]+/,

    scene_number: $ => seq(
      '#',
      /[A-Za-z0-9\-\.]+/,
      '#'
    ),

    character: $ => choice(
      token(seq(
        /[A-Z][A-Z0-9 \(\)\.']*[A-Z0-9\)\.]/,  // Character name - all caps, can have spaces, must end with letter/digit/paren/period
        optional(/ \^/),  // optional dual dialogue marker with single space
        /\n/  // Must be immediately followed by newline (no colon allowed)
      )),
      seq(
        $.forced_character_start,
        /[^\n]+/,
        optional(/ \^/),
        '\n'
      )
    ),

    dialogue_block: $ => prec(4, seq(
      $.character,
      repeat1(seq(
        $.dialogue_line_start,  // Must be a non-blank line
        choice($.parenthetical, $.dialogue)  // Check parenthetical first
      ))
    )),

    dialogue: $ => prec.right(seq(
      repeat1($._inline_content),
      token.immediate('\n')
    )),

    parenthetical: $ => prec.right(10, seq(  // Higher precedence than dialogue
      optional(/ +/),  // Optional leading spaces
      '(',
      /[^)]+/,
      ')',
      optional(/ +/),  // Optional trailing spaces
      '\n'
    )),

    action: $ => prec(1, choice(
      seq(
        $.forced_action_start,
        /[^\n]+/,
        '\n'
      ),
      seq(
        repeat1($._action_inline_content),
        '\n'
      )
    )),

    transition: $ => prec(3, choice(
      seq(
        $.forced_transition_start,
        /[^\n]+/,
        '\n'
      ),
      seq(
        token(/[A-Z][A-Z ]*TO:/),  // Any uppercase text ending in TO:
        '\n'
      )
    )),

    section_heading: $ => prec(5, seq(
      $.section_start,
      optional(seq(' ', $.description)),
      '\n'
    )),

    note: $ => prec(5, seq(
      $.note_start,
      $.note_content,
      ']]',
      '\n'
    )),

    note_content: $ => /[^\]]+/,

    // Boneyard comments (/* ... */)
    boneyard: $ => prec(10, seq(
      $.boneyard_start,
      $.boneyard_content,
      '*/',
      '\n'
    )),

    boneyard_content: $ => token(prec(-1, repeat(choice(
      /[^*]+/,  // Any character except *
      /\*[^\/]/  // * not followed by /
    )))),

    // Page breaks (===)
    page_break: $ => prec(10, seq(
      $.page_break_marker,
      '\n'
    )),

    // Synopses (= text)
    synopsis: $ => prec(5, seq(
      $.synopsis_start,
      /[^\n]+/,
      '\n'
    )),

    // Lyrics (~text)
    lyric: $ => prec(4, seq(
      $.lyric_start,
      /[^\n]+/,
      '\n'
    )),

    // Centered text (>text<)
    centered: $ => prec(4, seq(
      $.centered_start,
      $.centered_text,
      $.centered_end,
      '\n'
    )),

    centered_text: $ => /[^<\n]+/,

    centered_end: $ => '<',

    // Action inline content: includes paren_text for inline parens like "MAYA (28)"
    // Order matters: more specific patterns first
    // literal_char must come LAST as fallback for unmatched * or _
    _action_inline_content: $ => prec.left(choice(
      $.escaped_char,
      $.bold_italic,
      $.bold,
      $.italic,
      $.underline,
      $.uppercase_text,
      $.paren_text,
      $.text,
      prec(-1, $.literal_char)  // Lowest precedence - only match if nothing else works
    )),

    // Dialogue inline content: excludes paren_text (parentheticals are standalone lines)
    _inline_content: $ => prec.left(choice(
      $.escaped_char,
      $.bold_italic,
      $.bold,
      $.italic,
      $.underline,
      $.uppercase_text,
      $.text,
      prec(-1, $.literal_char)  // Lowest precedence - only match if nothing else works
    )),

    // Escaped characters - backslash followed by special char renders literally
    // Must come before emphasis markers to prevent \* from being parsed as italic
    escaped_char: $ => /\\[*_\[\]()\\]/,

    // Emphasis markers - these have higher precedence
    // Using token() to make matching atomic - either match completely or not at all
    // This prevents partial matches that would consume opening delimiters
    bold_italic: $ => token(seq(
      '***',
      /[^*\n]+/,
      '***'
    )),

    bold: $ => token(seq(
      '**',
      /[^*\n]+/,
      '**'
    )),

    italic: $ => token(seq(
      '*',
      /[^*\n]+/,
      '*'
    )),

    underline: $ => token(seq(
      '_',
      /[^_\n]+/,
      '_'
    )),

    // Uppercase key words (2+ consecutive uppercase letters)
    // Can include spaces between uppercase words
    uppercase_text: $ => /[A-Z][A-Z]+( +[A-Z]+)*/,

    // Parenthesized text - for inline parens in action lines and dialogue
    // Must be on same line (no newlines), entire paren group
    paren_text: $ => /\([^)\n]+\)/,

    // Literal emphasis characters that aren't part of formatting
    // Matches single * or _ that can't be paired for emphasis
    // Must come after emphasis rules attempt to match, as fallback
    literal_char: $ => /[*_]/,

    // Regular text - everything else
    // Matches: lowercase, digits, punctuation, title-case words (capital + lowercase+)
    // Excludes: parentheses (for parentheticals), emphasis markers, backslash (for escaped chars)
    text: $ => /[^A-Z*_\n()\\]+|[A-Z][^A-Z*_\n()\\]+/,

    line: $ => token(prec(-1, /[^\n]+/)),  // Lower precedence so specific patterns match first

    // Description should not start with whitespace (to avoid matching continuation lines)
    description: $ => /[^ \t\n][^\n]*/
  }
});
