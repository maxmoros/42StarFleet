%define		MACHO_SYSCALL(mode)	0x2000000 | mode
%define		STDIN				0
%define		STDOUT				1
%define		READ				3
%define		WRITE				4
%define		BUFF_SIZE			0x400

	global ft_cat

	section .bss
buffer:
	.buf	resb BUFF_SIZE

	section .text
ft_cat:
	push	r12
	mov		r12, rdi
	lea		rsi, [rel buffer.buf]

cat_read:
	mov		rdx, BUFF_SIZE
	mov		rax, MACHO_SYSCALL(READ)
	syscall
	jc		end
	cmp		rax, 0
	jz		end

cat_write:
	mov		r12, rdi
	mov		rdi, STDOUT		;fd = 1
	mov		rdx, rax		;read size

	mov		rax, MACHO_SYSCALL(WRITE)
	syscall
	jc		end

	mov		rdi, r12
	jmp		cat_read

end:
	pop		r12
	ret
