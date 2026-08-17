/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_bus_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/15 14:35:00 by ybalkan           #+#    #+#             */
/*   Updated: 2026/08/17 21:01:13 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

int	ft_bus_test(void)
{
	int		fd;
	char	*addr;

	fd = open("/tmp/bus_test", O_CREAT | O_RDWR, 0644);
	if (fd == -1)
		return (-1);
	addr = mmap(NULL, getpagesize(), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (addr == MAP_FAILED)
	{
		close(fd);
		return (-1);
	}
	addr[4096] = 42;
	munmap(addr, getpagesize());
	close(fd);
	return (0);
}
