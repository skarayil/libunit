/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   17_leading_zeros.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybalkan <ybalkan@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/15 15:10:00 by ybalkan           #+#    #+#             */
/*   Updated: 2026/08/16 18:44:19 by ybalkan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_atoi(const char *nptr);

int	t17_leading_zeros(void)
{
	if (ft_atoi("00042") == atoi("00042"))
		return (0);
	return (-1);
}
