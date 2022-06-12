/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sali <sali@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 12:07:04 by sali              #+#    #+#             */
/*   Updated: 2022/06/05 21:22:07 by Sali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	new_line_check(int *newline, char **arry, int *i, int *j)
{
	*newline = 0;
	*j = 1;
	while (arry[*i][*j] != '\0')
	{
		if (arry[*i][*j] != 'n')
		{
			*newline = 1;
			break ;
		}
		*j = *j + 1;
	}
	if (*newline != 1)
		*i = *i + 1;
}

void	echo_n_skip(char **arry, int *i, int *j, int *newline)
{
	int	brk;

	brk = 0;
	while (arry[*i] != NULL && *newline != 1)
	{
		*j = 1;
		if (arry[*i][0] == '-' && arry[*i][1] == 'n')
		{
			while (arry[*i][*j] != '\0')
			{
				if (arry[*i][*j] != 'n')
				{
					brk = 1;
					break ;
				}
				*j = *j + 1;
			}
			if (brk == 1)
				break ;
		}
		else
			break ;
		*i = *i + 1;
	}
}

void	ft_echo(char **arry)
{
	int	i;
	int	j;
	int	newline;

	i = 1;
	newline = 1;
	if (arry[i] != NULL && arry[i][0] == '-' && arry[i][1] == 'n')
	{
		new_line_check(&newline, arry, &i, &j);
		echo_n_skip(arry, &i, &j, &newline);
	}
	while (arry[i] != NULL)
	{
		write(1, arry[i], ft_strlen(arry[i]));
		if (arry[i + 1] != NULL)
			write(1, " ", 1);
		i++;
	}
	if (newline == 1)
		write(1, "\n", 1);
	g_ms.error = 0;
}
