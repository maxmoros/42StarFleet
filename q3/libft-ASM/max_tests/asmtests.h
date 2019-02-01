/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asmtests.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 20:46:16 by mmoros            #+#    #+#             */
/*   Updated: 2019/01/29 20:46:17 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASMTESTS_H
# define ASMTESTS_H

# include "libfts.h"
# include <assert.h>
# include <limits.h>
# include <math.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <strings.h>
# include <string.h>
# include <ctype.h>

void	ft_putstr(char *str);
void	ft_putchar(int c);
void	ft_putnbr(int n);

void	ck_abs(void);
void	ck_bzero(void);
void	ck_islower(void);
void	ck_isspace(void);
void	ck_isto(int (ft_x)(int), int (sysx)(int), char *func);
void	ck_isupper(void);
void	ck_strdup(void);
void	ck_strcat(void);
void	ck_strlen(void);
void	ck_math_swap(void);
void	ck_memcpy(void);
void	ck_memset(void);
void	ck_puts(void);
void	ck_cat(void);

#endif
