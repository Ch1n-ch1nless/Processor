		call MAIN
		hlt

; Fills video memory cells with a color code if they match the circle equation
;
; Arguments:
;	[0] -- x-coordinate of circle
;	[1] -- y-coordinate of circle
;	[2] -- square radius of circle
; 	[3] -- color of circle
; 	[4] -- size of videomemory
;	[5] -- begin of videomemory
;
; Clobbers:
;	rax -- y-coordinate
;	rbx -- x-coordinate
;	rcx -- index of RAM
;
; Returns:
;	video memory [0x30000-0x40000]
;
:MAKE_LIGHT_CIRCLE
		push 0
		pop rax
		jmp fill_line
	
	:fill_line
			push 0
			pop rbx
			
		:loop
				push rax
				push [4] ; push in stack size of video memory
				mul
				push rbx
				add
				push [5] ; push begin of video memory
				add
				pop rcx

				push [9]   ; push black color
				pop [rcx]
	
				push rbx
				push [0] ; push x-coordinate of light circle
				sub
				push rbx
				push [0] ; push x-coordinate of light circle
				sub
				mul

				push rax
				push [1] ; push y-coordinate of light circle
				sub
				push rax
				push [1] ; push y-coordinate of light circle
				sub
				mul

				add
				
				push [2] ; push square radius of light circle
				jb SKIP_POINT

				push [3] ; push color of light circle
				pop [rcx]
				
			:SKIP_POINT
					push rbx
					push 1
					add
					pop rbx

					push rbx   
					push [4] ; push size of video memory
					ja loop
		
		push rax
		push 1
		add
		pop rax

		push rax
		push [4] ; push size of video memory
		ja fill_line
		ret

; Fills video memory cells with a color code if they match the circle equation
;
; Arguments:
;	[6] -- x-coordinate of circle
;	[7] -- y-coordinate of circle
;	[8] -- square radius of circle
; 	[9] -- color of circle
; 	[4] -- size of videomemory
;	[5] -- begin of videomemory
;
; Clobbers:
;	rax -- y-coordinate
;	rbx -- x-coordinate
; 	rcx -- index of RAM
;
; Returns:
;	video memory [0x30000-0x40000]
;
:MAKE_DARK_CIRCLE
		push 0
		pop rax
		jmp fill_string
	
	:fill_string
			push 0
			pop rbx
			
		:make_dark_point
				push rax  
				push [4] ; push size of video memory
				mul
				push rbx
				add
				push [5] ; push begin of video memory
				add
				pop rcx
	
				push rbx
				push [6] ; push x-coordinate of dark circle
				sub
				push rbx
				push [6] ; push x-coordinate of dark circle
				sub
				mul

				push rax
				push [7] ; push y-coordinate of dark circle
				sub
				push rax
				push [7] ; push y-coordinate of dark circle
				sub
				mul

				add
				
				push [8] ; push square radius of dark circle
				jb SKIP_PIXEL

				push [9] ; push black color
				pop [rcx]
				
			:SKIP_PIXEL
					push rbx
					push 1
					add
					pop rbx

					push rbx   
					push [4] ; push size of video memory
					ja make_dark_point
		
		push rax
		push 1
		add
		pop rax

		push rax
		push [4] ; push size of video memory
		ja fill_string
		ret

; Draw all video memory
;
; Arguments:
;	[4] -- size of video memory
;	[5] -- begin of video memory
;
; Clobbers:
;	rax -- y-coordinate of pixel
;	rbx -- x-coordinate of pixel
;	rcx -- index of RAM
;
:DRAW_CIRCLE
		create_window ; make window [4] x [4]
		push 0
		pop rax

	:line	
			push 0
			pop rbx
		
		:pixel
				push rax
				push [4] ; push size of video memory
				mul
				push rbx
				add
				push [5] ; push begin of video memory
				add
				pop rcx
				
				set_pixel ; get color fron [rcx] and color pixel(rbx; rax) 

				push rbx
				push 1
				add
				pop rbx

				push rbx
				push [4] ; push size of video memory
				ja pixel

		push rax
		push 1
		add
		pop rax

		push rax
		push [4] ; push size of video memory
		ja line
		ret

; Make constants in RAM
;
; Arguments:
; 	RAM[0x0-0x9]
;
; Returns:
; 	constants in cells of RAM
; 
:MAKE_CONSTANTS
		push 128
		pop [0] ; in [0] keeps x-coordinate of light circle
		push 128
		pop [1] ; in [0] keeps y-coordinate of light circle
		push 4096
		pop [2] ; in [2] keeps radius of light circle
		push 16777054
		pop [3] ; in [3] keeps color of light circle

		push 256
		pop [4] ; in [4] keeps size of video memory
		push 196608
		pop [5] ; in [5] keeps begin of video memory

		push 107
		pop [6] ; in [6] keeps x-coordinate of dark circle
		push 128
		pop [7] ; in [7] keeps y-coordinate of dark circle
		push 2116
		pop [8] ; in [8] keeps radius of dark circle
		push 0
		pop [9] ; in [9] keeps color of dark circle
		ret 				

:MAIN
		call MAKE_CONSTANTS
		call MAKE_LIGHT_CIRCLE
		call MAKE_DARK_CIRCLE
		call DRAW_CIRCLE
		ret