global ft_memcpy

	section .text
ft_memcpy:
	mov		rax, rdi
	cmp		rsi, 0
	je		end
	cmp		rdx, 0
	je		end
	mov		rcx, rdx
	cld
	rep		movsb

end:
	ret
