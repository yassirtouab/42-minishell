/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit-status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sali <sali@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 12:07:12 by sali              #+#    #+#             */
/*   Updated: 2022/06/05 23:35:47 by Sali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_exit_status(pid_t *pid, pid_t *current_pid, int *wstatus)
{
	int	i;

	i = 0;
	if (g_ms.pid != 0)
	{
		while (i < g_ms.pipe + 1)
		{
			*pid = wait(wstatus);
			if (WIFEXITED(*wstatus) && (*pid > *current_pid))
			{
				*current_pid = *pid;
				g_ms.error = WEXITSTATUS(*wstatus);
			}
			else if (WIFSIGNALED(*wstatus) == 1 && (*pid > *current_pid))
			{
				*current_pid = *pid;
				if (WTERMSIG(*wstatus) != 13)
					g_ms.error = WTERMSIG(*wstatus) + 128;
				if (g_ms.error == 130)
					printf("\n");
			}
			i++;
		}
	}
}

void	close_wait(t_ms *ms, int *fd, t_arg *exe)
{
	int			i;
	pid_t		pid;
	pid_t		current_pid;
	int			wstatus;

	i = 0;
	current_pid = -1;
	while (i < 2 * ms->pipe)
	{
		close (fd[i]);
		i++;
	}
	close_heredoc(exe);
	set_exit_status(&pid, &current_pid, &wstatus);
	if (fd != NULL)
		free (fd);
	if (ms->pid == 0)
	{
		close (0);
		close (1);
		free_exit(ms, exe, g_ms.error);
	}
}
