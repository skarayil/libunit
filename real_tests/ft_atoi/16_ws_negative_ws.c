/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   16_ws_negative_ws.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybalkan <ybalkan@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/15 15:10:00 by ybalkan           #+#    #+#             */
/*   Updated: 2026/08/16 18:44:17 by ybalkan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_atoi(const char *nptr);

int	t16_ws_negative_ws(void)
{
	if (ft_atoi("  -99  ") == atoi("  -99  "))
		return (0);
	return (-1);
}
