		call MAIN
		hlt

:MAKE_CIRCLE
		push 0                   
		push rax
		jmp FILL_LINE
	
	:FILL_LINE
			push 0           
			push rbx
			
		:LOOP
				pop rax  
				push 20
				mul
				pop rbx
				add
				push rcx

				push 32
				push [rcx]
	
				pop rbx
				push 10
				sub
				pop rbx
				push 10
				sub
				mul

				pop rax
				push 10
				sub
				pop rax
				push 10
				sub
				mul

				add
				
				push 49
				jb SKIP_POINT

				push 35
				push [rcx]
				
			:SKIP_POINT
					pop rbx
					push 1
					add
					push rbx

					pop rbx   
					push 20
					ja LOOP
		
		pop rax
		push 1
		add
		push rax

		pop rax
		push 20
		ja FILL_LINE
		ret

:PRINT_CIRCLE
		push 0
		push rax

	:LINE	
			push 0
			push rbx
		
		:CHAR
				pop rax
				push 20
				mul
				pop rbx
				add
				push rcx
				
				pop [rcx]
				putc 

				pop rbx
				push 1
				add
				push rbx

				pop rbx
				push 20
				ja CHAR

		push 10
		putc

		pop rax
		push 1
		add
		push rax

		pop rax
		push 20
		ja LINE
		ret		

:MAIN
		call INTRO
		call MAKE_CIRCLE
		call PRINT_CIRCLE
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
		push 76
		putc
		push 111
		putc
		push 111
		putc
		push 107
		putc
		push 32
		putc
		push 97
		putc
		push 116
		putc
		push 32
		putc
		push 116
		putc
		push 104
		putc
		push 105
		putc
		push 115
		putc
		push 32
		putc
		push 99
		putc
		push 105
		putc
		push 114
		putc
		push 99
		putc
		push 108
		putc
		push 101
		putc
		push 33
		putc
		push 10
		putc
		ret

:OUTRO
		push 10
		putc
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