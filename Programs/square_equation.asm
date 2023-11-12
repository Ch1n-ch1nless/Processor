		call MAIN
		hlt

;------------------------------------------------

; Reads 3 coefficients of square equation
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

;------------------------------------------------

; Solves linear equation 
;
; Arguments:
; 	rbx -- second coefficient 
;	rcx -- free term
; Returns:
;	memory cell [0]  -- number of roots
;	memory cell [11] -- value of root

:SOLVE_LINEAR_EQUATION
		push rbx
		push 0
		je inf_or_zero	 ; if second coefficient == 0, then we go to label "inf_or_zero"
		jmp one_lin_root ; go to label "one_lin_root" in other cases

	:inf_or_zero
			push rcx
			push 0
			; if our equation looks like: "0 * x^2 + 0 * x + C = 0", then go to label "no_roots"
			jne no_roots
			; if our equation looks like: "0 * x^2 + 0 * x + 0 = 0", then go to label "inf_roots"
			jmp inf_roots 

		:inf_roots
				push 8
				pop [0] ; put the number, which means infinite of roots
				ret

		:no_roots
				push 0
				pop [0] ; put the number of roots
				ret

	:one_lin_root
			push rcx
			push -1
			mul
			push rbx
			div	 ; x = -c / b
			pop [11] ; put the x in the memory cell 

			push 1
			pop [0]	 ; put the number of roots

			ret

;------------------------------------------------

; Solves square equation
;
; Arguments:
;	rax -- first  coefficient, 
;      	rbx -- second coefficient, 
;	rcx -- free term
;
; Returns:
;	rdx -- Discriminant,
;	memory cell [0]	 -- number of roots, 
;	memory cell [11] -- value of first root, 
;	memory cell [22] -- value of second root

:SOLVE_SQUARE_EQUATION
		push 0
		push rax
		je SOLVE_LINEAR_EQUATION

		call CALCULATE_DISCRIMINANT
		call COUNT_ROOTS

		push [0]
		push 2
		je two_roots ; if number of roots == 2, go to "two_roots"
		push [0]
		push 1
		je one_root  ; if number of roots == 1, go to "one_root"
		jmp no_roots ; in other case go to "no_roots"

	:two_roots
			push rdx
			sqrt
			pop rdx ; put sqrt(Discriminant) in register "rdx"

			push rbx
			push -1
			mul
			push rdx
			sub
			push 2
			push rax
			div
			div
			pop [11] ; put (-b - sqrt(D)) / (2 * a) in the memory cell

			push rbx
			push -1
			mul
			push rdx
			add
			push 2
			push rax
			div
			div
			pop [22] ; put (-b + sqrt(D)) / (2 * a) in the memory cell

			ret

	:one_root
			push rbx
			push -1
			mul
			push 2
			div
			push rax
			div
			pop  [11] ; put -b / (2 * a) in the memory cell 

			ret

;------------------------------------------------ 

; Calculates Discriminant
;
; Arguments:
; 	rax -- senior coefficient, 
;	rbx -- second coefficient, 
;	rdx -- free term
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
		pop rdx ; put (b^2 - 4*a*c) in memory cell
		ret

;------------------------------------------------

; Calculates the number of roots
;
; Arguments:
;	rdx -- Discriminant
; Returns:
;	memory cell [0]  -- number of roots

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

;------------------------------------------------

; Prints number of roots and their values
;
; Arguments:
;	memory cell [0]  -- number of roots,
; 	memory cell [11] -- first  root,
;	memory cell [22] -- second root

:PRINT_ROOTS
		push [0]
		out	 ; print number of roots

		push [0]
		push 2
		je print_two_roots

		push [0]
		push 1
		je print_one_root

		ret

	:print_two_roots
			push [11]
			out	  ; print first root
			push [22]
			out	  ; print second root 
			ret

	:print_one_root
			push [11]
			out	  ; print root
			ret

;------------------------------------------------

:MAIN
		call READ_COEFFICIENTS
		call SOLVE_SQUARE_EQUATION
		call PRINT_ROOTS
		ret

;------------------------------------------------