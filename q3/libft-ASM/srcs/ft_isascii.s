%ifdef OSX
	%define SUCCESS 1
%elif LINUX
	%define SUCCESS 1024
%endif

section .text
	global ft_isascii

ft_isascii:
	cmp		rdi, 0
	jb		false
	cmp		rdi, 0x7f
	ja		false
	mov		rax, SUCCESS
	jmp		end

false:
	mov		rax, 0

end:
	ret
