/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_launcher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/15 14:10:00 by ybalkan           #+#    #+#             */
/*   Updated: 2026/08/16 21:17:57 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libunit.h"

int	ok_test(void);
int	ko_test(void);
int	segv_test(void);
int	bus_test(void);
int	abrt_test(void);
int	fpe_test(void);
int	pipe_test(void);
int	ill_test(void);

int	dummy_tests_launcher(void)
{
	t_unit_test	*testlist;

	testlist = NULL;
	load_test(&testlist, "DUMMY", "OK test", &ok_test);
	load_test(&testlist, "DUMMY", "KO test", &ko_test);
	load_test(&testlist, "DUMMY", "SIGSEGV test", &segv_test);
	load_test(&testlist, "DUMMY", "SIGBUS test", &bus_test);
	load_test(&testlist, "DUMMY", "SIGABRT test", &abrt_test);
	load_test(&testlist, "DUMMY", "SIGFPE test", &fpe_test);
	load_test(&testlist, "DUMMY", "SIGPIPE test", &pipe_test);
	load_test(&testlist, "DUMMY", "SIGILL test", &ill_test);
	return (launch_tests(&testlist));
}
