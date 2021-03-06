/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <mmoros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 19:08:55 by mmoros            #+#    #+#             */
/*   Updated: 2018/05/29 16:53:05 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "../libft/libft.h"
# include <stdio.h>

typedef struct		s_ops
{
	int				(*f)();
	struct s_ops	*next;
	char			*op;
}					t_ops;

typedef struct		s_stack
{
	int				*a;
	int				*b;
	int				i;
	int				j;
	int				size;
	int				moves;
	struct s_ops	*ops_list;
	struct s_ops	*op;
}					t_stack;

typedef int			(*t_func)(t_stack*);

void				delay(int sec);

int					median_ab(int *tab, int size, int ab, int sub_med);
int					sort_three_a(t_stack *st);
int					sort_stack(t_stack *stack);
void				triple_init_a(t_stack *st, int size,
									int median[2], int push[2]);
void				triple_init_b(t_stack *st, int size,
									int median[2], int push[2]);
void				sort_stack_a(t_stack *stack, int size, int x, int y);
void				sort_stack_b(t_stack *stack, int size, int x, int y);

void				clean_ops(t_stack *stack);

t_stack				*build_stack(int size);
int					parse_input(t_stack *stack, char **nums);
void				print_stack(t_stack *stack);
int					in_order(t_stack *st, int size, int ab);
int					free_stack(t_stack *stack, int out);

void				init_ops(char op_list[11][4], t_func f[11]);
t_ops				*op_node(t_ops *next, int (*f)(), char *op);
void				add_op(t_stack *stack, int (*f)(), char *op);
void				op_print(t_stack *stack);
int					do_ops(t_stack *stack, t_ops *ops);

int					op_sa(t_stack *stack);
int					op_sb(t_stack *stack);
int					op_ss(t_stack *stack);
int					op_pa(t_stack *stack);
int					op_pb(t_stack *stack);
int					op_ra(t_stack *stack);
int					op_rb(t_stack *stack);
int					op_rr(t_stack *stack);
int					op_rra(t_stack *stack);
int					op_rrb(t_stack *stack);
int					op_rrr(t_stack *stack);

#endif
