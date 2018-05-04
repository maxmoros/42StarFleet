/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 19:08:55 by mmoros            #+#    #+#             */
/*   Updated: 2018/05/02 23:11:14 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H

# include "../libft/libft.h"

typedef struct		s_stack
{
	int				*a;
	int				*b;
	int				i;
	int				j;
	int				size;
}					t_stack;

typedef struct		s_ops
{
	int				(*f)();
	struct s_ops	*next;
}					t_ops;

typedef int			(*t_func)(t_stack*);

int					free_stack(t_stack *stack, t_ops *ops, int out);
t_stack				*build_stack(int size);
int					parse_input(t_stack *stack, char **nums);
void				print_stack(t_stack *stack);
t_ops				*get_ops(int *count);
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
