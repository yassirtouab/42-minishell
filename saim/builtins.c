/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sali <sali@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 12:07:58 by sali              #+#    #+#             */
/*   Updated: 2022/05/25 12:07:59 by sali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_oldpwd(char *working_dir)
{
	int	index;

	index = get_env_index("OLDPWD=");
	if (index != -1)
	{
		free(g_ms.env[index]);
		g_ms.env[index] = ft_strjoin("OLDPWD=", working_dir);
	}
}

void	set_curpwd(void)
{
	char	*size;
	char	*wd;
	int		index;

	index = -1;
	size = (char *) malloc(sizeof(char) * 10000);
	wd = getcwd(size, 10000);
	index = get_env_index("PWD=");
	if (index != -1)
	{
		free(g_ms.env[index]);
		g_ms.env[index] = ft_strjoin("PWD=", wd);
	}
	free (size);
}

int	cd_arg(char **arg, char *size)
{
	if (chdir(arg[1]) != 0)
	{
		free (size);
		if (g_ms.pid != 0)
			print_error(arg[0], arg[1], "No such file or directory");
		g_ms.error = 1;
		return (-1);
	}
	return (0);
}

void	ft_cd(char **arg)
{
	char	*wd;
	char	*size;

	size = (char *) malloc(sizeof(char) * 10000);
	wd = getcwd(size, 10000);
	if (arry_size(arg) > 2)
	{
		if (g_ms.pid != 0)
			print_error(arg[0], NULL, "too many arguments");
		g_ms.error = 1;
		free (size);
		return ;
	}
	if (arg[1] == NULL)
		chdir("..");
	else
		if (cd_arg(arg, size) == -1)
			return ;
	set_oldpwd(wd);
	set_curpwd();
	g_ms.error = 0;
	free (size);
}

void	ft_pwd(void)
{
	char	*size;

	size = (char *) malloc(sizeof(char) * 10000);
	if (size == NULL)
		return ;
	printf("%s\n", getcwd(size, 10000));
	free (size);
	g_ms.error = 0;
}
