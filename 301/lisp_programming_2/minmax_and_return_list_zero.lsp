; define function min-max to have parameter list and optional parameters min and max
(defun min_max (lst &optional min max)
	; is the list null? return a list of min and max if min exists, otherwise return nil
  (cond ((null lst) (when min (list min max)))
		; does the list only have one element? return min max, where min is either (car lst) or min, and max to (car lst) or max
        ((null (cdr lst)) (list (if (or (null min) (< (car lst) min)) (car lst) min)
                                (if (or (null max) (> (car lst) max)) (car lst) max)))
        ; else, do this, lst has more than one element, so call function recursively
		(t (min_max (cdr lst)
                    (if (or (null min) (< (car lst) min)) (car lst) min)
                    (if (or (null max) (> (car lst) max)) (car lst) max)))))

(defun return_list_zero (n)
  (cond ((= 0 n) nil)
        (t (cons n (return_list_zero (read))))))

(print (min_max (return_list_zero (read))))





