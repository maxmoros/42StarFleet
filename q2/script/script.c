/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   script.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/13 09:09:54 by mmoros            #+#    #+#             */
/*   Updated: 2018/07/15 21:01:10 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "script.h"

struct termios		og_tty;
struct winsize		og_win;
char				*filename;
int					scriptfd;
char				slavename[MAX_SLAVENAME];
char				buf[BUF_SIZE];
fd_set				ifd;
ssize_t				read_in;

void	makeraw(struct termios *t)
{
	t->c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP |
			INLCR | IGNCR | ICRNL | IXON | INPCK);
	t->c_oflag &= ~OPOST;
	t->c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN);
	t->c_cflag &= ~(CSIZE | PARENB);
	t->c_cflag |= CS8;
	t->c_cc[VMIN] = 1;
	t->c_cc[VTIME] = 0;
	ioctl(0, TIOCSETAF, &t);
}

int		pty_fork(int *mfd)
{
	int		sfd;
	int		tmp_cpid;

	*mfd = open("/dev/ptmx", O_RDWR | O_NOCTTY);
	ioctl(*mfd, TIOCPTYGRANT);
	ioctl(*mfd, TIOCPTYUNLK);
	ioctl(*mfd, TIOCPTYGNAME, slavename);
	tmp_cpid = fork();
	if (tmp_cpid)
		return (tmp_cpid);
	setsid();
	close(*mfd);
	sfd = open(slavename, O_RDWR);
	ioctl(sfd, TIOCSCTTY, 0);
	ioctl(sfd, TIOCSETAF, &og_tty);
	ioctl(sfd, TIOCSWINSZ, &og_win);
	dup2(sfd, STDIN_FILENO);
	dup2(sfd, STDOUT_FILENO);
	dup2(sfd, STDERR_FILENO);
	if (sfd > STDERR_FILENO)
		close(sfd);
	return (tmp_cpid);
}

void	finish(int lol)
{
	if (lol)
		;
	ioctl(STDIN_FILENO, TIOCSETAF, &og_tty);
	ft_putstr("Script done, output file is ");
	ft_putstr(filename);
	ft_putstr("\n");
	ft_putstr_fd("Script done on :D\n", scriptfd);
}

void	main_loop(int mfd)
{
	FD_ZERO(&ifd);
	FD_SET(STDIN_FILENO, &ifd);
	FD_SET(mfd, &ifd);
	select(mfd + 1, &ifd, NULL, NULL, NULL);
	if (FD_ISSET(STDIN_FILENO, &ifd))
	{
		if ((read_in = read(STDIN_FILENO, buf, BUF_SIZE)) <= 0)
			exit(0);
		if (write(mfd, buf, read_in) != read_in)
			exit(1);
	}
	if (FD_ISSET(mfd, &ifd))
	{
		if ((read_in = read(mfd, buf, BUF_SIZE)) <= 0)
			exit(0);
		if ((write(STDOUT_FILENO, buf, read_in) != read_in) |
			(write(scriptfd, buf, read_in) != read_in))
			exit(1);
	}
}

int		main(int ac, char **av, char **env)
{
	int		mfd;
	int		cpid;
	char	*argv[2];

	ioctl(0, TIOCGETA, &og_tty);
	ioctl(0, TIOCGWINSZ, &og_win);
	cpid = pty_fork(&mfd);
	argv[1] = NULL;
	if (!cpid)
	{
		execve((argv[0] = getenv("SHELL")), argv, env);
		return (1);
	}
	filename = (ac > 1 ? av[1] : "typescript");
	ft_putstr("Script start, output file is ");
	ft_putstr(filename);
	ft_putchar('\n');
	scriptfd = open(filename, O_WRONLY | O_CREAT | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
	cfmakeraw(&og_tty);
	signal(SIGCHLD, finish);
	while (1)
		main_loop(mfd);
	return (0);
}
