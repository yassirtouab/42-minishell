/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouab <ytouab@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 11:17:58 by ytouab            #+#    #+#             */
/*   Updated: 2021/10/01 18:33:57 by ytouab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	ret;
	size_t	sl;
	size_t	dl;

	i = 0;
	sl = ft_strlen(src);
	dl = ft_strlen(dst);
	if (size == 0)
		return (sl);
	if (size < dl)
		ret = sl + size;
	else
		ret = sl + dl;
	while (src[i++] && ((i + dl) < (size)))
		dst[i + dl - 1] = src[i - 1];
	dst[i + dl - 1] = 0;
	return (ret);
}
