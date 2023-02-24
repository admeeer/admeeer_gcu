(defun test (l) (loop for x from 1 to 3 do (setq l (cons (read) l))) l )
(defun te () (test '()))

(print (te))


