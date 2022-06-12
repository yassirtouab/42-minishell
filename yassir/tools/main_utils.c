/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouab <ytouab@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 05:18:30 by ytouab            #+#    #+#             */
/*   Updated: 2022/05/21 17:35:50 by ytouab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../yassir.h"

char	**ft_ms_init(int ac, char **av, char **env_vars)
{
	(void)ac;
	(void)av;
	g_ms.env = NULL;
	g_ms.line = NULL;
	g_ms.env = NULL;
	g_ms.lst = NULL;
	g_ms.perror = 0;
	g_ms.error = 0;
	g_ms.quot = 0;
	g_ms.pipe = 0;
	return (ft_double_arr_dup(env_vars));
}

void	ft_free_line(void)
{
	if (g_ms.line)
		free(g_ms.line);
	g_ms.line = NULL;
	g_ms.perror = 0;
}

void	ft_freedom(void)
{
	size_t	i;

	i = 0;
	if (g_ms.env)
	{
		while (g_ms.env[i])
			free(g_ms.env[i++]);
		free(g_ms.env[i]);
		free(g_ms.env);
	}
	ft_lstfree(&g_ms.lst);
	ft_free_line();
	exit(0);
}
