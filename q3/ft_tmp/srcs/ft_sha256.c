/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sha256.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 09:55:38 by mmoros            #+#    #+#             */
/*   Updated: 2019/05/09 19:37:22 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>
#include <ft_sha256.h>

t_sha256		g_sha256;

static const uint32_t	g_h_init[] =
{
	0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
	0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19
};

static const uint32_t	g_k[] =
{
   0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1,
   0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
   0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174, 0xe49b69c1, 0xefbe4786,
   0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
   0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147,
   0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
   0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85, 0xa2bfe8a1, 0xa81a664b,
   0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
   0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a,
   0x5b9cca4f, 0x682e6ff3, 0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
   0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

static void				sha256_digest()
{
	int			i;
	uint8_t		raw;
	uint8_t		hex;

	i = -1;
	while (++i < 32)
	{
		raw = g_sha256.digest[i];
		hex = raw & 0x0F;
		g_sha256.hex_digest[i * 2] = (hex < 10 ? '0' + hex : 'W' + hex);
		hex = raw >> 4;
		g_sha256.hex_digest[i * 2 + 1] = (hex < 10 ? '0' + hex : 'W' + hex);
	}
	g_sha256.hex_digest[64] = '\0';
}

void					init_sha256()
{
	ft_memcpy(g_sha256.x_result, g_h_init, 32);
}

static void				sha256_prep_chunk(uint32_t *w, uint32_t *chunk)
{
	int			i;
	uint32_t	t1;
	uint32_t	t2;
	
	ft_bzero(w, 256);
	ft_memcpy(w, chunk, 64);
	i = 15;
	while (++i < 64)
	{
		t1 = RROT(w[i - 15], 7) ^ RROT(w[i - 15], 18) ^ w[i - 15] >> 3;
		t2 = RROT(w[i - 2], 17) ^ RROT(w[i - 2], 19) ^ w[i - 2] >> 10;
		w[i] = w[i - 16] + t1 + w[i - 7] + t2;
	}
}

static void				sha256_main_loop()
{
	int			i;
	uint32_t	t1;
	uint32_t	t2;

	i = -1;
	while (++i < 64)
	{
		t1 = RROT(X_BLOCK[4], 6) ^ RROT(X_BLOCK[4], 11) ^ RROT(X_BLOCK[4], 25);
		t1 += (X_BLOCK[4] & X_BLOCK[5]) ^ ((~X_BLOCK[4]) & X_BLOCK[6]);
		t1 += X_BLOCK[7] + g_k[i] + g_sha256.w[i];
		t2 = RROT(X_BLOCK[0], 2) ^ RROT(X_BLOCK[0], 13) ^ RROT(X_BLOCK[0], 22);
		t2 += (X_BLOCK[0] & X_BLOCK[1]) ^ (X_BLOCK[0] & X_BLOCK[2]) ^
			(X_BLOCK[1] & X_BLOCK[2]);
		X_BLOCK[7] = X_BLOCK[6];
		printf("random g_block = \'%u\'\n", X_BLOCK[6]);
		X_BLOCK[6] = X_BLOCK[5];
		printf("random f_block = \'%u\'\n", X_BLOCK[5]);
		X_BLOCK[5] = X_BLOCK[4];
		X_BLOCK[4] = X_BLOCK[3] + t1;
		X_BLOCK[3] = X_BLOCK[2];
		X_BLOCK[2] = X_BLOCK[1];
		X_BLOCK[1] = X_BLOCK[0];
		X_BLOCK[0] = t1 + t2;
	}
	i = -1;
	while (++i < 8)
		X_RESULT[i] += X_BLOCK[i];
}

void				sha256(t_512chunk *chunk)
{
	ft_putstr("doing SHA256\n");
	flip_chunk();
	sha256_prep_chunk(g_sha256.w, chunk->c);
	ft_memcpy(g_sha256.x_block, g_sha256.x_result, 32);
	sha256_main_loop();
	ft_memcpy(g_sha256.digest, g_sha256.x_result, 32);
	sha256_digest();
	ft_putstr("(xxx) = ");
	ft_putstr(g_sha256.hex_digest);
	ft_putchar('\n');
}
