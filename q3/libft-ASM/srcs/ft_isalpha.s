section .text
	global	ft_isalpha

ft_isalpha:
	xor		rax, rax
	and		rdi, -33
	sub		rdi, 0x41
	cmp		rdi, 0x19
	setbe	al

end:
	ret
