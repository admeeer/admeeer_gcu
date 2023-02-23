(defun QuickSort (lst)
  (cond
    ((null lst) nil)
    (t
      (append
        (QuickSort (ListLessThan (car lst) (cdr lst)))
        (cons (car lst) nil) 
        (QuickSort (ListGreaterThan (car lst) (cdr lst)))))))

(defun ListLessThan (a b)
  (cond
    ((or (null a) (null b)) nil)
    ((< a (car b)) (ListLessThan a (cdr b)))
    (t (cons (car b) (ListLessThan a (cdr b))))))

(defun ListGreaterThan (a b)
  (cond
    ((or (null a) (null b)) nil)
    ((>= a (car b)) (ListGreaterThan a (cdr b)))
    (t (cons (car b) (ListGreaterThan a (cdr b))))))
	
	
(print (QuickSort '(1 3 2 5 4)))

(print (QuickSort '(8 4 3 5 6 7 1 2 3 44 33 212 654 2 78 4 3 6)))