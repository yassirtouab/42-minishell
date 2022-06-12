/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sali <sali@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 12:07:47 by sali              #+#    #+#             */
/*   Updated: 2022/06/05 21:20:36 by Sali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isspace(const char str)
{
	if (str == '\t' || str == '\n' || str == '\v' || str == '\r' || str == '\f'
		|| str == ' ')
		return (1);
	return (0);
}

int	arry_size(char **arry)
{
	int	i;

	i = 0;
	while (arry[i] != NULL)
		i++;
	return (i);
}

void	print_error(char *cmd, char *arg, char *error)
{
	write(2, "minishell: ", 12);
	ft_putstr_fd(cmd, 2);
	write (2, ": ", 3);
	if (arg != NULL)
	{
		ft_putstr_fd(arg, 2);
		write (2, ": ", 3);
	}
	ft_putstr_fd(error, 2);
	write(2, "\n", 1);
}

void	ft_clear(void)
{
	write(1, "\033[H\033[2J", 8);
	g_ms.error = 0;
}

void	ft_env(t_ms *ms)
{
	int	i;

	i = 0;
	while (ms->env != NULL && ms->env[i] != NULL)
	{
		printf("%s\n", ms->env[i]);
		i++;
	}
	g_ms.error = 0;
}
