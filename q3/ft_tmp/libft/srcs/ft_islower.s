section .text
	global ft_islower

ft_islower:
	xor		rax, rax
	sub		rdi, 0x61
	cmp		rdi, 0x19
	setbe	al
	ret
