		call MAIN
		hlt
:OUT
		pop rax
		out
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

		pop rcx
		pop rdx
		ja FIB
		ret
:READ
		in
		push rdx
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