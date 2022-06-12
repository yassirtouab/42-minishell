/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouab <ytouab@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 23:55:41 by ytouab            #+#    #+#             */
/*   Updated: 2022/05/01 23:55:41 by ytouab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "yassir.h"

void	ft_parse(void)
{
	ft_op_split(g_ms.line, "<>|");
	ft_lst_env_var(g_ms.lst);
	ft_lst_splitargs(g_ms.lst);
	ft_lst_cleanquotes(g_ms.lst);
}
