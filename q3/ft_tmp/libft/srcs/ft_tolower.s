extern ft_isalpha
section .text
	global ft_tolower

ft_tolower:
	mov		rbx, rdi
	call	ft_isalpha
	cmp		rax, 0
	jz		end
	or		rbx, 0x20

end:
	mov		rax, rbx
	ret 
