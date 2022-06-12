/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouab <ytouab@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 12:08:14 by sali              #+#    #+#             */
/*   Updated: 2022/06/12 17:49:55 by ytouab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

long long	ft_atol(const char *str)
{
	size_t					i;
	unsigned long long		nb;
	int						sign;

	i = 0;
	nb = 0;
	sign = 1;
	while (ft_isspace(str[i]) == 1)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = sign * -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	if (nb > 9223372036854775808LLU && sign == -1)
		return (0);
	else if (nb > 9223372036854775807LLU && sign == 1)
		return (-1);
	return (nb * sign);
}

int	size_check(char **arry)
{
	int	len;

	if (arry[1] != NULL)
	{
			len = ft_strlen(arry[1]);
		if (len > 20)
			return (1);
		if ((ft_atol(arry[1]) == 0 && len >= 18)
			|| (ft_atol(arry[1]) == -1 && len >= 18))
			return (1);
	}
	return (0);
}

int	is_digit_string(char *str)
{
	int	i;

	i = 0;
	if (str != NULL)
	{
		if (str[0] == '+' || str[0] == '-')
			i++;
		while (str[i] != '\0')
		{
			if (!ft_isdigit(str[i]))
				return (-1);
			i++;
		}
	}
	return (0);
}

void	exit_mh(t_ms *ms, t_arg *exe, char **arg, int code)
{
	if (is_digit_string(arg[1]) == -1)
	{
		if (g_ms.pid != 0)
			print_error(arg[0], arg[1], "numeric argument required");
		free_exit(ms, exe, 255);
	}
	if (arry_size(arg) > 2)
	{
		if (g_ms.pid != 0)
			print_error(arg[0], NULL, "too many arguments");
		g_ms.error = 1;
		return ;
	}
	if (size_check(arg) == 1)
	{
		if (g_ms.pid != 0)
			print_error(arg[0], arg[1], "numeric argument required");
		free_exit(ms, exe, 255);
	}
	if (arg[1] != NULL)
		code = ft_atol(arg[1]) % 256;
	free_exit(ms, exe, code);
}
