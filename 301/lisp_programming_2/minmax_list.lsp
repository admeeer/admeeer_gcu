

		
;(defun min-max (lst)
 ; (cond ((null lst) nil)
  ;      ((null (cdr lst)) (list (car lst) (car lst)))
   ;     (t (let ((result (min-max (cdr lst))))
    ;         (list (if (< (car lst) (car result))
     ;                  (car lst)
      ;                 (car result))
       ;            (if (> (car lst) (cadr result))
        ;               (car lst)
         ;              (cadr result)))))))


; define function min-max to have parameter list and optional parameters min and max
(defun min-max (lst &optional min max)
	; is the list null? return a list of min and max if min exists, otherwise return nil
  (cond ((null lst) (when min (list min max)))
		; does the list only have one element? return min max, where min is either (car lst) or min, and max to (car lst) or max
        ((null (cdr lst)) (list (if (or (null min) (< (car lst) min)) (car lst) min)
                                (if (or (null max) (> (car lst) max)) (car lst) max)))
        ; else, do this, lst has more than one element, so call function recursively
		(t (min-max (cdr lst)
                    (if (or (null min) (< (car lst) min)) (car lst) min)
                    (if (or (null max) (> (car lst) max)) (car lst) max)))))


(print (min-max '(6 2 3 4 5)))


;(if condition
;    true-form
 ;   false-form)
