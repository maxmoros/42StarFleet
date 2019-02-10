#include "server.h"
#include "test.h"

void test_remembers_server_socket(void)
{
	assert(get_server_fd() != -1);
}

int random_fake_clients(fd_set *yesdata, fd_set *nodata, int nclients, int *yescount)
{
	int fd;
	int maxfd = 0;
	assert(nclients <= MAX_CLIENTS);
	socket_lookup_init(0);
	FD_ZERO(yesdata);
	FD_ZERO(nodata);
	int actual_yescount = 0;
	int rand;
	for (int i = 0; i < nclients; i++)
	{
		rand = random() % nclients;
		if (rand < *yescount)
		{
			fd = open("temp_test_file.txt", O_RDONLY | O_CREAT, 0644);
			FD_SET(fd, yesdata);
			++actual_yescount;
		}
		else
		{
			fd = socket(PF_INET, SOCK_STREAM, 0);
			FD_SET(fd, nodata);
		}
		if (fd > maxfd)
			maxfd = fd;
		socket_lookup_add(fd, ACTIVE_PLAYER);
	}
	*yescount = actual_yescount;
	return maxfd;
}

void	do_sockiter_test(fd_set *yes, int yescount, int max)
{
	for (int i = 0; i < 300000; i++)
	{
		int fd = iter_next_readable_socket();
		if (i % (yescount + 1) == yescount)
			assert(fd == -1);
		else
			assert(FD_ISSET(fd, yes));
	}
	while (iter_next_readable_socket() != -1)
		;
}

void test_can_iterate_through_readable_sockets()
{
	fd_set yesdata, nodata;
	int yescount = MAX_CLIENTS;
	int nclients = MAX_CLIENTS;
	int maxfd = random_fake_clients(&yesdata, &nodata, nclients, &yescount);
	do_sockiter_test(&yesdata, yescount, maxfd);
}


void test_client_connection_listener(void)
{
	test_server_listen();
	test_remembers_server_socket();
	test_can_iterate_through_readable_sockets();
	printf("%s: ok\n", __FILE__);
}
