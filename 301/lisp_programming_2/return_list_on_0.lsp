
(defun return_list_zero (n)
  (cond ((= 0 n) nil)
        (t (cons n (return_list_zero (read))))))

(print (return_list_zero (read)))

