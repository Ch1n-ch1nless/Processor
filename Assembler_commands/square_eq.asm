		call MAIN
		hlt
:READ
		push 97
		putc
		push 32
		putc
		push 58
		putc
		push 61
		putc
		push 32
		putc 
		in
		push rax
		push 98
		putc
		push 32
		putc
		push 58
		putc
		push 61
		putc
		push 32
		putc
		in 
		push rbx
		push 99
		putc
		push 32
		putc
		push 58
		putc
		push 61
		putc
		push 32
		putc
		in
		push rcx
		push 10
		putc
		ret

:IS_LINEAR
		pop rax
		push 0
		jne SQR
		call SOLVE_LINEAR
		ret
	:SQR
			call QUADRATKA
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
				call NUMBER_OF_ROOTS
				push 73
				putc
				push 78
				putc
				push 70
				putc
				push 10
				putc
				ret

		:NO_ROOTS
				call NUMBER_OF_ROOTS
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
			call NUMBER_OF_ROOTS
			push 1
			out
			push 10
			putc
			call X_ONE
			pop [11]
			out
			push 10
			putc
			ret

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
			
			call NUMBER_OF_ROOTS
			push 2	
			out
			push 10
			putc
			call X_ONE
			pop [11]
			out
			push 10
			putc
			call X_TWO
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

			call NUMBER_OF_ROOTS
			push 1
			out
			push 10
			putc
			call X_ONE
			pop[11]
			out
			push 10
			putc

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
		call INTRO
		call READ
		call IS_LINEAR
		call OUTRO
		ret

:INTRO
		push 72
		putc
		push 101
		putc
		push 108
		putc
		push 108
		putc
		push 111
		putc
		push 33
		putc
		push 32
		putc
		push 84
		putc
		push 104
		putc
		push 105
		putc
		push 115
		putc
		push 32
		putc
		push 112
		putc
		push 114
		putc
		push 111
		putc
		push 103
		putc
		push 114
		putc
		push 97
		putc
		push 109
		putc
		push 32
		putc
		push 99
		putc
		push 97
		putc
		push 110
		putc
		push 32
		putc
		push 115
		putc
		push 111
		putc
		push 108
		putc
		push 118
		putc
		push 101
		putc
		push 32
		putc
		push 115
		putc
		push 113
		putc
		push 117
		putc
		push 97
		putc
		push 114
		putc
		push 101
		putc
		push 95
		putc
		push 101
		putc
		push 113
		putc
		push 117
		putc
		push 97
		putc
		push 116
		putc
		push 105
		putc
		push 111
		putc
		push 110
		putc
		push 33
		putc
		push 10
		putc
		push 69
		putc
		push 110
		putc
		push 116
		putc
		push 101
		putc
		push 114
		putc
		push 32
		putc
		push 116
		putc
		push 104
		putc
		push 101
		putc
		push 32
		putc
		push 118
		putc
		push 97
		putc
		push 108
		putc
		push 117
		putc
		push 101
		putc
		push 115
		putc
		push 32
		putc
		push 111
		putc
		push 102
		putc
		push 32
		putc
		push 99
		putc
		push 111
		putc
		push 101
		putc
		push 102
		putc
		push 102
		putc
		push 105
		putc
		push 99
		putc
		push 105
		putc
		push 101
		putc
		push 110
		putc
		push 116
		putc
		push 115
		putc
		push 58
		putc
		push 10
		putc
		ret

:OUTRO
		push 71
		putc
		push 111
		putc
		push 111
		putc
		push 100
		putc
		push 98
		putc
		push 121
		putc
		push 101
		putc
		push 33
		putc
		push 10
		putc
		ret

:NUMBER_OF_ROOTS
		push 84
		putc
		push 104
		putc
		push 101
		putc
		push 32
		putc
		push 99
		putc
		push 111
		putc
		push 117
		putc
		push 110
		putc
		push 116
		putc
		push 32
		putc
		push 111
		putc
		push 102
		putc
		push 32
		putc
		push 114
		putc
		push 111
		putc
		push 111
		putc
		push 116
		putc
		push 115
		putc
		push 32
		putc
		push 61
		putc
		push 32
		putc
		ret

:X_ONE
		push 120
		putc
		push 49
		putc
		push 32
		putc
		push 61
		putc
		push 32
		putc
		ret

:X_TWO
		push 120
		putc
		push 50
		putc
		push 32
		putc
		push 61
		putc
		push 32
		putc
		ret