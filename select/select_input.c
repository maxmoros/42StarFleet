/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <mmoros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 18:43:19 by mmoros            #+#    #+#             */
/*   Updated: 2018/05/14 20:52:20 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"

void	clear_term(void)
{
	ft_putstr_fd(tgetstr("cl", NULL), 1);
}
