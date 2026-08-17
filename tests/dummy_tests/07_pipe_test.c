/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07_pipe_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/16 16:42:00 by ybalkan           #+#    #+#             */
/*   Updated: 2026/08/17 20:46:33 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

int	ft_pipe_test(void)
{
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		exit(0);
	}
	else
	{
		close(pipefd[0]);
		wait(NULL);
		write(pipefd[1], "X", 1);
		close(pipefd[1]);
	}
	return (0);
}
