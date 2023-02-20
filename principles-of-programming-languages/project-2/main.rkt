; deniz ünal
; 2019400234
; compiling: yes
; complete: yes
#lang racket

(provide (all-defined-out))

; 10 points
(define := (lambda (var value) (list var value)))
; 10 points
(define -- (lambda args (cons 'let (list args))))
; 10 points
(define @ (lambda (bindings expr) (list (car bindings) (car (cdr bindings)) (car expr))))
; 20 points
(define split_at_delim (lambda (delim args) 
			 (cond ((null? args) '()) 
			 (else (cons (car (get_first_split delim args))
                         (split_at_delim delim (car (cdr (get_first_split delim args)))))))))

(define (get_first_split delim args) (cond ((null? args) (list '() '()))
                            ((equal? delim (car args)) (list '() (cdr args)))
                            (else (list (cons (car args) (car (get_first_split delim (cdr args))))
                            (car (cdr (get_first_split delim (cdr args))))))))

; 30 points
(define parse_expr (lambda (expr) (cond ((null? expr) '())
                                ((contains_char '+ expr)
                                (cons '+ (map parse_expr (split_at_delim '+ expr))))
                                ((contains_char '* expr)
                                (cons '* (map parse_expr (split_at_delim '* expr))))
                                ((contains_char '@ expr)
                                (apply @ (list (parse_bind (caar (split_at_delim '@ expr))) (list (parse_expr (cdr (split_at_delim '@ expr)))))))
                                ((null? (cdr expr)) (cond ((list? (car expr)) (parse_expr (car expr))) (else (car expr))))
                                (else expr))))

(define (parse_bind bl) (cond ((null? bl) '())
                              ((contains_char '-- bl) (apply -- (map parse_bind (split_at_delim '-- bl))))
                              ((contains_char ':= bl) (:= (parse_bind (cdr (caar (split_at_delim ':= bl))))
                              (cond ((number? (parse_bind (car (cdr (split_at_delim ':= bl))))) (parse_bind (car (cdr (split_at_delim ':= bl)))))
                              (else (parse_bind (cdr (caar (cdr (split_at_delim ':= bl)))))))))
                              (else (car bl))))

(define (contains_char char expr) (cond ((null? expr) #F)
                                ((equal? char (car expr)) #T)
                                (else (contains_char char (cdr expr)))))

; 20 points
(define eval_expr (lambda (expr) (eval (parse_expr expr))))

