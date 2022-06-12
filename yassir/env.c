/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouab <ytouab@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 07:02:27 by ytouab            #+#    #+#             */
/*   Updated: 2022/05/03 07:02:27 by ytouab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "yassir.h"

char	*ft_take_var_name(char	*env_var)
{
	size_t	i;

	i = 0;
	if (!env_var)
		return (NULL);
	while (env_var[i] && env_var[i] != '=')
		i++;
	return (ft_substr(env_var, 0, i));
}

char	*ft_var_from_str(size_t *start, char *str)
{
	size_t	i;

	if (!str)
		return (NULL);
	if (str[*start] == '$')
		*start = *start + 1;
	i = *start;
	while (i < ft_strlen(str) && str[i]
		&& !ft_delimiter(str[i], " \t\v\r\f\n$\"\'<|>"))
		i++;
	return (ft_substr(str, *start, i - *start));
}

int	ft_valid_env_replace(char *s)
{
	size_t	i;
	int		quote;

	i = 0;
	quote = 0;
	while (s[i])
	{
		ft_inquote(s[i], &quote);
		if (s[i] == '$')
			break ;
		i++;
	}
	if (quote == '\'')
		return (0);
	return (1);
}

static char	*ft_replace_env_var_norm(char *s, char *ret, size_t i, int quote)
{
	char	*tmp;

	i = 0;
	tmp = ft_strdup(ret);
	while (s[i])
	{
		if (ft_inquote(s[i], &quote) != '\'' && s[i] == '$')
			break ;
		i++;
	}
	tmp = ft_strjoin_free(ft_substr(s, 0, i), ft_replace_env_var(ft_substr(s,
					i, ft_strlen(s) - i), quote, 0, NULL));
	free(ret);
	return (tmp);
}

char	*ft_replace_env_var(char *s, int quote, size_t i, char *ret)
{
	if (ft_strchr(s, '$') && ft_valid_env_replace(s))
	{
		while (s[i] && s[i] != '$')
			i++;
		ret = ft_substr(s, 0, i);
		if (!ft_isdigit(s[i + 1]))
		{
			ret = ft_strjoin_free(ret, ft_var_value(ft_var_from_str(&i, s)));
			while (s[i] && !ft_delimiter(s[i], " \t\v\r\f\n$\"\'<|>"))
				i++;
		}
		else
			i = i + 2;
		ret = ft_strjoin_free(ret, ft_substr(s, i, ft_strlen(s) - i));
		if (ft_strchr(ret, '$'))
			ret = ft_replace_env_var(ret, quote, 0, NULL);
	}
	else if (ft_strchr(s, '$') && !ft_valid_env_replace(s))
		ret = ft_replace_env_var_norm(s, ret, i, quote);
	else
		ret = ft_strdup(s);
	if (s)
		free(s);
	return (ret);
}
