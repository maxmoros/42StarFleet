	global ft_puts

%define WRITE 0x02000004

	section .data

newline:	db 0x0a
nullstr:	db '(null)'

	section .text

ft_puts:
	mov		rdx, 0
	mov		rsi, rdi
	mov		rdi, 1
	cmp		rsi, 0
	jne		str_len

null_arg:
	lea		rsi, [rel nullstr]
	mov		rdx, 6
	jmp		write_str
	
str_len:
	inc		rdx
	cmp		byte[rsi + rdx], 0
	jnz		str_len

write_str:
	mov		rax, WRITE
	syscall
	jc		fail

end_char:
	mov		rax, WRITE
	lea		rsi, [rel newline]
	mov		rdx, 1
	syscall
	mov		rax, 1
	jnc		end

fail:
	mov		eax, -1

end:
	ret 

