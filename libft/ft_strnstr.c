/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouab <ytouab@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 13:59:27 by ytouab            #+#    #+#             */
/*   Updated: 2021/09/27 18:19:19 by ytouab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char	*haystack, const char *needle, size_t n)
{
	size_t	i;
	size_t	x;

	i = 0;
	x = 0;
	if (!needle[x])
		return ((char *)haystack);
	while (haystack[i] && i < n)
	{
		x = 0;
		while (needle[x] == haystack[i + x] && haystack[i + x] && (i + x) < n)
			if (!needle[++x])
				return ((char *)haystack + i);
		i++;
	}
	return (0);
}
