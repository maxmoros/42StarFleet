/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   script.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/13 09:10:40 by mmoros            #+#    #+#             */
/*   Updated: 2018/07/15 21:02:08 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCRIPT_H
# define SCRIPT_H

# include "libft/libft.h"
# include <sys/ioctl.h>
# include <sys/select.h>
# include <termios.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>

# define MAX_SLAVENAME 256
# define BUF_SIZE 256

extern	struct termios		og_tty;
extern	struct winsize		og_win;
extern	char				*filename;
extern	int					scriptfd;
extern	char				slavename[MAX_SLAVENAME];
extern	char				buf[BUF_SIZE];
extern	fd_set				ifd;
extern	ssize_t				numRead;

#endif
