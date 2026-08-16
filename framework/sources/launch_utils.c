/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/16 16:30:00 by ybalkan           #+#    #+#             */
/*   Updated: 2026/08/16 21:17:57 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libunit.h"

t_status	analyze(int status)
{
	int	sig;

	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status) == 0)
			return (STATUS_OK);
		return (STATUS_KO);
	}
	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGSEGV)
			return (STATUS_SEGV);
		if (sig == SIGBUS)
			return (STATUS_BUS);
		if (sig == SIGABRT)
			return (STATUS_ABRT);
		if (sig == SIGFPE)
			return (STATUS_FPE);
		if (sig == SIGPIPE)
			return (STATUS_PIPE);
		if (sig == SIGILL)
			return (STATUS_ILL);
	}
	return (STATUS_UNKNOWN);
}

void	run_one(t_unit_test *lst, t_result_buf *buf, int i)
{
	pid_t	pid;
	int		wstatus;
	int		result;

	pid = fork();
	if (pid == 0)
	{
		result = lst->test();
		exit(result);
	}
	if (pid < 0)
		buf->data[i].status = STATUS_UNKNOWN;
	else
	{
		waitpid(pid, &wstatus, 0);
		buf->data[i].status = analyze(wstatus);
	}
	buf->data[i].func_name = lst->func_name;
	buf->data[i].test_name = lst->name;
}
