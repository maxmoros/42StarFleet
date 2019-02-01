/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 20:45:56 by mmoros            #+#    #+#             */
/*   Updated: 2019/01/29 20:45:57 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asmtests.h"

void	run_tests1(void)
{
	ft_putstr("\nPART ONE:\n");
	ck_bzero();
	ck_strcat();
	ck_isto(ft_isalpha, isalpha, "ft_isalpha");
	ck_isto(ft_isdigit, isdigit, "ft_isdigit");
	ck_isto(ft_isalnum, isalnum, "ft_isalnum");
	ck_isto(ft_isascii, isascii, "ft_isascii");
	ck_isto(ft_toupper, toupper, "ft_toupper");
	ck_isto(ft_tolower, tolower, "ft_tolower");
	ck_puts();
}

void	run_tests2(void)
{
	ft_putstr("\nPART TWO:\n");
	ck_strlen();
	ck_memset();
	ck_memcpy();
	ck_strdup();
}

void	run_tests3(void)
{
	ft_putstr("\nPART THREE:\n");
	ck_cat();
}

void	run_tests4(void)
{
	ft_putstr("\nBONUS:\n");
	ck_abs();
	ck_islower();
	ck_isspace();
	ck_isupper();
	ck_math_swap();
	ft_putstr("\n");
}

int		main(void)
{
	run_tests1();
	run_tests2();
	run_tests3();
	run_tests4();
	return (0);
}
