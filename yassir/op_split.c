/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouab <ytouab@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 23:43:14 by ytouab            #+#    #+#             */
/*   Updated: 2022/05/04 10:06:58 by ytouab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "yassir.h"

char	*ft_take_operator(char *s, size_t *i)
{
	char	*ret;

	ret = NULL;
	if (s[*i] == '<')
	{
		if (s[*i] == '<' && s[*i + 1] == '<')
			ret = ft_strdup("<<");
		else
			ret = ft_strdup("<");
	}
	else if (s[*i] == '>')
	{
		if (s[*i] == '>' && s[*i + 1] == '>')
			ret = ft_strdup(">>");
		else
			ret = ft_strdup(">");
	}
	else if (s[*i] == '|')
		ret = ft_strdup("|");
	*i = *i + ft_strlen(ret) - 1;
	return (ret);
}

void	ft_op_split(char *s, char *charset)
{
	size_t	start;
	size_t	i;

	start = 0;
	i = 0;
	g_ms.quot = 0;
	ft_cmdadd_back(&g_ms.lst, ft_cmdnew());
	while (i < ft_strlen(s) && s[i])
	{
		start = i;
		while (s[i] && (ft_inquote(s[i], &g_ms.quot)
				|| !ft_delimiter(s[i], charset)))
			i++;
		if (i > start)
			g_ms.lst->cmdl = ft_substr(s, start, i - start);
		if (s[i] && ft_delimiter(s[i], charset))
		{
			g_ms.lst->n_op = ft_take_operator(s, &i);
			ft_cmdadd_back(&g_ms.lst, ft_cmdnew());
			if (ft_lstlen(g_ms.lst) > 1)
				g_ms.lst = g_ms.lst->next;
		}
		i++;
	}
}

int	ft_count_words(char *str, char *charset)
{
	int	nb;
	int	i;

	nb = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && ft_delimiter(str[i], charset))
			i++;
		if (str[i] && !ft_delimiter(str[i], charset))
			nb++;
		while (str[i] && !ft_delimiter(str[i], charset))
			i++;
	}
	return (nb);
}

char	**ft_split_charset(char *str, char *charset)
{
	char	**arr;
	int		nb;
	int		i;
	int		x;

	nb = ft_count_words(str, charset);
	arr = (char **)malloc((nb + 1) * sizeof(char *));
	if (!arr)
		return (0);
	i = 0;
	while (i < nb)
	{
		while (*str && ft_delimiter(*str, charset))
			str++;
		x = 0;
		while (str[x] && !ft_delimiter(str[x], charset))
			x++;
		arr[i] = (char *)malloc(x + 1);
		x = 0;
		while (*str && !ft_delimiter(*str, charset))
			arr[i][x++] = *str++;
		arr[i++][x] = 0;
	}
	arr[i] = 0;
	return (arr);
}
