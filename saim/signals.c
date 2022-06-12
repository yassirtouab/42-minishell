/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sali <sali@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 17:32:03 by sali              #+#    #+#             */
/*   Updated: 2022/06/05 23:15:47 by Sali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sig_handler(int sig)
{
	if (sig == SIGQUIT)
		return ;
	if (sig == SIGINT)
	{
		if (g_ms.line != NULL && get_env_index("SHLVL=") > -1
			&& s_strncmp(g_ms.env[get_env_index("SHLVL=")], "SHLVL=1", 8) == 0)
		{
			write(1, "\n", 1);
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
			g_ms.error = 130;
		}
		else if (get_env_index("SHLVL=") > -1
			&& s_strncmp(g_ms.env[get_env_index("SHLVL=")], "SHLVL=1", 8) == 0)
		{
			write(1, "\n", 1);
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
			g_ms.error = 1;
		}
	}
}

void	ft_signals(void)
{
	signal(SIGQUIT, sig_handler);
	signal(SIGINT, sig_handler);
}

void	eof_check(void)
{
	if (g_ms.line == NULL)
	{
		free_exit(&g_ms, NULL, 0);
	}
}
