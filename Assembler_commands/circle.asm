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
				
				push 25
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
		call MAKE_CIRCLE
		call PRINT_CIRCLE
		ret