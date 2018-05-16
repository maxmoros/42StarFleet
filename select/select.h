/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <mmoros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 10:17:43 by mmoros            #+#    #+#             */
/*   Updated: 2018/05/15 20:00:23 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SELECT_H
# define SELECT_H

# include "libft/libft.h"
# include <termcap.h>
# include <termios.h>
# include <term.h>
# include <stdio.h>

typedef struct		s_item
{
	char			*name;
	char			state;
	struct s_item	*next;
	struct s_item	*prev;
}					t_item;

typedef struct		s_table
{
	t_item			*list;
}					t_table;

typedef struct		s_select
{
	char			*termtype;
	char			*buffer;
	struct termios	orig;
	struct termios	term;
	t_table			*table;
}					t_select;

void				clear_term(void);

t_item				*build_list(char **input);
void				free_item_list(t_item *node);

t_table				*new_table(char **input);
void				free_table(t_table *node);

t_select			*init_select(char **input);
int					free_select(t_select *node, int out);

#endif