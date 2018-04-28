/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 09:08:49 by mmoros            #+#    #+#             */
/*   Updated: 2018/04/27 19:03:08 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"
# include <stdarg.h>
# include <stdio.h>

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
}					t_conv;

typedef int			(*t_func)(t_conv*);

void				delay(int number_of_seconds);

t_conv				*new_conv(char **str);
t_conv				*pf_chomp(char *str, char *error);
void				print_nodes(t_conv *node);
t_conv				*free_conv(t_conv *node);

int					do_conv(va_list ap, t_conv *node, char *error);
int					percent(va_list ap, t_conv *node);
int					conv_s(va_list ap, t_conv *node);
int					conv_di(va_list ap, t_conv *node);
int					conv_o(va_list ap, t_conv *node);
int					conv_u(va_list ap, t_conv *node);
int					conv_p(va_list ap, t_conv *node);
int					conv_x(va_list ap, t_conv *node);
int					conv_X(va_list ap, t_conv *node);
int					conv_c(va_list ap, t_conv *node);

#endif
