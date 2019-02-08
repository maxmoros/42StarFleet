global ft_strlen

	section .text
ft_strlen:
	xor		rax, rax
	cmp		rdi, 0
	je		end
	xor		rcx, rcx
	dec		rcx
	cld
	repne	scasb
	not		rcx
	dec		rcx
	add		rax, rcx

end:
	ret
	
