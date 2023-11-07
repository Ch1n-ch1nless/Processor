		call MAIN
		hlt
; Reads the number that factorial will be calculated after
;
; Arguments:
;	rax -- number
:READ_NUMBER
		in
		pop rax
		ret

; Prints factorial number
;
; Arguments:
;	rbx -- factorial number
:PRINT_FACTORIAL
		push rbx
		out
		ret

; Calculate the factorial number
;
; Arguments:
;	rax -- number
; Returns:
; 	rbx -- factorial number 
;
:CALCULATE_FACTORIAL_NUMBER
		push rax
		push 1
		je not_call

		push rax
		push rbx
		mul      	; rbx = rbx * rax
		pop rbx

		push rax
		push 1
		sub
		pop rax 	; rax = rax - 1
		
		call CALCULATE_FACTORIAL_NUMBER
	:not_call
		ret

;Put 1 in register 'rbx'
;
; Arguments
;	rbx -- register
:FILL_RBX
		push 1
		pop rbx 
		ret

:MAIN
		call READ_NUMBER
		call FILL_RBX
		call CALCULATE_FACTORIAL_NUMBER
		call PRINT_FACTORIAL	
