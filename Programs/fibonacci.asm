		call MAIN
		hlt

; Prints the last fibonacci number 
;
; Arguments:
;	rax -- value of last fibonacci number
;
:PRINT_FIBONACCI_NUMBER
		push rax
		out
		ret

; Evaluates fibonacci number
;
; Arguments:
;	rdx -- amount of fibonacci numbers
; Returns:
;	rax  -- desired fibonacci number, 
; 	rbx  -- next fibonacci number, 
;	rcx  -- counter
;
:SEARCH_FIBONACCI_NUMBER
		call MAKE_START_VALUES
	:start_cycle
			push rbx	  ; rax = rbx, rbx = rax + rbx
			push rax
			push rbx
			add
			pop rbx
			pop rax 

			push 1    ; rcx += 1
			push rcx
			add
			pop rcx

			push rcx
			push rdx
			ja start_cycle
		ret

; Read the amount of fibonacci numbers
;
; Arguments:
;	rdx -- amount of fibonacci numbers
:READ_NUMBER_OF_FIBONACCI_NUMBER
		in
		pop rdx
		ret

; Fills rax and rbx by values of first and second fibonacci numbers and makes counter 
;
; Returns
;	rax -- fibonacci number with 0
;	rbx -- fibonacci number with 1
;	rcx -- counter
:MAKE_START_VALUES
		push 0
		pop rax ; first fibonacci number
		push 0
		pop rcx ; counter
		push 1
		pop rbx ; second fibonacci number
		ret
		
:MAIN
		call READ_NUMBER_OF_FIBONACCI_NUMBER	; Read number of fibonacci number
		call SEARCH_FIBONACCI_NUMBER		; Search the fibonacci number
		call PRINT_FIBONACCI_NUMBER	   	; Print the number  
		ret