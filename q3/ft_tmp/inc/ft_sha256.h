/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sha256.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 09:47:33 by mmoros            #+#    #+#             */
/*   Updated: 2019/05/09 19:37:26 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SHA256_H
# define FT_SHA256_H

# define X_BLOCK		g_sha256.x_block
# define X_RESULT		g_sha256.x_result
# define RROT(x, i)		((x >> i) | (x << (32 - i)))

typedef struct		s_sha256
{
	uint32_t		w[64];
	uint32_t		x_block[8];
	uint32_t		x_result[8];
	char			digest[32];
	char			hex_digest[65];
}					t_sha256;

extern t_sha256		g_sha256;

#endif
