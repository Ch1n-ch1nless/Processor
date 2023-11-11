		call MAIN
		hlt

;----------------------------------------------------------

; Prints the last fibonacci number 
;
; Arguments:
;	rax -- value of last fibonacci number

:PRINT_FIBONACCI_NUMBER
		push rax
		out
		ret

;----------------------------------------------------------

; Evaluates fibonacci number
;
; Arguments:
;	rdx -- amount of fibonacci numbers
; Returns:
;	rax  -- desired fibonacci number, 
; 	rbx  -- next fibonacci number,

:SEARCH_FIBONACCI_NUMBER
		push 0
		push rdx
		je end_of_recursion

		push rdx
		push 1
		sub
		pop  rdx

		call SEARCH_FIBONACCI_NUMBER

		push rdx
		push 1
		add
		pop  rdx

		push rbx
		push rax
		push rbx
		add
		pop  rbx
		pop rax

		ret

	:end_of_recursion
			push 0
			pop  rax
			push 1
			pop  rbx

			ret

;----------------------------------------------------------

; Reads the amount of fibonacci numbers
;
; Arguments:
;	rdx -- amount of fibonacci numbers

:READ_NUMBER_OF_FIBONACCI_NUMBER
		in
		pop rdx
		ret

;----------------------------------------------------------
		
:MAIN
		call READ_NUMBER_OF_FIBONACCI_NUMBER	; Read number of fibonacci number
		call SEARCH_FIBONACCI_NUMBER		; Search the fibonacci number
		call PRINT_FIBONACCI_NUMBER	   	; Print the number  
		ret

;----------------------------------------------------------