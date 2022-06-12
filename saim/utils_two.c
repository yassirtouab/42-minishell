/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sali <sali@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 12:08:39 by sali              #+#    #+#             */
/*   Updated: 2022/05/25 12:08:40 by sali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_getenv(char *str, t_ms *ms, int i, int j)
{
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (ms->env != NULL && ms->env[i] != NULL)
	{
		j = 0;
		while (ms->env[i][j] != '\0')
		{
			if (ms->env[i][j] == '=')
			{
				tmp = ft_substr(ms->env[i], 0, j);
				if (s_strncmp(str, tmp, ft_strlen(str)) == 0)
				{
					free (tmp);
					return (ft_substr(ms->env[i], j + 1,
							ft_strlen(ms->env[i]) - j + 1));
				}
				free (tmp);
			}
			j++;
		}
		i++;
	}
	return (NULL);
}

char	*file_append(char *path, char *exec_name)
{
	char	*temp;
	char	*ret;

	temp = NULL;
	ret = NULL;
	ret = ft_strjoin(path, "/");
	temp = ret;
	ret = ft_strjoin(ret, exec_name);
	free (temp);
	free (path);
	return (ret);
}

void	file_path_helper(char *env_path, char *exec_name, char **search_path)
{
	char	*temp;
	int		i;
	int		start;

	temp = NULL;
	i = 0;
	start = 0;
	while (env_path != NULL && env_path[i] != '\0')
	{
		if (env_path[i] == ':')
		{
			free (*search_path);
			temp = ft_substr(env_path, start, i - start);
			*search_path = file_append(temp, exec_name);
			start = i + 1;
			if (access(*search_path, X_OK) == 0)
				break ;
		}
		i++;
	}
}

//find the executable if avaiable in the environment path //
char	*file_path(char *exec_name, t_ms *ms)
{
	char	*search_path;
	char	*env_path;

	search_path = NULL;
	env_path = ft_getenv("PATH", ms, 0, 0);
	file_path_helper(env_path, exec_name, &search_path);
	free (env_path);
	return (search_path);
}

t_arg	*new_arg(void)
{
	t_arg	*temp;

	temp = (t_arg *)malloc(sizeof(t_arg));
	temp->exec = NULL;
	temp->next = NULL;
	temp->redir = NULL;
	return (temp);
}
