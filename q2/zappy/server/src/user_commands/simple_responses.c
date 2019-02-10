/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_responses.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgelbard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 00:25:18 by jgelbard          #+#    #+#             */
/*   Updated: 2018/10/01 00:25:18 by jgelbard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

char	*ok_response(void)
{
	char	*res;

	asprintf(&res, "ok\n");
	return (res);
}

char	*ko_response(void)
{
	char	*res;

	asprintf(&res, "ko\n");
	return (res);
}
