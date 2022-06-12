/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_clean.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouab <ytouab@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 08:39:00 by ytouab            #+#    #+#             */
/*   Updated: 2022/05/06 20:20:26 by ytouab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "yassir.h"

int	ft_quote_index(int i, char *s, int	*quote)
{
	while (s[i++])
	{
		if (s[i] == *quote)
		{
			*quote = 0;
			return (i);
		}
	}
	return (i);
}

int	ft_index_out_quote(int i, char *s)
{
	while (s[i] && s[i] != 39 && s[i] != 34)
		i++;
	return (i - 1);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*ret;
	int		i;
	int		x;

	i = -1;
	x = 0;
	if (!s1)
	{
		s1 = (char *)malloc(1);
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	ret = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	while (s1[++i])
		ret[i] = s1[i];
	while (s2[x])
		ret[i++] = s2[x++];
	ret[i] = '\0';
	free(s1);
	free(s2);
	return (ret);
}

static char	*ft_init_quote_vars(int *start, int *end, int *quote, char **ret)
{
	char	*trim;

	*start = 0;
	*end = 0;
	*quote = 0;
	*ret = NULL;
	trim = (char *)ft_calloc(2, 1);
	if (!trim)
		return (NULL);
	return (trim);
}

char	*ft_quote_clean(char *s)
{
	int		start;
	int		end;
	char	*ret;
	char	*trim;
	char	*tmp;

	trim = ft_init_quote_vars(&start, &end, &g_ms.quot, &ret);
	while (start < (int)ft_strlen(s) && s[start])
	{
		if ((s[start] == 39 || s[start] == 34))
		{
			trim[0] = s[start];
			g_ms.quot = (int)s[start];
			end = ft_quote_index(start, s, &g_ms.quot);
		}
		else
			end = ft_index_out_quote(start, s);
		tmp = ft_substr(s, start, end - start + 1);
		ret = ft_strjoin_free(ret, ft_strtrim(tmp, trim));
		free(tmp);
		trim[0] = '\0';
		start = end + 1;
	}
	free(trim);
	return (ret);
}
