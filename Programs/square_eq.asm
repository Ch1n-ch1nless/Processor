		call MAIN
		hlt

; Read 3 coefficients of square equation
;
; Arguments:
;	rax -- senior coefficient
;	rbx -- second coefficient
; 	rcx -- free term
:READ_COEFFICIENTS 
		in
		pop rax
		in 
		pop rbx
		in
		pop rcx
		ret

; Defines a square or linear equation, depending on the senior coefficient
;
; Argument:
; 	rax -- senior coefficient
:IS_ZERO_THE_FIRST_CF
		push rax
		push 0
		jne first_cf_is_not_zero
		call SOLVE_LINEAR_EQUATION ; call this function, if senior coefficient == 0
		ret
	:first_cf_is_not_zero
			call SOLVE_SQUARE_EQUATION
			ret

; Solve linear equation 
;
; Arguments:
; 	rbx -- second coefficient 
;	rcx -- free term
; Returns:
;	memory([0], [11])
:SOLVE_LINEAR_EQUATION
		push rbx
		push 0
		je inf_or_zero
		jmp one_lin_root

	:inf_or_zero
			push rcx
			push 0
			jne no_roots
			jmp inf_roots

		:inf_roots
				push 8
				out
				ret

		:no_roots
				push 0
				out
				ret

	:one_lin_root
			push rcx
			push -1
			mul
			push rbx
			div
			pop [11]
			push 1
			out
			push [11]
			out
			ret

; Solve square equation
;
; Arguments:
;	rax -- first  coefficient, 
;      	rbx -- second coefficient, 
;	rcx -- free term
;
; Returns:
; 	rdx, memory([0], [11], [22])
:SOLVE_SQUARE_EQUATION
		call CALCULATE_DISCRIMINANT
		call COUNT_ROOTS

		push [0]
		push 2
		je two_roots
		push [0]
		push 1
		je one_root
		jmp no_roots

	:two_roots
			push rdx
			sqrt
			pop rdx

			push rbx
			push -1
			mul
			push rdx
			sub
			push 2
			push rax
			div
			div
			pop [11]

			push rbx
			push -1
			mul
			push rdx
			add
			push 2
			push rax
			div
			div
			pop [22]
			
			push 2	
			out
			push [11]
			out
			push [22]
			out

			ret

	:one_root
			push rbx
			push -1
			mul
			push 2
			div
			push rax
			div
			pop  [11]

			push 1
			out
      			push [11]
			out

			ret 

; Calculate Discriminant
;
; Arguments:
; 	rax, rbx, rdx
; Returns:
; 	rdx -- Discriminant
:CALCULATE_DISCRIMINANT
		push rbx
		push rbx
		mul
		push 4
		push rax
		mul
		push rcx
		mul
		sub
		pop rdx
		ret

; Calculate the number of roots
;
; Arguments:
;	rdx -- Discriminant
; Returns:
;	[0] (RAM cell with number 0)
:COUNT_ROOTS
		push rdx
		push 0
		je d_equal_0
		push rdx
		push 0
		ja d_fewer_0
		jmp d_greater_0

	:d_equal_0
			push 1
			pop  [0]
			ret
	
	:d_fewer_0
			push 0
			pop  [0]
			ret

	:d_greater_0
			push 2
			pop  [0]
			ret

:MAIN
		call READ_COEFFICIENTS
		call :IS_ZERO_THE_FIRST_CF
		ret