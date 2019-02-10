#include "server.h"
#include "clients_lookup.h"
#include "client_type.h"
#include "test.h"

int check_lookup_size(t_client **clients)
{
	int i;

	i = 0;
	while (clients[i])
		++i;
	return (i);
}

void test_can_make_and_free_client(void)
{
	t_client *c, *c2;

	c = new_client(9, 5, ACTIVE_PLAYER);
	c2 = new_client(13, 2, ACTIVE_PLAYER);
	assert(c->socket_fd == 9 && c2->socket_fd == 13);
	assert(c->id == 5 && c2->id == 2);
}

void populate_client_lookup_with_fake_data(void)
{
	bzero(g_clients, sizeof(g_clients));
	g_count_clients = 0;
	register_client(1, 99, ACTIVE_PLAYER);
	register_client(63, 729, ACTIVE_PLAYER);
	register_client(107, 24, ACTIVE_PLAYER);
}

void test_can_register_clients(void)
{
	populate_client_lookup_with_fake_data();
	assert(check_lookup_size(g_clients) == 3);
}

void test_getting_client_by_id(void)
{
	populate_client_lookup_with_fake_data();
	t_client **gc = g_clients;
	assert(get_client_by_id(99) == gc[0]);
	assert(get_client_by_id(729) == gc[1]);
	assert(get_client_by_id(24) == gc[2]);
}

void test_getting_client_by_socket_fd(void)
{
	populate_client_lookup_with_fake_data();
	t_client **gc = g_clients;
	assert(get_client_by_socket_fd(1) == gc[0]);
	assert(get_client_by_socket_fd(63) == gc[1]);
	assert(get_client_by_socket_fd(107) == gc[2]);
}

void test_unregister_client_by_id()
{
	t_client **gc = g_clients;
	t_client *to_remove = gc[1];
	populate_client_lookup_with_fake_data();
	unregister_client_by_id(to_remove->id);
	assert(gc[1] != to_remove);
	assert(gc[2] == NULL);
}

void test_client_lookup(void)
{
	test_can_make_and_free_client();
	test_can_register_clients();
	test_getting_client_by_id();
	test_getting_client_by_socket_fd();
	test_unregister_client_by_id();
	printf("%s: ok\n", __FILE__);
}
