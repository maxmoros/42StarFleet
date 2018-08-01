/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testpf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <mmoros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 20:08:26 by mmoros            #+#    #+#             */
/*   Updated: 2018/07/31 19:25:45 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

int		main()
{
	printf("%s is a test\n", "This");
	ft_printf("%s is a test\n", "This");
	printf("%s is a %s\n", "This", "test.");
	ft_printf("%s is a %s\n", "This", "test");

	ft_printf("%d%d yolo %d%d maxint = %d\n", 4, 2, 0, -0, 0x7FFFFFFF);

	return (0);
}
