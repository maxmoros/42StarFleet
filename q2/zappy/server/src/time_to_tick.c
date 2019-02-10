/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_to_tick.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgelbard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 00:24:50 by jgelbard          #+#    #+#             */
/*   Updated: 2018/10/01 00:24:50 by jgelbard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

#define NSEC_PER_SEC 1000000000
#define NSEC_PER_TICK (NSEC_PER_SEC / g_opts.tickrate)

static struct timespec	g_timestamp;
static long				g_next_tick_nsec;
static int				g_ticks;

int						get_elapsed_ticks(void)
{
	return (g_ticks);
}

void					init_tick_timer(void)
{
	g_ticks = 0;
	g_next_tick_nsec = NSEC_PER_TICK;
	clock_gettime(CLOCK_MONOTONIC_RAW, &g_timestamp);
}

long					timediff(struct timespec *late, struct timespec *early)
{
	return ((late->tv_sec - early->tv_sec) * NSEC_PER_SEC
			+ late->tv_nsec - early->tv_nsec);
}

int						have_we_ticked(void)
{
	struct timespec	now;
	long			diff;

	clock_gettime(CLOCK_MONOTONIC_RAW, &now);
	diff = timediff(&now, &g_timestamp);
	assert(diff >= 0);
	g_next_tick_nsec -= diff;
	memcpy(&g_timestamp, &now, sizeof(now));
	if (g_next_tick_nsec <= 0)
	{
		g_ticks += 1;
		g_next_tick_nsec = NSEC_PER_TICK;
		return (1);
	}
	else
		return (0);
}
