;; 将dialogue_body内容注入到fountain-inline语法解析
;; fountain-inline只处理 [[note]] /*注释*/ (text)
;; 忽略@、>、#等语法标记
((dialogue_body) @content
 (#set! language "fountain_inline"))
