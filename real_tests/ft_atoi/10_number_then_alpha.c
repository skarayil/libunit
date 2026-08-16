/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_number_then_alpha.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybalkan <ybalkan@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/15 15:10:00 by ybalkan           #+#    #+#             */
/*   Updated: 2026/08/16 18:44:04 by ybalkan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_atoi(const char *nptr);

int	t10_number_then_alpha(void)
{
	if (ft_atoi("42abc") == atoi("42abc"))
		return (0);
	return (-1);
}
