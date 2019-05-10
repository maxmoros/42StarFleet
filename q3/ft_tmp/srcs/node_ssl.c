/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_ssl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 12:27:31 by mmoros            #+#    #+#             */
/*   Updated: 2019/05/09 18:34:54 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>

t_ft_ssl	g_ft_ssl;

int		set_hash(char *hash)
{
	ft_putstr("Setting Hash\n");
	if ((!ft_strcmp(hash, "md5") && (g_ft_ssl.hash = md5)) ||
		(!ft_strcmp(hash, "sha256") && (g_ft_ssl.hash = sha256)))
		return (0);
	return (1);
}

void	print_flags()
{
	ft_putstr("Flags -");
	if (g_ft_ssl.flags & FLAG_P)
		ft_putchar('p');
	if (g_ft_ssl.flags & FLAG_Q)
		ft_putchar('q');
	if (g_ft_ssl.flags & FLAG_R)
		ft_putchar('r');
	if (g_ft_ssl.flags & FLAG_S)
		ft_putchar('s');
	ft_putchar('\n');
}

int		set_flags(int *argc, char ***args)
{
	ft_putstr("Setting Flags\n");
	g_ft_ssl.flags = 0;
	while (*argc && ***args == '-')
	{
		(*argc)--;
		if ((**args)[1] == 'p')
			g_ft_ssl.flags |= FLAG_P;
		else if ((**args)[1] == 'q')
			g_ft_ssl.flags |= FLAG_Q;
		else if ((**args)[1] == 'r')
			g_ft_ssl.flags |= FLAG_R;
		else if ((**args)[1] == 's')
			g_ft_ssl.flags |= FLAG_S;
		else
			return (1);
		if (*argc)
			(*args)++;
	}
	print_flags();
	return (0);
}
