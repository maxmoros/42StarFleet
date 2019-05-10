/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_md5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 21:07:36 by mmoros            #+#    #+#             */
/*   Updated: 2019/05/09 12:45:11 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>
#include <ft_md5.h>

t_md5			g_md5;

static const uint32_t	g_s[] =
{
	7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17,22, 5, 9, 14,
	20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 4, 11, 16, 23, 4, 11,
	16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 6, 10, 15, 21, 6, 10, 15, 21,
	6, 10, 15, 21, 6, 10, 15, 21
};

static const uint32_t	g_k[] =
{
	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
	0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
	0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
	0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
	0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
	0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
	0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
	0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
	0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
	0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
	0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
	0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
	0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
};

static void				md5_digest()
{
	int			i;
	uint8_t		raw;
	uint8_t		hex;

	i = -1;
	while (++i < 16)
	{
		raw = g_md5.digest[i];
		hex = raw >> 4;
		g_md5.hex_digest[i * 2] = (hex < 10 ? '0' + hex : 'a' + hex - 10);
		hex = raw & 0x0F;
		g_md5.hex_digest[i * 2 + 1] = (hex < 10 ? '0' + hex : 'a' + hex - 10);
	}
	g_md5.hex_digest[32] = '\0';
}

void					init_md5()
{
	g_md5.a_result = INIT_A;
	g_md5.b_result = INIT_B;
	g_md5.c_result = INIT_C;
	g_md5.d_result = INIT_D;
	g_md5.a_block = INIT_A;
	g_md5.b_block = INIT_B;
	g_md5.c_block = INIT_C;
	g_md5.d_block = INIT_D;
}

static void				md5_hash_dispatch(uint32_t *f_func,
									uint32_t *g_index, int i)
{
	if (i < 16)
	{
		*f_func = (B_BLOCK & C_BLOCK) | ((~B_BLOCK) & D_BLOCK);
		*g_index = i;
	}
	else if (i < 32)
	{
		*f_func = (D_BLOCK & B_BLOCK) | ((~D_BLOCK) & C_BLOCK);
		*g_index = (5 * i + 1) % 16;
	}
	else if (i < 48)
	{
		*f_func = B_BLOCK ^ C_BLOCK ^ D_BLOCK;
		*g_index = (3 * i + 5) % 16;
	}
	else
	{
		*f_func = C_BLOCK ^ (B_BLOCK | (~D_BLOCK));
		*g_index = (7 * i) % 16;
	}	
}

static void				md5_main_loop()
{
	int			i;
	uint32_t	f_func;
	uint32_t	g_index;

	g_md5.a_block = g_md5.a_result;
	g_md5.b_block = g_md5.b_result;
	g_md5.c_block = g_md5.c_result;
	g_md5.d_block = g_md5.d_result;
	i = -1;
	while (++i < 64)
	{
		md5_hash_dispatch(&f_func, &g_index, i);
		f_func += A_BLOCK + g_k[i] + g_md5.m[g_index];
		A_BLOCK = D_BLOCK;
		D_BLOCK = C_BLOCK;
		C_BLOCK = B_BLOCK;
		B_BLOCK += LROT(f_func, g_s[i]);
	}
	g_md5.a_result += A_BLOCK;
	g_md5.b_result += B_BLOCK;
	g_md5.c_result += C_BLOCK;
	g_md5.d_result += D_BLOCK;
}

void					md5(t_512chunk *chunk)
{
	ft_putstr("Doin md5\n");
	ft_memcpy(g_md5.m, chunk->c, 64);
	md5_main_loop();
	ft_memcpy(g_md5.digest, &g_md5.a_result, 16);
	md5_digest();
	ft_putstr(g_md5.hex_digest);
	ft_putchar('\n');
}
