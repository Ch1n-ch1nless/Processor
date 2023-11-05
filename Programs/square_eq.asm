		call MAIN
		hlt

; Read 3 coefficients of square equation
;
; Arguments:
;	rax -- senior coefficient
;	rbx -- second coefficient
; 	rcx -- free term
:READ 
		in
		push rax
		in 
		push rbx
		in
		push rcx
		ret

; Defines a square or linear equation
;
; Argument:
; 	rax -- senior coefficient
:IS_LINEAR
		pop rax
		push 0
		jne SQR
		call SOLVE_LINEAR
		ret
	:SQR
			call QUADRATKA
			ret

; Solve linear equation 
;
; Arguments:
; 	rbx, rcx
; Clobbers:
;	memory([0] & [11])
:SOLVE_LINEAR
		pop rbx
		push 0
		je INF_OR_ZERO
		jmp ONE_LIN_ROOT

	:INF_OR_ZERO
			pop rcx
			push 0
			jne NO_ROOTS
			jmp INF_ROOTS

		:INF_ROOTS
				push 8
				out
				push 10
				putc
				ret

		:NO_ROOTS
				push 0
				out
				push 10
				putc
				ret

	:ONE_LIN_ROOT
			pop rcx
			push -1
			mul
			pop rbx
			div
			push [11]
			push 1
			out
			push 10
			putc
			pop [11]
			out
			push 10
			putc
			ret

; Solve square equation
;
; Arguments:
;	rax, rbx, rcx
;
; Clobbers:
; 	rdx, memory([0], [11] & [22])
:QUADRATKA
		call CALCULATE_DISCRIMINANT
		call COUNT_ROOTS

		pop [0]
		push 2
		je TWO_ROOTS
		pop [0]
		push 1
		je ROOT_ONE
		jmp NO_ROOTS

	:TWO_ROOTS
			pop rdx
			sqrt
			push rdx

			pop rbx
			push -1
			mul
			pop rdx
			sub
			push 2
			pop rax
			div
			div
			push [11]

			pop rbx
			push -1
			mul
			pop rdx
			add
			push 2
			pop rax
			div
			div
			push [22]
			
			push 2	
			out
			push 10
			putc
			pop [11]
			out
			push 10
			putc
			pop [22]
			out 
			push 10
			putc

			ret

	:ROOT_ONE
			pop rbx
			push -1
			mul
			push 2
			div
			pop rax
			div
			push [11]

			push 1
			out
			push 10
			putc
			pop[11]
			out
			push 10
			putc

			ret 

; Calculate Discriminant
;
; Arguments:
; 	rax, rbx, rdx
; Return:
; 	rdx -- Discriminant
:CALCULATE_DISCRIMINANT
		pop rbx
		pop rbx
		mul
		push 4
		pop rax
		mul
		pop rcx
		mul
		sub
		push rdx
		ret

; Calculate the number of roots
;
; Arguments:
;	rdx 
; Return:
;	[0] (RAM cell with number 0)
:COUNT_ROOTS
		pop rdx
		push 0
		je D_EQUAL_0
		pop rdx
		push 0
		ja D_FEWER_0
		jmp D_GREATER_0

	:D_EQUAL_0
			push 1
			push [0]
			ret
	
	:D_FEWER_0
			push 0
			push [0]
			ret

	:D_GREATER_0
			push 2
			push [0]
			ret

:MAIN
		call READ
		call IS_LINEAR
		ret