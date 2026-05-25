;; Fountain 语法高亮定义

(dialogue_line_start) @string
(action) @text

;; Parenthetical lines (wrylies)
(parenthetical_line) @type

;; Emphasis in dialogue and action (bold but same color)
(italic) @emphasis.strong
(bold) @emphasis.strong
(bold_italic) @emphasis.strong
(underline) @emphasis.strong

;; Uppercase key words/props in action lines
(uppercase_text) @emphasis.strong
(action (uppercase_text) @emphasis.strong)

;; Title page - subtle highlighting
(title_key) @keyword

;; Character names
(character) @number

;; Transitions (normal and forced >)
(transition) @attribute
(forced_transition_start) @comment

;; Scene headings with scene numbers
(scene_heading) @keyword
(scene_start) @function
(scene_location) @keyword
(scene_time) @function
(scene_number) @attribute

;; Section headings (# markers)
(section_heading) @constant
(section_start) @comment

;; Notes [[text]]
(note) @comment
(note_start) @comment
(note_content_nested) @comment

;; Forced elements
(forced_action_start) @comment
(forced_character_start) @comment

;; Lyrics ~text
(lyric_start) @type
(lyric) @string.special

;; Centered text >text<
(centered_start) @comment
(centered) @type
(centered_end) @comment

;; Page breaks ===
(page_break) @keyword
(page_break_marker) @keyword

;; Synopses = text
(synopsis_start) @comment
(synopsis) @comment.doc

;; Boneyard /* ... */
(boneyard) @comment
(boneyard_start) @comment
(boneyard_content_nested) @comment
