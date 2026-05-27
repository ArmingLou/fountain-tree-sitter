;; 对话体内部注入fountain语法实现精细高亮
;; 对话体内容会被重新解析，[[...]]和/*...*/会自动匹配为inline_note/inline_boneyard
(dialogue_body) @injection.content
  (#set! injection.language "fountain")
