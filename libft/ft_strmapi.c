/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouab <ytouab@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 11:36:24 by ytouab            #+#    #+#             */
/*   Updated: 2021/10/07 12:30:55 by ytouab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*str;
	size_t			l;

	i = 0;
	if (!s)
		return (0);
	str = ft_strdup(s);
	if (!str || !s || !f)
		return (0);
	l = ft_strlen(str);
	while (i < l)
	{
		str[i] = f(i, str[i]);
		i++;
	}
	return (str);
}
