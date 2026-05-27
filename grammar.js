/// <reference types="tree-sitter-cli/dsl" />
// @ts-check

module.exports = grammar({
  name: "fountain",

  conflicts: $ => [
    [$.title_page_field, $.action],
    [$.scene_block],
    [$.section_block],
    [$.dialogue_block]
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
    $.dialogue_line_start,
    $.dialogue_body,
    $.parenthetical_line,
    $.inline_note,
    $.inline_boneyard
  ],

  rules: {
    document: $ => seq(
      optional($.title_page),
      repeat(choice(
        $._element,
        $.blank_line
      ))
    ),

    // Title page: consume all key:value pairs and indented lines
    // until we hit a blank line or EOF or a scene/section start
    title_page: $ => prec(20, repeat1($.title_page_field)),

    // Top-level elements: order matters! scene/section/character/transition before action
    // boneyard 已移除，通过 inline_boneyard 在 action 行内匹配 /* */
    _element: $ => choice(
      $.section_block,
      $.scene_block,
      $.dialogue_block,
      $.transition,
      $.note,
      $.synopsis,
      $.lyric,
      $.centered,
      $.page_break,
      $.action  // Action LAST - it's the fallback
    ),

    // Section block: section heading followed by scenes and content
    // Continues until the next section heading or EOF
    section_block: $ => prec(8, seq(  // Highest precedence for top-level elements
      $.section_heading,
      repeat(choice(
        $.blank_line,
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
      $.blank_line,
      $.dialogue_block,
      $.action,
      $.transition,
      $.centered,
      $.lyric,
      $.note,
      $.boneyard,
      $.synopsis,
      $.page_break
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

    scene_heading: $ => prec(7, choice(  // Higher precedence than action (4)
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
      /[^#\n]+/,
      '#'
    ),

    character: $ => choice(
      // Standard character: uppercase name, must be after blank line (handled by grammar context)
      token(seq(
        /[A-Z][A-Z0-9 \(\)\.']*[A-Z0-9\)\.]/,
        optional(/ \^/),
        /\n/
      )),
      // Forced character (@): must follow blank line for proper parsing
      seq(
        $.forced_character_start,
        /[^\n]+/,
        optional(/ \^/),
        '\n'
      )
    ),

    dialogue_block: $ => prec(20, seq(
      $.character,
      $.dialogue_body
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

    action: $ => prec(1, choice(  // Lowest precedence - action is fallback
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

    transition: $ => prec(6, choice(  // Higher than action (1), lower than scene_heading (7)
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

    section_heading: $ => prec(7, seq(
      $.section_start,
      optional(seq(optional(' '), $.description)),
      '\n'
    )),

note: $ => prec(2, seq(  // Higher precedence than action (prec 1)
      $.note_start,
      token.immediate(repeat1(/[^\]]|\*[^/]/)),  // 匹配到 ]] 之前的所有内容
      ']]',
      '\n'
    )),

    // Boneyard comments (/* ... */) - 从 /* 到 */
    boneyard: $ => prec(10, seq(
      $.boneyard_start,
      token.immediate(repeat1(/[^*]|\*[^/]/)),
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

    // Action inline content - 行内注释和备注优先
    // inline_boneyard 和 inline_note 有最高优先级(20)确保 /* */ 和 [[ ]] 正确匹配
    // 支持跨行的行内注释如：xxx[[sdf\nsdfsdf]]是内容
    _action_inline_content: $ => prec.left(choice(
      prec(20, $.inline_boneyard),
      prec(20, $.inline_note),
      $.escaped_char,
      $.underline,
      $.uppercase_text,
      $.paren_text,
      $.text,
      prec(-1, $.literal_char)  // Lowest precedence
    )),

    // Dialogue inline content - 支持行内注释
    _inline_content: $ => prec.left(choice(
      prec(20, $.inline_boneyard),
      prec(20, $.inline_note),
      $.escaped_char,
      $.underline,
      $.uppercase_text,
      $.text,
      prec(-1, $.literal_char)
    )),

    // Escaped characters - backslash followed by special char renders literally
    // Must come before emphasis markers to prevent \* from being parsed as italic
    escaped_char: $ => /\\[*_\[\]()\\]/,

    // Emphasis markers - 已禁用以避免与 /* */ 冲突
    // bold_italic: $ => token(seq(
    //   '***',
    //   /[^*\n]+/,
    //   '***'
    // )),

    // bold: $ => token(seq(
    //   '**',
    //   /[^*\n]+/,
    //   '**'
    // )),

    // italic: $ => token(seq(
    //   '*',
    //   /[^*\n]+/,
    //   '*'
    // )),

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
    // Matches single * _ or / that can't be paired for formatting
    // Must come after emphasis rules attempt to match, as fallback
    literal_char: $ => /[*_\/]/,

    // Regular text - everything else
    // Matches: lowercase, digits, punctuation, title-case words (capital + lowercase+)
    // Excludes: parentheses, emphasis markers, backslash, @ (for forced character), / (for inline_boneyard)
    // Note: [] excluded for inline_note
    text: $ => /[^A-Z*\/_\n()\\@\[\]]+|[A-Z][^A-Z*\/_\n()\\@\[\]]+/,

    line: $ => token(prec(-1, /[^\n]+/)),  // Lower precedence so specific patterns match first

    // Description should not start with whitespace (to avoid matching continuation lines)
    description: $ => /[^ \t\n][^\n]*/
  }
});
