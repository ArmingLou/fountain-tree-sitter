;; 对话体内部自注入fountain语法实现精细高亮
;; injection.self 将dialogue_body内容用同一grammar重新解析
;; 内容会fallback到action规则，从而识别 inline_note、inline_boneyard、paren_text
(dialogue_body) @injection.content
  (#set! injection.self)
