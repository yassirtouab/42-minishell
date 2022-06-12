/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouab <ytouab@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 20:06:20 by ytouab            #+#    #+#             */
/*   Updated: 2022/05/04 19:11:36 by ytouab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "yassir.h"

int	ft_inquote(char s, int *quote)
{
	if (s && s == '\"' && *quote != '\'')
	{
		if (!*quote)
			*quote = '\"';
		else if (*quote == '\"')
			*quote = 0;
	}
	else if (s && s == '\'' && *quote != '\"')
	{
		if (!*quote)
			*quote = '\'';
		else if (*quote == '\'')
			*quote = 0;
	}
	return (*quote);
}

int	ft_delimiter(char c, char *charset)
{
	int	i;

	i = -1;
	while (charset[++i])
		if (charset[i] == c)
			return (1);
	return (0);
}

int	ft_quote_count_words(char *str, char *charset)
{
	int	cw;
	int	i;

	cw = 0;
	i = 0;
	g_ms.quot = 0;
	while (str[i])
	{
		while (str[i] && ft_delimiter(str[i], charset)
			&& !ft_inquote(str[i], &g_ms.quot))
			i++;
		if (str[i] && (!ft_delimiter(str[i], charset)))
		{
			cw++;
			while (str[i] && (ft_inquote(str[i], &g_ms.quot)
					|| !ft_delimiter(str[i], charset)))
				i++;
		}
	}
	return (cw);
}

static void	ft_init_quote_split(char *str, char *charset, int *cw, int	*i)
{
	*cw = ft_quote_count_words(str, charset);
	*i = 0;
}

char	**ft_quote_split_charset(char *str, char *charset)
{
	char	**arr;
	int		a[3];

	ft_init_quote_split(str, charset, &a[0], &a[1]);
	arr = (char **)malloc((a[0] + 1) * sizeof(char *));
	while (a[1] < a[0])
	{
		while (*str && ft_delimiter(*str, charset)
			&& !ft_inquote(*str, &g_ms.quot))
			str++;
		a[2] = 0;
		while (str[a[2]] && (ft_inquote(str[a[2]], &g_ms.quot)
				|| !ft_delimiter(str[a[2]], charset)))
			a[2]++;
		arr[a[1]] = (char *)malloc(a[2] + 1);
		a[2] = 0;
		g_ms.quot = 0;
		while (*str && (ft_inquote(*str, &g_ms.quot)
				|| !ft_delimiter(*str, charset)))
			arr[a[1]][a[2]++] = *str++;
		arr[a[1]++][a[2]] = 0;
	}
	arr[a[1]] = 0;
	return (arr);
}
