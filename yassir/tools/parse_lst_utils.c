/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lst_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouab <ytouab@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 00:53:50 by ytouab            #+#    #+#             */
/*   Updated: 2022/04/30 00:53:50 by ytouab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../yassir.h"

void	ft_lstprint(t_cmd *lst)
{
	size_t	i;

	if (!lst)
		return ;
	while (lst->prev)
		lst = lst->prev;
	while (lst)
	{
		i = 0;
		ft_putendl_fd("******************************\n", 1);
		ft_putstr_fd("Prev op: |", 1);
		ft_putendl_fd(lst->p_op, 1);
		ft_putstr_fd("Line:    |", 1);
		ft_putendl_fd(lst->cmdl, 1);
		ft_putstr_fd("Next op: |", 1);
		ft_putendl_fd(lst->n_op, 1);
		ft_putstr_fd("\n", 1);
		ft_putstr_fd("Args:\n", 1);
		ft_putstr_fd("\n", 1);
		while (lst->arg && lst->arg[i])
			ft_putendl_fd(lst->arg[i++], 1);
		ft_putendl_fd("******************************\n", 1);
		lst = lst->next;
	}
}

void	ft_lst_splitargs(t_cmd *lst)
{
	if (!lst)
		return ;
	while (lst->prev)
		lst = lst->prev;
	while (lst)
	{
		if (lst->cmdl)
			lst->arg = ft_quote_split_charset(lst->cmdl, " \t\v\r\f\n");
		lst = lst->next;
	}
}

void	ft_lst_cleanquotes(t_cmd *lst)
{
	size_t	i;
	char	*tmp;

	i = 0;
	if (!lst)
		return ;
	while (lst->prev)
		lst = lst->prev;
	while (lst)
	{
		i = 0;
		while (lst->arg && lst->arg[i])
		{
			if (ft_strchr(lst->arg[i], '"') || ft_strchr(lst->arg[i], '\''))
			{
				tmp = ft_strdup(lst->arg[i]);
				free(lst->arg[i]);
				lst->arg[i] = ft_quote_clean(tmp);
				free(tmp);
			}
			i++;
		}
		lst = lst->next;
	}
}

void	ft_lst_env_var(t_cmd *lst)
{
	char	*tmp;

	if (!lst)
		return ;
	while (lst->prev)
		lst = lst->prev;
	while (lst)
	{
		if (lst->cmdl && ft_strchr(lst->cmdl, '$'))
		{
			if (ft_strncmp(lst->p_op, "<<", 3))
			{
				tmp = ft_strdup(lst->cmdl);
				if (lst->cmdl)
					free(lst->cmdl);
				lst->cmdl = ft_replace_env_var(tmp, 0, 0, NULL);
			}
		}
		lst = lst->next;
	}
}
