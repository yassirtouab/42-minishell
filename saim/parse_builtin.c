/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouab <ytouab@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 12:07:22 by sali              #+#    #+#             */
/*   Updated: 2022/06/12 17:49:45 by ytouab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	s_strncmp(char *s1, char *s2, int size)
{
	int	size_one;
	int	size_two;

	size_one = 0;
	size_two = 0;
	if (s1 != NULL)
		size_one = ft_strlen(s1);
	if (s2 != NULL)
		size_two = ft_strlen(s2);
	if (size_one == size_two)
		return (ft_strncmp(s1, s2, size));
	return (-1);
}

int	is_builtin(char *str)
{
	if (!s_strncmp(str, "echo", 4) || !s_strncmp(str, "cd", 3)
		|| !s_strncmp(str, "pwd", 3) || !s_strncmp(str, "export", 7)
		|| !s_strncmp(str, "unset", 6) || !s_strncmp(str, "env", 4)
		|| !s_strncmp(str, "exit", 5) || !s_strncmp(str, "clear", 6))
		return (1);
	return (0);
}

void	builtin_parent_child(t_arg *exe, t_ms *ms)
{
	if (g_ms.pipe == 0 && exe->exec != NULL)
	{
		if (s_strncmp(exe->exec[0], "cd", 3) == 0)
			ft_cd(exe->exec);
		if (s_strncmp(exe->exec[0], "export", 7) == 0)
			ft_export(ms->lst->arg);
		if (s_strncmp(exe->exec[0], "unset", 6) == 0)
			ft_unset(ms->lst->arg);
		if (s_strncmp(exe->exec[0], "exit", 5) == 0)
			exit_mh(ms, exe, exe->exec, 0);
	}
	else if (g_ms.pipe > 0 && exe->exec != NULL)
	{
		if (g_ms.pid == 0)
		{
			if (s_strncmp(exe->exec[0], "cd", 3) == 0)
				ft_cd(exe->exec);
			if (s_strncmp(exe->exec[0], "export", 7) == 0)
				ft_export(exe->exec);
			if (s_strncmp(exe->exec[0], "unset", 6) == 0)
				ft_unset(exe->exec);
		}
	}
}

int	builtin(t_ms *ms, t_arg *exe, pid_t pid)
{
	builtin_parent_child(exe, ms);
	if (pid == 0 && exe->exec != NULL)
	{
		if (s_strncmp(exe->exec[0], "echo", 5) == 0)
			ft_echo(exe->exec);
		else if (s_strncmp(exe->exec[0], "pwd", 4) == 0)
			ft_pwd();
		else if (s_strncmp(exe->exec[0], "env", 4) == 0)
			ft_env(ms);
		else if (s_strncmp(exe->exec[0], "clear", 6) == 0)
			ft_clear();
	}
	return (0);
}
