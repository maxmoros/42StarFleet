/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 09:08:49 by mmoros            #+#    #+#             */
/*   Updated: 2018/04/30 00:28:25 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"
# include <stdarg.h>
# include <stddef.h>

typedef struct		s_conv
{
	char			*prefix;
	int				i;
	char			flags;
	int				width;
	int				precision;
	char			length;
	int				(*type)(va_list, struct s_conv*);
	struct s_conv	*next;
	int				j;
	int				padding;
}					t_conv;

typedef int			(*t_func)(t_conv*);

int					ft_printf(char *str, ...);
t_conv				*new_conv(char **str);
t_conv				*pf_chomp(char *str, char *error);
int					parse_conv(char *str, t_conv *node, int *i);
void				print_nodes(t_conv *node);
t_conv				*free_conv(t_conv *node);
int					sum_printed(t_conv *node);

int					do_conv(va_list ap, t_conv *node, char *error);
intmax_t			get_length(va_list ap, char length);
uintmax_t			get_ulength(va_list ap, char length);
int					padding(t_conv *node);
int					zpadding(int i);
int					conv_s(va_list ap, t_conv *node);
int					conv_di(va_list ap, t_conv *node);
int					conv_o(va_list ap, t_conv *node);
int					conv_u(va_list ap, t_conv *node);
int					conv_p(va_list ap, t_conv *node);
int					conv_x(va_list ap, t_conv *node);
int					conv_xx(va_list ap, t_conv *node);
int					conv_c(va_list ap, t_conv *node);

int					put_intmax_t(intmax_t num, char print);
int					put_uintmax_t(uintmax_t num, char print);

int					count_bigoct(uintmax_t oct);
int					put_bigoct(uintmax_t oct);
int					put_bighex(uintmax_t hex, t_conv *node, char format);

#endif
