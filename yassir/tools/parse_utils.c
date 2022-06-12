/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sali <sali@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 02:20:22 by ytouab            #+#    #+#             */
/*   Updated: 2022/06/06 09:30:56 by Sali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../yassir.h"

int	ft_all_delimiter(char *s, char *charset)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (!ft_delimiter(s[i], charset))
			return (0);
		i++;
	}
	return (1);
}

char	**ft_double_arr_dup(char **arr)
{
	char	**ret;
	size_t	i;

	i = 0;
	if (!arr)
		return (NULL);
	while (arr[i])
		i++;
	ret = (char **)malloc((i + 2) * sizeof(char *));
	i = 0;
	while (arr[i])
	{
		ret[i] = ft_strdup(arr[i]);
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

void	ft_arr_print(char **arr)
{
	size_t	i;
	size_t	x;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		x = 0;
		ft_putstr_fd("declare -x ", 1);
		while (arr[i][x] && arr[i][x] != '=')
			ft_putchar_fd(arr[i][x++], 1);
		if (arr[i][x] == '=')
			x++;
		ft_putstr_fd("=\"", 1);
		if (arr[i][x])
			while (arr[i][x])
				ft_putchar_fd(arr[i][x++], 1);
		ft_putstr_fd("\"\n", 1);
		i++;
	}
}
