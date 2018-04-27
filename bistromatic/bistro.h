/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bistro.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 19:19:56 by mmoros            #+#    #+#             */
/*   Updated: 2018/04/11 10:27:03 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BISTRO_H
# define BISTRO_H

# include "libft/libft.h"

# define BUFSIZE 32

typedef struct		s_num2
{
	int				value;
}					t_num2;

typedef struct		s_num
{
	unsigned int	*left;
	unsigned int	*right;
	int				cut;
	int				zeros;
	unsigned int	ldig;
	unsigned int	rdig;
	char			sign;		//-1 and 1? or 0 and 1?
}					t_num;

typedef struct		s_equ
{
	char			op;
	struct s_equ	*up;
	struct s_equ	*left;
	struct s_equ	*right;
	struct s_num	*value;
}					t_equ;

t_equ				*new_equ(char op, t_equ *up, t_equ *left, t_num *value);
t_num				*new_num(char **equ, int radix);
t_equ				*equ_home(t_equ *parent, char **equ, int radix);
int					is_number(char equ, int radix);
t_equ				*solve(t_equ *equ);

#endif
