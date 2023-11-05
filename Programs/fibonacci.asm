		call MAIN
		hlt

; Prints the last fibonacci number 
;
; Arguments:
;	rax -- value of last fibonacci number
;
:OUT
		pop rax
		out
		push 10
		putc
		ret

; Evaluates and prints fibonacci number
;
; Arguments:
;	rdx -- amount of fibonacci numbers
; Clobbers:
;	rax, rbx, rcx
; Returns
;	rax -- last fibonacci number 
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

; Read the amount of fibonacci numbers
;
; Clobbers:
;	rdx -- amount of fibonacci numbers
:READ
		in
		push rdx
		push 10
		putc
		ret

; Fill registers by values of first and second fibonacci numbers and makes counter 
;
; Clobbers
;	rax -- fibonacci number with 0
;	rbx -- fibonacci number with 1
;	rcx -- counter
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