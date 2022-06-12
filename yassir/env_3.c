/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouab <ytouab@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 05:09:48 by ytouab            #+#    #+#             */
/*   Updated: 2022/05/09 05:09:48 by ytouab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "yassir.h"

void	ft_unset(char **arg)
{
	int	i;
	int	x;

	i = 0;
	x = 1;
	if (!arg)
		return ;
	if (!ft_strncmp(arg[0], "unset", 6) && arg[1])
	{
		while (arg[x])
		{
			i = ft_existing_var(arg[x]);
			if (i != -1)
				g_ms.env = ft_unset_index_arr(g_ms.env, i);
			x++;
		}
	}
}

char	**ft_unset_index_arr(char **arr, int i)
{
	int		j;
	int		x;
	char	**ret;

	j = 0;
	x = 0;
	ret = NULL;
	while (arr[j])
		j++;
	ret = (char **)malloc(sizeof(char *) * j);
	j = 0;
	while (arr[j])
	{
		if (j == i)
			j++;
		if (arr[j])
			ret[x++] = ft_strdup(arr[j++]);
	}
	ret[x] = NULL;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
	return (ret);
}

int	ft_existing_var(char *var)
{
	int		i;
	char	*var_name;
	char	*env_vars_names;

	i = 0;
	if (!var)
		return (-1);
	var_name = ft_take_var_name(var);
	while (g_ms.env[i])
	{
		env_vars_names = ft_take_var_name(g_ms.env[i]);
		if (!ft_strncmp(var_name, env_vars_names, ft_strlen(var_name) + 1))
		{
			free(env_vars_names);
			free(var_name);
			return (i);
		}
		free(env_vars_names);
		i++;
	}
	free(var_name);
	return (-1);
}
