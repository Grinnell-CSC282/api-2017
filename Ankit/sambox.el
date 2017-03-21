(defun sambox ()
  "Inserts a commented box, depending on the length of fill-column"
  ;; This is horrible code but it works
  (interactive)
  (let ((string (concat " " (read-from-minibuffer "String? ") " ")))
    (table-insert 1 1 (length string) 1)
    (insert-string string)
    (delete-forward-char (length string)))
  (previous-line)
  (save-excursion
    (move-beginning-of-line nil)
    (set-mark (point))
    (next-line 2)
    (move-end-of-line nil)
    (comment-region (mark) (point)))
  (move-end-of-line nil)
  (insert-char ?- (- fill-column (current-column))))
