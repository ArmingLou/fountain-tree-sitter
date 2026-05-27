;; Fountain 语法高亮定义

;; 对话体（基底）和普通文本节点。 不能指定，否则注入的高亮不起作用
;; (dialogue_body) @string

;; Action行
(action) @text

;; fountain_inline 注入后的高亮（由 languages/fountain_inline/queries/highlights.scm 处理）
(inline_note) @comment
(inline_boneyard) @comment

;; Emphasis
(underline) @emphasis.strong
(uppercase_text) @emphasis.strong

;; Title page
(title_key) @keyword

;; Character names
(character) @number

;; Transitions
(transition) @attribute
(forced_transition_start) @comment

;; Scene headings
(scene_heading) @keyword
(scene_start) @function
(scene_location) @keyword
(scene_time) @function
(scene_number) @attribute

;; Section headings
(section_heading) @constant
(section_start) @comment

;; 独立Notes [[text]]（顶级元素）
(note) @comment
(note_start) @comment

;; Forced elements
(forced_action_start) @comment
(forced_character_start) @comment

;; Lyrics
(lyric_start) @type
(lyric) @string.special

;; Centered text
(centered_start) @comment
(centered) @type
(centered_end) @comment

;; Page breaks
(page_break) @keyword
(page_break_marker) @keyword

;; Synopses
(synopsis_start) @comment
(synopsis) @comment.doc

;; 独立Boneyard /* ... */（顶级元素）
(boneyard) @comment
(boneyard_start) @comment
