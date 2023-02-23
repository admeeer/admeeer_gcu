(defun tail-recursive (lst)
; is list null?
  (if (null lst)
; yes, return 0
      0
; add 1 to result, call function again
      (+ 1 (tail-recursive (cdr lst)))))



(print (tail-recursive '(1 2 3 4 5)))

(print (tail-recursive '(1 2 3)))

(print (tail-recursive '(1 2)))

(print (tail-recursive '(1)))