/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/15 15:46:52 by ybalkan           #+#    #+#             */
/*   Updated: 2026/08/16 21:17:57 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libunit.h"

void	load_test(t_unit_test **lst, char *func_name,
			char *name, int (*test)(void))
{
	t_unit_test	*node;
	t_unit_test	*tail;

	node = (t_unit_test *)malloc(sizeof(t_unit_test));
	if (!node)
		return ;
	node->func_name = func_name;
	node->name = name;
	node->test = test;
	node->next = NULL;
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
