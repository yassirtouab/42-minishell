/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouab <ytouab@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 19:52:04 by ytouab            #+#    #+#             */
/*   Updated: 2021/10/01 16:16:15 by ytouab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t items, size_t size)
{
	size_t	fsize;
	char	*ret;

	fsize = items * size;
	ret = (void *)malloc(fsize);
	if (!ret)
		return (0);
	ft_bzero(ret, fsize);
	return (ret);
}
