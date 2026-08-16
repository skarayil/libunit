/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_tests.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/15 10:45:00 by ybalkan           #+#    #+#             */
/*   Updated: 2026/08/16 21:17:57 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libunit.h"

t_status	analyze(int status);
void		run_one(t_unit_test *lst, t_result_buf *buf, int i);

static int	count_tests(t_unit_test *lst)
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

static t_bool	buf_init(t_result_buf *buf, int capacity)
{
	buf->data = (t_result *)malloc(sizeof(t_result) * capacity);
	if (!buf->data)
		return (FALSE);
	buf->count = 0;
	buf->capacity = capacity;
	return (TRUE);
}

static void	run_all(t_unit_test *lst, t_result_buf *buf)
{
	int	i;

	i = 0;
	while (lst && i < buf->capacity)
	{
		run_one(lst, buf, i);
		i++;
		lst = lst->next;
	}
	buf->count = i;
}

static void	free_list(t_unit_test **lst)
{
	t_unit_test	*tmp;

	while (*lst)
	{
		tmp = (*lst)->next;
		free(*lst);
		*lst = tmp;
	}
}

int	launch_tests(t_unit_test **lst)
{
	t_result_buf	buf;
	t_bool			all_ok;
	int				total;

	total = count_tests(*lst);
	if (total == 0)
		return (0);
	if (buf_init(&buf, total) == FALSE)
		return (-1);
	run_all(*lst, &buf);
	all_ok = print_all(&buf);
	free(buf.data);
	free_list(lst);
	if (all_ok == TRUE)
		return (0);
	return (-1);
}
