/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libunit.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/15 09:30:00 by ybalkan           #+#    #+#             */
/*   Updated: 2026/08/16 21:17:15 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBUNIT_H
# define LIBUNIT_H

# include <sys/wait.h>
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>

# include "colors.h"

# define TIMEOUT_SECONDS	5

typedef enum e_bool
{
	FALSE = 0,
	TRUE = 1
}	t_bool;

typedef enum e_status
{
	STATUS_OK = 0,
	STATUS_KO = 1,
	STATUS_SEGV = 2,
	STATUS_BUS = 3,
	STATUS_ABRT = 4,
	STATUS_FPE = 5,
	STATUS_PIPE = 6,
	STATUS_ILL = 7,
	STATUS_UNKNOWN = 8,
	STATUS_TIMEOUT = 9
}	t_status;

typedef struct s_result
{
	char		*func_name;
	char		*test_name;
	t_status	status;
}	t_result;

typedef struct s_result_buf
{
	t_result	*data;
	int			count;
	int			capacity;
}	t_result_buf;

typedef struct s_unit_test
{
	char				*func_name;
	char				*name;
	int					(*test)(void);
	struct s_unit_test	*next;
}	t_unit_test;

void	load_test(t_unit_test **lst, char *func_name,
			char *name, int (*test)(void));
int		launch_tests(t_unit_test **lst);

t_bool	print_all(t_result_buf *buf);
t_bool	print_all_bonus(t_result_buf *buf);

#endif
