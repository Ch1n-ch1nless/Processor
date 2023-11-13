		call MAIN
		hlt

;------------------------------------------------------------------------------

; Fills video memory cells with a color code if they match the circle equation
;
; Arguments:
;	memory cell [0] -- x-coordinate of circle
;	memory cell [1] -- y-coordinate of circle
;	memory cell [2] -- square radius of circle
; 	memory cell [3] -- color of circle
; 	memory cell [4] -- size of video memory
;	memory cell [5] -- begin of video memory
;
; Clobbers:
;	rax -- y-coordinate
;	rbx -- x-coordinate
;	rcx -- index of RAM
;
; Returns:
;	video memory [0x30000-0x40000]

:MAKE_CIRCLE
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

				push 0   ; push black color
				pop [rcx]
	
				push rbx
				push [0] ; push x-coordinate of circle
				sub
				push rbx
				push [0] ; push x-coordinate of circle
				sub
				mul

				push rax
				push [1] ; push y-coordinate of circle
				sub
				push rax
				push [1] ; push y-coordinate of circle
				sub
				mul

				add
				
				push [2] ; push square radius of circle
				jb skip_point

				push [3] ; push color of circle
				pop [rcx]
				
			:skip_point
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

;------------------------------------------------------------------------------

; Draws all video memory
;
; Arguments:
;	memory cell [4] -- size of video memory
;	memory cell [5] -- begin of video memory
;
; Clobbers:
;	rax -- y-coordinate of pixel
;	rbx -- x-coordinate of pixel
;	rcx -- index of RAM

:DRAW_CIRCLE
		create_window ; create window size equal to video memory size
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
				
				set_pixel ; get color from [rcx] and color pixel(rbx; rax) 

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

;------------------------------------------------------------------------------

; Sets arguments for the function to create a light circle
;
; Returns:
; 	constants in cells of RAM 
 
:SET_ARGS_FOR_LIGHT_CIRCLE
		push 128
		pop [0] ; keeps x-coordinate of light circle
		push 128
		pop [1] ; keeps y-coordinate of light circle
		push 4096
		pop [2] ; keeps square radius of light circle
		push 16777054
		pop [3] ; keeps color of light circle

		push 256
		pop [4] ; keeps size of video memory
		push 196608
		pop [5] ; keeps begin of video memory

		ret

;------------------------------------------------------------------------------

; Sets arguments for the function to create a dark circle
;
; Returns:
; 	constants in cells of RAM 
 
:SET_ARGS_FOR_DARK_CIRCLE
		push 107
		pop [0] ; keeps x-coordinate of dark circle
		push 128
		pop [1] ; keeps y-coordinate of dark circle
		push 2116
		pop [2] ; keeps square radius of dark circle
		push 0
		pop [3] ; keeps color of dark circle

		push 256
		pop [4] ; keeps size of video memory
		push 196608
		pop [5] ; keeps begin of video memory

		ret

;------------------------------------------------------------------------------				

:MAIN
		call SET_ARGS_FOR_LIGHT_CIRCLE
		call MAKE_CIRCLE
		call SET_ARGS_FOR_DARK_CIRCLE
		call MAKE_CIRCLE
		call DRAW_CIRCLE
		ret

;------------------------------------------------------------------------------