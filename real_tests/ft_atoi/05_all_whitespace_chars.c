/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_all_whitespace_chars.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybalkan <ybalkan@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/15 15:10:00 by ybalkan           #+#    #+#             */
/*   Updated: 2026/08/16 18:43:49 by ybalkan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_atoi(const char *nptr);

int	t05_all_whitespace_chars(void)
{
	char	*s;

	s = "\t\n\v\f\r 99";
	if (ft_atoi(s) == atoi(s))
		return (0);
	return (-1);
}
