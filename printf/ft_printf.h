/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 09:08:49 by mmoros            #+#    #+#             */
/*   Updated: 2018/04/26 13:38:03 by mmoros           ###   ########.fr       */
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
	char			flags;
	int				width;
	int				precision;
	char			length;
	int				(*type)();
	struct s_conv	*next;
}					t_conv;

typedef int			(*t_func)(t_conv*);

void				delay(int number_of_seconds);

t_conv				*new_conv(int len, char *str);
t_conv				*pf_chomp(char *str, char *error);
void				print_nodes(t_conv *node);

int					percent(t_conv *node);
int					conv_s(t_conv *node);
int					conv_d(t_conv *node);
int					conv_o(t_conv *node);
int					conv_u(t_conv *node);
int					conv_p(t_conv *node);
int					conv_i(t_conv *node);
int					conv_x(t_conv *node);
int					conv_X(t_conv *node);
int					conv_c(t_conv *node);

#endif
