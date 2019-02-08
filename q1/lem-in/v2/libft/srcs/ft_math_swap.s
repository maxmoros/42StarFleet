	global	ft_math_swap

	section .text

ft_math_swap:
	xchg	eax, dword[rdi]
	xchg	ecx, dword[rsi]
	xchg	dword[rdi], ecx
	xchg	dword[rsi], eax
	ret
