/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_launcher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/15 15:10:00 by ybalkan           #+#    #+#             */
/*   Updated: 2026/08/17 20:57:51 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libunit.h"
#include <stdlib.h>

int			t01_basic_positive(void);
int			t02_basic_negative(void);
int			t03_zero(void);
int			t04_leading_spaces(void);
int			t05_all_whitespace_chars(void);
int			t06_plus_sign(void);
int			t07_negative_zero(void);
int			t08_int_max(void);
int			t09_int_min(void);
int			t10_number_then_alpha(void);
int			t11_alpha_then_number(void);
int			t12_only_whitespace(void);
int			t13_empty_string(void);
int			t14_only_plus_sign(void);
int			t15_only_minus_sign(void);
int			t16_ws_negative_ws(void);
int			t17_leading_zeros(void);

static void	ft_atoi_tests(t_unit_test **lst)
{
	ft_load_test(lst, "FT_ATOI", "Pozitif sayi [42]", &t01_basic_positive);
	ft_load_test(lst, "FT_ATOI", "Negatif sayi [-42]", &t02_basic_negative);
	ft_load_test(lst, "FT_ATOI", "Sifir [0]", &t03_zero);
	ft_load_test(lst, "FT_ATOI", "One bosluk [   42]", &t04_leading_spaces);
	ft_load_test(lst, "FT_ATOI", "Tum bosluk char", &t05_all_whitespace_chars);
	ft_load_test(lst, "FT_ATOI", "Arti isareti [+42]", &t06_plus_sign);
	ft_load_test(lst, "FT_ATOI", "Negatif sifir [-0]", &t07_negative_zero);
	ft_load_test(lst, "FT_ATOI", "INT_MAX [2147483647]", &t08_int_max);
	ft_load_test(lst, "FT_ATOI", "INT_MIN [-2147483648]", &t09_int_min);
	ft_load_test(lst, "FT_ATOI", "Sayi + harf [42abc]", &t10_number_then_alpha);
	ft_load_test(lst, "FT_ATOI", "Harf + sayi [abc42]", &t11_alpha_then_number);
	ft_load_test(lst, "FT_ATOI", "Sadece bosluk [   ]", &t12_only_whitespace);
	ft_load_test(lst, "FT_ATOI", "Bos string []", &t13_empty_string);
	ft_load_test(lst, "FT_ATOI", "Sadece arti [+]", &t14_only_plus_sign);
	ft_load_test(lst, "FT_ATOI", "Sadece eksi [-]", &t15_only_minus_sign);
	ft_load_test(lst, "FT_ATOI", "Neg-bosluk [-99]", &t16_ws_negative_ws);
	ft_load_test(lst, "FT_ATOI", "Once sifirler [00042]", &t17_leading_zeros);
}

int	ft_atoi_launcher(void)
{
	t_unit_test	*testlist;

	testlist = NULL;
	ft_atoi_tests(&testlist);
	return (ft_launch_tests(&testlist));
}
