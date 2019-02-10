/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list_type.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgelbard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 00:27:29 by jgelbard          #+#    #+#             */
/*   Updated: 2018/10/01 00:27:29 by jgelbard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_LIST_TYPE_H
# define COMMAND_LIST_TYPE_H
# include "server.h"

struct	s_command_list
{
	t_command				*cmd;
	struct s_command_list	*next;
};

#endif
