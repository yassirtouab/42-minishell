/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouab <ytouab@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 12:08:19 by sali              #+#    #+#             */
/*   Updated: 2022/05/30 22:53:10 by ytouab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	heredoc_if(char **str, char **tmp)
{
	if (*str == NULL)
	{
		write(1, "\n", 1);
		print_error("warning", NULL,
			"here-document delimited by end-of-file");
		return (-1);
	}
	if (*str && ft_strchr(*str, '$'))
	{
		*tmp = ft_strdup(*str);
		if (*str)
			free(*str);
		*str = ft_replace_env_var(*tmp, 0, 0, NULL);
	}
	return (0);
}

void	heredoc(int *fd, char *end)
{
	char	*str;
	char	*tmp;

	end = ft_strjoin(end, "\n");
	str = NULL;
	tmp = NULL;
	while (1)
	{
		str = readline("Prompt: ");
		if (heredoc_if(&str, &tmp) == -1)
			break ;
		str = ft_strjoin_free(str, ft_strdup("\n"));
		if (s_strncmp(str, end, ft_strlen(end)) == 0)
			break ;
		write(fd[1], str, ft_strlen(str));
		free (str);
	}
	free (end);
	if (str != NULL)
		free (str);
	close(fd[1]);
}

void	close_heredoc(t_arg *exe)
{
	t_arg	*temp_arg;
	t_redir	*temp_redir;

	temp_arg = exe;
	while (temp_arg != NULL)
	{
		temp_redir = temp_arg->redir;
		while (temp_redir != NULL)
		{
			if (temp_redir->fd != -1)
				close(temp_redir->fd);
			temp_redir = temp_redir->next;
		}
		temp_arg = temp_arg->next;
	}
}

void	set_heredoc(t_arg *temp, int *fd)
{
	t_redir	*redir_head;

	while (temp != NULL)
	{
		fd[0] = -1;
		redir_head = temp->redir;
		while (temp->redir != NULL)
		{
			if (ft_strncmp(temp->redir->type, "<<", 3) == 0)
			{
				if (fd[0] != -1)
					close(fd[0]);
				pipe(fd);
				heredoc(fd, temp->redir->name);
			}
			if (temp->redir != NULL)
				temp->redir->fd = fd[0];
			temp->redir = temp->redir->next;
		}
		temp->redir = redir_head;
		temp = temp->next;
	}
}

void	init_heredoc(t_arg *exe)
{
	t_arg	*temp;
	int		*fd;

	temp = exe;
	fd = malloc(sizeof(int) * 2);
	set_heredoc(temp, fd);
	free (fd);
}
