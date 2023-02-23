; palindrome function
(defun ispal (list)
	(cond
		((null list) T) ; a list with no elements is technically palindromic
		((null (cdr list)) T) ; a list with one element is also, oddly enough, palindromic
		(t (and (equal (car list) (car (reverse list))) ; make sure the first and last elements are equal
				(ispal (cdr (reverse (cdr (reverse list))))))))) ; call the function recursively with the firsts and last element removed


(print (ispal '(1 2 3 4 5)))

(print (ispal '(1 2 3 2 1)))

(print (ispal '(1 2 2 1)))

(print (ispal '(1 2 3 4 5 4 3 2 1)))
