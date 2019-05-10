/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_md5.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 20:38:51 by mmoros            #+#    #+#             */
/*   Updated: 2019/05/09 12:26:24 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MD5
# define FT_MD5

# define INIT_A			0x67452301   //A
# define INIT_B			0xefcdab89   //B
# define INIT_C			0x98badcfe   //C
# define INIT_D			0x10325476   //D
# define A_BLOCK		g_md5.a_block
# define B_BLOCK		g_md5.b_block
# define C_BLOCK		g_md5.c_block
# define D_BLOCK		g_md5.d_block
# define LROT(x, i)		((x << i) | (x >> (32 - i)))

typedef struct		s_md5
{
	uint32_t		m[16];
	uint32_t		a_block;
	uint32_t		b_block;
	uint32_t		c_block;
	uint32_t		d_block;
	uint32_t		a_result;
	uint32_t		b_result;
	uint32_t		c_result;
	uint32_t		d_result;
	char			digest[16];
	char			hex_digest[33];
}					t_md5;

extern t_md5		g_md5;

#endif
