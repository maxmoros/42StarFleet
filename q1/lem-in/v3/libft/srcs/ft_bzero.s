# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    ft_bzero.s                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmoros <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/28 10:52:34 by mmoros            #+#    #+#              #
#    Updated: 2019/01/28 10:52:36 by mmoros           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

section	.text
		global ft_bzero

ft_bzero:
		cmp		rsi, 0
		jle		exit

clear:
		mov		byte[rdi], 0
		inc		rdi
		dec		rsi
		jnz		clear

exit:
		ret
