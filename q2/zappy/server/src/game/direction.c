/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direction.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgelbard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 00:25:05 by jgelbard          #+#    #+#             */
/*   Updated: 2018/10/01 00:25:05 by jgelbard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "player_type.h"

#define MIN_DIRECTION NORTH
#define NUM_DIRECTIONS 8
#define DNORM(d) ((d) - MIN_DIRECTION)
#define DCLAMP(d) ((((d) + NUM_DIRECTIONS) % NUM_DIRECTIONS) + MIN_DIRECTION)

int		direction_sub(int d1, int d2)
{
	return (DCLAMP(DNORM(d1) - DNORM(d2)));
}

int		direction_add(int d1, int d2)
{
	return (DCLAMP(DNORM(d1) + DNORM(d2)));
}

int		opposite_direction(int d)
{
	return (direction_add(d, DCLAMP(NUM_DIRECTIONS / 2)));
}

int		perceived_direction(int d, t_player *p)
{
	return (direction_sub(d, p->facing));
}
