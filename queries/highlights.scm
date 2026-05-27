;; Fountain 语法高亮定义

;; 对话体（包含所有对话行、延续标记、行内note/注释 - 统一高亮为string）
;; 内部细化高亮通过injection查询处理
(dialogue_body) @string

;; Action行（包含行内内容）
(action) @text

;; 括号内文本（action/dialogue_body注入后使用）
(paren_text) @type

;; Parenthetical lines
(parenthetical_line) @type

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

;; 行内Notes（action行内）
(inline_note) @comment

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

;; 行内Boneyard（action行内）
(inline_boneyard) @comment
