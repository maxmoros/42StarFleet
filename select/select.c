/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <mmoros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 10:18:38 by mmoros            #+#    #+#             */
/*   Updated: 2018/05/14 21:07:27 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"

int		init_termdata(char **buffer, char *termtype)
{
	if (!(*buffer = (char*)ft_memalloc(sizeof(char) * 2048)))
		return (0);
	if (tgetent(*buffer, termtype) < 1)
	{
		free(*buffer);
		return (0);
	}
	return (1);
}

int		set_term(struct termios *orig, struct termios *new)
{
	if (tcgetattr(0, orig) == -1 || tcgetattr(0, new) == -1)
		return (-1);
	new->c_lflag &= ~(ICANON);
	new->c_lflag &= ~(ECHO);
	new->c_cc[VMIN] &= 1;
	new->c_cc[VTIME] &= 0;
	if (tcsetattr(0, TCSADRAIN, new) == -1)
		return (-1);
	return (1);
}

int		input_loop(void)
{
	char	buff[3];

	clear_term();
	while (1)
	{
		read(0, buff, 3);
		printf("buff = %d, %d, %d\n", buff[0], buff[1], buff[2]);
		buff[1] = 0;
		buff[2] = 0;
	}
	return (1);
}

int		ft_select(char **input)
{
	char			*termtype;
	char			*buffer;
	struct termios	orig;
	struct termios	new;

	buffer = NULL;
	info = NULL;
	init_termdata(&buffer, (termtype = getenv("TERM")));
	printf("termtype is %s, buffer is %s\n", termtype, buffer);
	set_term(&orig, &new);
	input_loop();
	return (1);
}

int		main(int ac, char **av)
{
	if (ac > 2)
		ft_select(av + 1);
	return (0);
}
