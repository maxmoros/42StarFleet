%ifdef OSX
	%define SUCCESS 1
%elif LINUX
	%define SUCCESS 1024
%endif

section .text
	global ft_isprint

ft_isprint:
	cmp		rdi, 0x20 
	jb		false
	cmp		rdi, 0x7e
	ja		false
	mov		rax, SUCCESS
	jmp		end

false:
	mov		rax, 0

end:
	ret
