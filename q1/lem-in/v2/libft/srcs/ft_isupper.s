section .text
	global ft_isupper

ft_isupper:
	xor		rax, rax
	sub		rdi, 'A'
	cmp		rdi, 0x19
	setbe	al
	ret
