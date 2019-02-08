global ft_abs

	section .text

ft_abs:
	mov		rax, rdi
	cmp		eax, 0
	jge		end
	neg		rax

end:
	ret
