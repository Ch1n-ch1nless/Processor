		call MAIN
		hlt
:READ
		in
		push rax
		in 
		push rbx
		in
		push rcx
		ret

:OUT
		pop rax
		out
		pop rbx
		out
		pop rcx
		out
		ret

:IS_LINEAR
		pop rax
		push 0
		je LIN
		jmp SQR
	:LIN
			call SOLVE_LINEAR
			ret
	:SQR
			call SOLVE_SQUARE
			ret

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
				ret

		:NO_ROOTS
				push 0
				out
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
			pop [11]
			out
			ret

:SOLVE_SQUARE
		call CALCULATE_DISCRIMINANT
		call COUNT_ROOTS

		pop [0]
		push 2
		je FIND_TWO_ROOTs
		pop [0]
		push 1
		je FIND_ONE_ROOT
		jmp NO_ROOTS

	:FIND_TWO_ROOTS
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
			pop [11]
			out
			pop [22]
			out 

			ret

	:FIND_ONE_ROOT
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
			pop[11]
			out

			ret 

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