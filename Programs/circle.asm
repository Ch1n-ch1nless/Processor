		call MAIN
		hlt

:MAKE_LIGHT_CIRCLE
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
				
				push 4096
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

:MAKE_DARK_CIRCLE
		push 0                   
		push rax
		jmp FILL_STRING
	
	:FILL_STRING
			push 0           
			push rbx
			
		:MAKE_DARK_POINT
				pop rax  
				push 256
				mul
				pop rbx
				add
				push 196608
				add
				push rcx
	
				pop rbx
				push 107
				sub
				pop rbx
				push 107
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
				
				push 2116
				jb SKIP_PIXEL

				push 0
				push [rcx]
				
			:SKIP_PIXEL
					pop rbx
					push 1
					add
					push rbx

					pop rbx   
					push 256
					ja MAKE_DARK_POINT
		
		pop rax
		push 1
		add
		push rax

		pop rax
		push 256
		ja FILL_STRING
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
		call MAKE_LIGHT_CIRCLE
		call MAKE_DARK_CIRCLE
		call DRAW_CIRCLE
		ret