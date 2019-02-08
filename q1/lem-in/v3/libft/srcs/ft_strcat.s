section .text
	global	ft_strcat

ft_strcat:
	mov		rcx, rdi
	mov		rdx, rsi

str_end:
	cmp		byte[rcx], 0
	je		str_app
	inc		rcx
	jmp		str_end

str_app:
	cmp		byte[rdx], 0
	je		str_null
	mov		al, byte[rdx]
	mov		byte[rcx], al
	inc		rcx
	inc		rdx
	jmp		str_app

str_null:
	mov		byte[rcx], 0

end:
	mov		rax, rdi
	ret
