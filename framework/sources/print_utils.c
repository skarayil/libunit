/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/15 19:00:00 by ybalkan           #+#    #+#             */
/*   Updated: 2026/08/17 20:38:56 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libunit.h"
#include <unistd.h>

static char	*ft_get_status(int status)
{
	if (status == STATUS_OK)
		return ("[OK]");
	if (status == STATUS_KO)
		return ("[KO]");
	if (status == STATUS_SEGV)
		return ("[SIGSEGV]");
	if (status == STATUS_BUS)
		return ("[SIGBUS]");
	if (status == STATUS_ABRT)
		return ("[SIGABRT]");
	if (status == STATUS_FPE)
		return ("[SIGFPE]");
	if (status == STATUS_PIPE)
		return ("[SIGPIPE]");
	if (status == STATUS_ILL)
		return ("[SIGILL]");
	if (status == STATUS_TIMEOUT)
		return ("[TIMEOUT]");
	return ("[UNKNOWN]");
}

static void	ft_putstr(char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
}

static void	ft_putnbr(int n)
{
	char	c;
	long	nbr;

	nbr = n;
	if (nbr < 0)
	{
		write(1, "-", 1);
		nbr = -nbr;
	}
	if (nbr > 9)
		ft_putnbr(nbr / 10);
	c = '0' + nbr % 10;
	write(1, &c, 1);
}

static char	*ft_get_color(int status)
{
	if (status == STATUS_OK)
		return (C_GREEN);
	if (status == STATUS_KO)
		return (C_RED);
	if (status == STATUS_SEGV)
		return (C_YELLOW);
	if (status == STATUS_BUS)
		return (C_MAGENTA);
	if (status == STATUS_TIMEOUT)
		return (C_BLUE);
	if (status >= STATUS_ABRT && status <= STATUS_ILL)
		return (C_CYAN);
	return (C_RED);
}

t_bool	ft_print_all(t_result_buf *buf)
{
	int	i;
	int	passed;

	i = 0;
	passed = 0;
	while (i < buf->count)
	{
		ft_putstr(buf->data[i].func);
		ft_putstr(": ");
		ft_putstr(buf->data[i].test_name);
		ft_putstr(" : ");
		ft_putstr(ft_get_color(buf->data[i].status));
		ft_putstr(ft_get_status(buf->data[i].status));
		ft_putstr(C_RESET);
		ft_putstr("\n");
		if (buf->data[i].status == STATUS_OK)
			passed++;
		i++;
	}
	ft_putnbr(passed);
	write(1, "/", 1);
	ft_putnbr(buf->count);
	ft_putstr(" tests checked\n");
	return ((t_bool)(passed == buf->count));
}
