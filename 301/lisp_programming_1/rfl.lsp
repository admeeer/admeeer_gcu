; remove the last element of a list
(defun remove-last (lst)
	; check if tail is null, if it is, return nothing
  (if (null (cdr lst))
      '()
	  ; this will recursively call itself until cdr lst is nothing
     (cons (car lst) (remove-last (cdr lst)))))

; removes the first element and calls remove-last, which returns the 
(defun remove-first-call-remove-last (lst)
; if function has length of 1 or 2, return the lst
  (if (or (null (cdr lst)) (null (cdr (cdr lst))))
		; return
      lst
	  ; else return new list of second element and call remove-last with second element removed
      (cons (cadr lst) (remove-last (cddr lst)))))


(print (remove-first-call-remove-last '(1)))

(print (remove-first-call-remove-last '(1 2)))

(print(remove-first-call-remove-last '(1 2 3 4)))

(print (remove-first-call-remove-last '(1 2 3 4 5 6 7)))

(print (remove-first-call-remove-last '(1 2 3 4 5)))




