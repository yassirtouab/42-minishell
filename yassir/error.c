/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouab <ytouab@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 04:00:13 by ytouab            #+#    #+#             */
/*   Updated: 2022/05/02 04:00:13 by ytouab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "yassir.h"

int	ft_unclosed_quote(char *s)
{
	size_t	i;
	int		quote;

	i = 0;
	quote = 0;
	while (i < ft_strlen(s) && s[i])
	{
		ft_inquote(s[i], &quote);
		i++;
	}
	if (!g_ms.perror && quote)
		g_ms.perror = 1;
	return (quote);
}

void	ft_invalid_ops(char *s, size_t i, int quote, char *op)
{
	while (i < ft_strlen(s) && s[i] && !g_ms.perror)
	{
		ft_inquote(s[i], &quote);
		if (!quote && ft_delimiter(s[i], "<|>"))
		{
			op = ft_take_operator(s, &i);
			while (s[++i] && ft_delimiter(s[i], " \t\v\r\f\n"))
				;
			if (s[i] && ft_delimiter(s[i], "<|>"))
			{
				if (op[0] == '|' && s[i] != '|')
					ft_invalid_ops(s, i, quote, NULL);
				else
				{
					free(op);
					g_ms.perror = 2;
					break ;
				}
			}
			free(op);
		}
		i++;
	}
}

void	ft_lst_operators_check(t_cmd *lst)
{
	if (!lst)
		return ;
	while (lst->prev)
		lst = lst->prev;
	while (lst)
	{
		if (lst->next && lst->n_op[0] == '|')
		{
			if (!lst->arg || !lst->arg[0])
			{
				g_ms.perror = 2;
				break ;
			}
		}
		if (lst->next)
		{
			if (!lst->next->arg || !lst->next->arg[0])
			{
				g_ms.perror = 2;
				break ;
			}
		}
		lst = lst->next;
	}
	ft_perror(g_ms.perror);
}

void	ft_check_perror(void)
{
	if (!ft_unclosed_quote(g_ms.line))
		ft_invalid_ops(g_ms.line, 0, 0, NULL);
	ft_perror(g_ms.perror);
}

void	ft_perror(int perror)
{
	if (perror == 1)
		ft_putstr_fd("Minishell: unclosed quotes\n", 2);
	else if (perror == 2)
		ft_putstr_fd("Minishell: syntax error\n", 2);
}
