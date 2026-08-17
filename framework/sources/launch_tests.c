/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_tests.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/15 10:45:00 by ybalkan           #+#    #+#             */
/*   Updated: 2026/08/17 20:44:39 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libunit.h"
#include <stdlib.h>

static int	ft_count_tests(t_unit_test *lst)
{
	int	n;

	n = 0;
	while (lst)
	{
		n++;
		lst = lst->next;
	}
	return (n);
}

static t_bool	ft_buf_init(t_result_buf *buf, int capacity)
{
	buf->data = (t_result *)malloc(sizeof(t_result) * capacity);
	if (!buf->data)
		return (FALSE);
	buf->count = 0;
	buf->capacity = capacity;
	return (TRUE);
}

static void	ft_run_all(t_unit_test *lst, t_result_buf *buf)
{
	int	i;

	i = 0;
	while (lst && i < buf->capacity)
	{
		ft_run_one(lst, buf, i);
		i++;
		lst = lst->next;
	}
	buf->count = i;
}

static void	ft_free_list(t_unit_test **lst)
{
	t_unit_test	*tmp;

	while (*lst)
	{
		tmp = (*lst)->next;
		free(*lst);
		*lst = tmp;
	}
}

int	ft_launch_tests(t_unit_test **lst)
{
	t_result_buf	buf;
	t_bool			all_ok;
	int				total;

	total = ft_count_tests(*lst);
	if (total == 0)
		return (0);
	if (ft_buf_init(&buf, total) == FALSE)
		return (-1);
	ft_run_all(*lst, &buf);
	all_ok = ft_print_all(&buf);
	free(buf.data);
	ft_free_list(lst);
	if (all_ok == TRUE)
		return (0);
	return (-1);
}
