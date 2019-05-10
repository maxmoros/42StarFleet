extern	ft_isalpha
extern	ft_isdigit

section .text
	global	ft_isalnum

ft_isalnum:
	mov		rbx, rdi
	call	ft_isalpha
	cmp		rax, 0
	jne		end
	mov		rdi, rbx
	call	ft_isdigit

end:
	ret
