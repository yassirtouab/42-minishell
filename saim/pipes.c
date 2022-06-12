/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sali <sali@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 12:08:23 by sali              #+#    #+#             */
/*   Updated: 2022/05/25 12:08:24 by sali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	*init_pipe(t_ms *ms)
{
	int	*fd;
	int	i;

	i = 0;
	fd = malloc(sizeof(int) * (ms->pipe * 2));
	while (i < ms->pipe)
	{
		pipe(&fd[i * 2]);
		i++;
	}
	return (fd);
}

void	close_fds(int pipes, int *fd)
{
	int	i;

	i = 0;
	while (i < (pipes * 2))
	{
		close(fd[i]);
		i++;
	}
}

void	set_pipe(int i, int pipes, int *fd)
{
	if (pipes > 0)
	{
		if (i == 0 && pipes > 0)
		{
			dup2(fd[(i * 2) + 1], 1);
			close_fds(pipes, fd);
		}
		else if (i != pipes && i != 0)
		{
			dup2(fd[(i - 1) * 2], 0);
			dup2(fd[(i * 2) + 1], 1);
			close_fds(pipes, fd);
		}
		if (i == pipes && pipes > 0)
		{
			dup2(fd[(i - 1) * 2], 0);
			close_fds(pipes, fd);
		}
	}
}
