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
				push 256
				mul
				pop rbx
				add
				push 196608
				add
				push rcx

				push 0
				push [rcx]
	
				pop rbx
				push 128
				sub
				pop rbx
				push 128
				sub
				mul

				pop rax
				push 128
				sub
				pop rax
				push 128
				sub
				mul

				add
				
				push 2024
				jb SKIP_POINT

				push 16777054
				push [rcx]
				
			:SKIP_POINT
					pop rbx
					push 1
					add
					push rbx

					pop rbx   
					push 256
					ja LOOP
		
		pop rax
		push 1
		add
		push rax

		pop rax
		push 256
		ja FILL_LINE
		ret

:DRAW_CIRCLE
		create_window
		push 0
		push rax

	:LINE	
			push 0
			push rbx
		
		:CHAR
				pop rax
				push 256
				mul
				pop rbx
				add
				push 196608
				add
				push rcx
				
				set_pixel 

				pop rbx
				push 1
				add
				push rbx

				pop rbx
				push 256
				ja CHAR

		pop rax
		push 1
		add
		push rax

		pop rax
		push 256
		ja LINE
		ret		

:MAIN
		call MAKE_CIRCLE
		
		ret