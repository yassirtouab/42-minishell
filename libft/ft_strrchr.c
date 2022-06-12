/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouab <ytouab@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 11:19:31 by ytouab            #+#    #+#             */
/*   Updated: 2022/05/06 20:32:08 by ytouab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int		i;
	char	*ret;

	if (!str)
		return (NULL);
	ret = (char *)str;
	i = 0;
	while (*ret)
	{
		ret++;
		i++;
	}
	if (!c)
		return (ret);
	while (i >= 0)
	{
		if (*ret == (char)c)
			return (ret);
		ret--;
		i--;
	}
	return (NULL);
}
