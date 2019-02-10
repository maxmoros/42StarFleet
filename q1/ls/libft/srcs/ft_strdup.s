extern ft_strlen
extern malloc
global ft_strdup

	section .text
ft_strdup:
	push	r12
	push	r13

	cld
	mov		r12, rdi		;save src pointer

	call	ft_strlen
	inc		rax				;room for null char
	mov		r13, rax		;save len for later
	mov		rdi,rax			;malloc size

;	xor		rax, rax		
;	xor		rcx, rcx
;	not		rcx				;flip to intmax
;	repnz	scasb			;rdi len to null
;	not		rcx				;len + 1
;	mov		r13, rcx		;save len
;	mov		rdi, rcx		;prepare size for malloc

	sub		rsp, 8
	call	malloc
	add		rsp, 8
	mov		rdi, rax		;destination pointer
	mov		rsi, r12		;source pointer
	mov		rcx, r13		;n characters
	rep		movsb			;move n chars

end:
	pop		r13
	pop		r12

	ret
