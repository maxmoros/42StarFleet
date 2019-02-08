section .text
	global	ft_isdigit

ft_isdigit:
	xor		rax, rax
	sub		rdi, 0x30
	cmp		rdi, 0x9
	setbe	al

end:
	ret
