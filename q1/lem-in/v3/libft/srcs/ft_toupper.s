extern ft_isalpha
section .text
	global ft_toupper

ft_toupper:
	mov		rbx, rdi
	call	ft_isalpha
	cmp		rax, 0
	jz		end
	and		rbx, -33

end:
	mov		rax, rbx
	ret 
