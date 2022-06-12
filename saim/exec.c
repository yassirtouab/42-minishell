/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sali <sali@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 12:08:02 by sali              #+#    #+#             */
/*   Updated: 2022/06/05 23:08:56 by Sali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_env_index(char *str)
{
	int		i;
	char	*temp;

	i = 0;
	while (g_ms.env[i] != NULL)
	{
		temp = ft_substr(g_ms.env[i], 0, ft_strlen(str));
		if (s_strncmp(temp, str, ft_strlen(str)) == 0)
		{
			free(temp);
			return (i);
		}
		free(temp);
		i++;
	}
	return (-1);
}

int	exec_cmd(char **arg_list, t_ms *ms)
{
	char	*path;

	path = NULL;
	if (arg_list != NULL)
	{
		if (access(arg_list[0], X_OK) == 0)
			execve(arg_list[0], arg_list, g_ms.env);
		else
		{
			path = file_path(arg_list[0], ms);
			execve(path, arg_list, g_ms.env);
		}
		if (errno == 2)
		{
			print_error(arg_list[0], arg_list[1], "command not found");
			g_ms.error = 127;
		}
		free (path);
	}
	return (0);
}

void	exec_lst(t_ms *ms, t_arg *exe, int *fd)
{
	int	i;

	i = 0;
	while (exe != NULL && i < ms->pipe + 1)
	{
		ms->pid = fork();
		if (ms->pid != 0)
			builtin(ms, exe, ms->pid);
		if (ms->pid != 0 && exe->exec != NULL
			&& s_strncmp(exe->exec[0], "./minishell", 12) == 0)
			set_shell_level(-1);
		if (ms->pid == 0)
		{
			set_pipe(i, ms->pipe, fd);
			if (redirect(exe->redir) == -1)
				break ;
			if (exe->exec != NULL && is_builtin(exe->exec[0]) == 1)
				builtin(ms, exe, ms->pid);
			else
				exec_cmd(exe->exec, ms);
			break ;
		}
		i++;
		exe = exe->next;
	}
}

void	set_shell_level(int input)
{
	int		index;
	int		lvl;
	int		i;
	char	*temp;

	i = 0;
	lvl = 0;
	temp = NULL;
	index = get_env_index("SHLVL");
	while (index > -1 && g_ms.env[index][i] != '\0')
	{
		if (g_ms.env[index][i] == '=')
		{
			lvl = ft_atoi(&g_ms.env[index][i + 1]);
			free (g_ms.env[index]);
			temp = ft_itoa(lvl + input);
			g_ms.env[index] = ft_strjoin("SHLVL=", temp);
			free (temp);
			break ;
		}
		i++;
	}
}

void	execute(t_ms *ms, t_arg *exe)
{
	t_arg	*head;
	int		*fd;

	head = exe;
	fd = init_pipe(ms);
	init_heredoc(exe);
	if (exe->exec != NULL && s_strncmp(exe->exec[0], "./minishell", 12) == 0)
		set_shell_level(1);
	exec_lst(ms, exe, fd);
	exe = head;
	close_wait(ms, fd, exe);
}
