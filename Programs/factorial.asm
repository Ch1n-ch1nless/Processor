		call MAIN
		hlt

;--------------------------------------------------------------------

; Reads the number that factorial will be calculated after
;
; Returns:
;	rax -- number

:READ_NUMBER
		in
		pop rax
		ret

;--------------------------------------------------------------------

; Prints factorial number
;
; Arguments:
;	rbx -- factorial number

:PRINT_FACTORIAL
		push rbx
		out
		ret

;--------------------------------------------------------------------

; Calculates the factorial number
;
; Arguments:
;	rax -- number
; Returns:
; 	rbx -- factorial number 

:CALCULATE_FACTORIAL_NUMBER
		push 0
		push rax
		je end_of_recursion
		
		push rax
		push 1
		sub
		pop rax	; rax = rax - 1

		call CALCULATE_FACTORIAL_NUMBER	

		push rax
		push 1
		add
		pop rax ; rax = rax + 1

		push rax
		push rbx
		mul
		pop rbx	; rbx = rbx * rax
	
		ret

	:end_of_recursion
			push 1
			push rbx
			add
			pop rbx ; rbx = 0!
			
			ret

;--------------------------------------------------------------------

:MAIN
		call READ_NUMBER
		call CALCULATE_FACTORIAL_NUMBER
		call PRINT_FACTORIAL
		ret

;--------------------------------------------------------------------	
