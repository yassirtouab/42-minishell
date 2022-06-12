/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouab <ytouab@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 21:01:27 by ytouab            #+#    #+#             */
/*   Updated: 2022/05/06 21:01:27 by ytouab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "yassir.h"

char	*ft_exit_value(char *var)
{
	char	*ret;

	ret = ft_itoa(g_ms.error);
	if (ft_strlen(var) > 1)
		ret = ft_strjoin_free(ret, ft_substr(var, 1, ft_strlen(var)));
	free(var);
	return (ret);
}

char	*ft_var_value(char *var)
{
	size_t	i;
	size_t	len;
	char	*env_var;

	i = 0;
	if (!ft_strncmp(var, "?", 1))
		return (ft_exit_value(var));
	len = ft_strlen(var) + 1;
	while (g_ms.env[i])
	{
		env_var = ft_take_var_name((g_ms.env[i]));
		if (!ft_strncmp(var, env_var, ft_strlen(var) + 1))
		{
			free(env_var);
			free(var);
			return (ft_substr(g_ms.env[i], len, ft_strlen(g_ms.env[i]) - len));
		}
		free(env_var);
		i++;
	}
	if (var)
		free(var);
	return (ft_strdup(""));
}

char	**ft_export_var(char *var)
{
	size_t	i;
	char	**ret;

	ret = NULL;
	i = 0;
	while (g_ms.env[i])
		i++;
	ret = (char **)malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (g_ms.env[i])
	{
		ret[i] = g_ms.env[i];
		i++;
	}
	ret[i] = ft_strdup(var);
	ret[++i] = NULL;
	free(g_ms.env);
	return (ret);
}

void	ft_replace_var(char *var)
{
	int	i;

	i = 0;
	i = ft_existing_var(var);
	if (i == -1)
		return ;
	if (g_ms.env[i])
		free(g_ms.env[i]);
	g_ms.env[i] = ft_strdup(var);
}

void	ft_export(char **arg)
{
	int	i;

	i = 1;
	if (!arg)
		return ;
	if (!ft_strncmp(arg[0], "export", ft_strlen(arg[0])) && arg[1])
	{
		while (arg[i])
		{
			if (ft_existing_var(arg[i]) == -1)
				g_ms.env = ft_export_var(arg[i]);
			else
				ft_replace_var(arg[i]);
			i++;
		}
	}
	else if (!ft_strncmp(arg[0], "export", ft_strlen(arg[0])))
		if (!(g_ms.pipe == 0 && g_ms.pid != 0))
			ft_arr_print(g_ms.env);
}
