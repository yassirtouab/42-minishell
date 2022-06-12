/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouab <ytouab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 14:06:08 by ytouab            #+#    #+#             */
/*   Updated: 2022/06/10 12:41:15 by ytouab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_run(t_arg **exe)
{
	if (!ft_all_delimiter(g_ms.line, " \t\v\r\f\n"))
	{
		add_history(g_ms.line);
		ft_check_perror();
		if (!g_ms.perror)
		{
			ft_parse();
			ft_lst_operators_check(g_ms.lst);
			if (!g_ms.perror)
			{
				*exe = arrange_parse(g_ms.lst);
				execute(&g_ms, *exe);
				free_arg(*exe);
			}
			ft_lstfree(&g_ms.lst);
		}
	}
}

int	main(int ac, char **av, char **env_vars)
{
	t_arg	*exe;

	g_ms.env = ft_ms_init(ac, av, env_vars);
	ft_signals();
	while (1)
	{
		g_ms.line = readline(PROMPT);
		rl_on_new_line();
		eof_check();
		if (g_ms.line && *(g_ms.line))
		{
			ft_run(&exe);
			ft_free_line();
		}
	}
	return (0);
}
