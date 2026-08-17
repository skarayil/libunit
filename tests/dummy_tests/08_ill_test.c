/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08_ill_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/16 16:42:00 by ybalkan           #+#    #+#             */
/*   Updated: 2026/08/17 20:46:36 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>

int	ft_ill_test(void)
{
	void	(*invalid_func)(void);

	(invalid_func) = (void (*)(void))0x12345678;
	invalid_func();
	return (0);
}
