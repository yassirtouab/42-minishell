/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouab <ytouab@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 11:30:17 by ytouab            #+#    #+#             */
/*   Updated: 2021/10/07 01:23:25 by ytouab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ret;
	size_t	a[4];

	a[0] = 0;
	a[1] = 0;
	if (!s1 || !s2)
		return (0);
	a[2] = ft_strlen(s1);
	a[3] = ft_strlen(s2);
	ret = (char *)malloc((a[2] + a[3] + 1) * sizeof(char));
	if (!ret)
		return (0);
	while (a[0] < a[2])
	{
		ret[a[0]] = s1[a[0]];
		a[0]++;
	}
	while (a[1] < a[3])
		ret[a[0]++] = s2[a[1]++];
	ret[a[0]] = 0;
	return (ret);
}
