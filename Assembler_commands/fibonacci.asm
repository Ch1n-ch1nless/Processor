		call MAIN
		hlt
:OUT
		push 10
		putc
		call THE_ANSWER
		pop rax
		out
		push 10
		putc
		ret

:FIB
		pop rbx	  ; rax = rbx, rbx = rax + rbx
		pop rax
		pop rbx
		add
		push rbx
		push rax 

		push 1    ; rcx += 1
		pop rcx
		add
		push rcx

		call PRINT_FIB

		pop rcx
		pop rdx
		ja FIB
		ret
:READ
		call INTRO
		in
		push rdx
		push 10
		putc
		ret

:FILL_REGS
		push 0
		push rax
		push 0
		push rcx
		push 1
		push rbx
		ret
		
:MAIN
		call READ	   ; function reading number of fibonacci
		call FILL_REGS     ; function filling rax, rbx and rcx
		call FIB	   ; Search the fibonacci number
		call OUT	   ; Print the number  
		ret

:INTRO
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
		push 110
		putc
		push 117
		putc
		push 109
		putc
		push 98
		putc
		push 101
		putc
		push 114
		putc
		push 32
		putc
		push 111
		putc
		push 102
		putc
		push 32
		putc
		push 102
		putc
		push 105
		putc
		push 98
		putc
		push 111
		putc
		push 110
		putc
		push 97
		putc
		push 99
		putc
		push 99
		putc
		push 105
		putc
		push 58
		putc
		push 32
		putc
		ret

:THE_ANSWER
		push 84
		putc
		push 104
		putc
		push 101
		putc
		push 32
		putc
		push 97
		putc
		push 110
		putc
		push 115
		putc
		push 119
		putc
		push 101
		putc
		push 114
		putc
		push 58
		putc
		push 32
		putc
		ret

:PRINT_FIB
		push 91
		putc
		pop rcx
		out
		push 93
		putc
		push 32
		putc
		push 61
		putc
		push 32
		putc
		pop rax
		out
		push 10
		putc
		ret