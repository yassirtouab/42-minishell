/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouab <ytouab@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 12:31:12 by ytouab            #+#    #+#             */
/*   Updated: 2022/04/03 06:36:50 by ytouab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

// size_t	ft_strlen(const char *str)
// {
// 	size_t	l;

// 	l = 0;
// 	if (!str)
// 		return (0);
// 	while (str[l])
// 		l++;
// 	return (l);
// }

size_t	ft_nl_index(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strjoingnl(char *s1, char *s2)
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
	return (ret);
}
