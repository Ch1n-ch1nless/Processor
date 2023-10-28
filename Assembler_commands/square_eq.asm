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
				push 10
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

:MAIN
		call READ
		call IS_LINEAR
		ret