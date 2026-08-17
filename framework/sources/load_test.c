/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/15 15:46:52 by ybalkan           #+#    #+#             */
/*   Updated: 2026/08/17 20:38:30 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libunit.h"
#include <stdlib.h>

static void	ft_append_node(t_unit_test **lst, t_unit_test *node)
{
	t_unit_test	*tail;

	if (!*lst)
	{
		*lst = node;
		return ;
	}
	tail = *lst;
	while (tail->next)
		tail = tail->next;
	tail->next = node;
}

void	ft_load_test(t_unit_test **lst, char *func, char *name,
		int (*test)(void))
{
	t_unit_test	*node;

	node = (t_unit_test *)malloc(sizeof(t_unit_test));
	if (!node)
		return ;
	node->func = func;
	node->name = name;
	node->test = test;
	node->next = NULL;
	ft_append_node(lst, node);
}
