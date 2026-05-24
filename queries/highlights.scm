[
 (action)
 (dialogue)
] @spell

;; Emphasis in dialogue and action (bold but same color)
(italic) @emphasis.strong
(bold) @emphasis.strong
(bold_italic) @emphasis.strong
(underline) @emphasis.strong

;; Uppercase key words/props in action lines
(uppercase_text) @emphasis.strong
(action (uppercase_text) @emphasis.strong)

(parenthetical) @comment.doc

;; Title page - subtle highlighting
(title_key) @keyword

;; Character names
(character) @label

;; Transitions (normal and forced >)
(transition) @keyword
(forced_transition_start) @keyword

;; Scene headings with scene numbers
(scene_start) @keyword
(scene_location) @emphasis.strong
(scene_time) @string.special
(scene_number) @number

;; Section headings (# markers)
(section_start) @punctuation.special
(section_heading (description) @emphasis.strong)

;; Notes [[text]]
(note_start) @punctuation.bracket
(note_content) @comment

;; Forced elements
(forced_action_start) @operator
(forced_character_start) @operator

;; Lyrics ~text
(lyric_start) @operator
(lyric) @string.special

;; Centered text >text<
(centered_start) @operator
(centered) @emphasis

;; Page breaks ===
(page_break) @punctuation.special
(page_break_marker) @punctuation.special

;; Synopses = text
(synopsis_start) @operator
(synopsis) @comment.doc

;; Boneyard /* ... */
(boneyard_start) @comment
(boneyard) @comment
