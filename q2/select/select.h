/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <mmoros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 10:17:43 by mmoros            #+#    #+#             */
/*   Updated: 2018/05/16 19:38:34 by mmoros           ###   ########.fr       */
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
	int				cols;
	int				rows;
}					t_table;

typedef struct		s_select
{
	char			*termtype;
	char			*buffer;
	struct termios	orig;
	struct termios	term;
	int				width;
	int				height;
	int				elements;
	t_table			*table;
}					t_select;

void				clear_term(void);

void				navkey(t_select *node, char key);
void				navkey_select(t_select *node);

void				actkey_remove(t_select *node);

t_item				*build_list(char **input);
void				remove_item(t_select *node, t_item *item);
void				free_item_list(t_item *node);
void				print_item(t_item *node);

t_table				*new_table(char **input);
void				free_table(t_table *node);
void				set_table(t_select *node);
void				print_table(t_select *node);

int					init_termdata(char *buffer, char *termtype);
t_select			*init_select(char **input);
int					free_select(t_select *node, int out);

#endif