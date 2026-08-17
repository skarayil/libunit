/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_analyzer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/16 16:30:00 by ybalkan           #+#    #+#             */
/*   Updated: 2026/08/17 20:44:52 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libunit.h"
#include <stdlib.h>
#include <unistd.h>

static t_status	ft_get_signal(int sig)
{
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
	if (sig == SIGALRM)
		return (STATUS_TIMEOUT);
	return (STATUS_UNKNOWN);
}

t_status	ft_analyze(int status)
{
	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status) == 0)
			return (STATUS_OK);
		return (STATUS_KO);
	}
	if (WIFSIGNALED(status))
		return (ft_get_signal(WTERMSIG(status)));
	return (STATUS_UNKNOWN);
}

void	ft_run_one(t_unit_test *lst, t_result_buf *buf, int i)
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
		buf->data[i].status = ft_analyze(wstatus);
	}
	buf->data[i].func = lst->func;
	buf->data[i].test_name = lst->name;
}
