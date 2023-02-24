; fibonacci function fib
(defun fib (n)
; if n == 0, return 0, if n == 1, return 1
  (cond ((= n 0) 0)
        ((= n 1) 1)
		; return sum of (n-1) and (n-2) fibonacci number
        (t (+ (fib (- n 1)) (fib (- n 2))))))

; ask for input
(format t "Please enter a number: ")
; get input, typecast the line to an integer
(let ((n (parse-integer (read-line))))
; call fib and print fibonacci number
  (format t "The ~Dth fibonacci number is ~D~%" n (fib n)))
