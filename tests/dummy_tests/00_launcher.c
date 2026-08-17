/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_launcher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/15 14:10:00 by ybalkan           #+#    #+#             */
/*   Updated: 2026/08/17 20:47:20 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libunit.h"
#include <stdlib.h>

int	ft_ok_test(void);
int	ft_ko_test(void);
int	ft_segv_test(void);
int	ft_bus_test(void);
int	ft_abort_test(void);
int	ft_fpe_test(void);
int	ft_pipe_test(void);
int	ft_ill_test(void);

int	ft_dummy_tests(void)
{
	t_unit_test	*testlist;

	testlist = NULL;
	ft_load_test(&testlist, "DUMMY", "OK test", &ft_ok_test);
	ft_load_test(&testlist, "DUMMY", "KO test", &ft_ko_test);
	ft_load_test(&testlist, "DUMMY", "SIGSEGV test", &ft_segv_test);
	ft_load_test(&testlist, "DUMMY", "SIGBUS test", &ft_bus_test);
	ft_load_test(&testlist, "DUMMY", "SIGABRT test", &ft_abort_test);
	ft_load_test(&testlist, "DUMMY", "SIGFPE test", &ft_fpe_test);
	ft_load_test(&testlist, "DUMMY", "SIGPIPE test", &ft_pipe_test);
	ft_load_test(&testlist, "DUMMY", "SIGILL test", &ft_ill_test);
	return (ft_launch_tests(&testlist));
}
