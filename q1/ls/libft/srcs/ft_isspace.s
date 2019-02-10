	global ft_isspace

	section .text
ft_isspace:
	mov		rax, 1
	cmp		rdi, 0x20
	je		end
	sub		rdi, 0x09
	cmp		rdi, 0x04
	jbe		end
	xor		rax, rax

end:
	ret
