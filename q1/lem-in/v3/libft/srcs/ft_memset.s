global ft_memset

	section .text
ft_memset:
	mov		r8, rdi
	mov		rax, rsi
	mov		rcx, rdx
	cld
	rep		stosb
	mov		rax, r8

end:
	ret
