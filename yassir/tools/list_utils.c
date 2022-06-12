/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouab <ytouab@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 04:30:03 by ytouab            #+#    #+#             */
/*   Updated: 2022/04/30 00:41:06 by ytouab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../yassir.h"

t_cmd	*ft_cmdnew(void)
{
	t_cmd	*new;

	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->cmdl = NULL;
	new->arg = NULL;
	new->n_op = NULL;
	new->p_op = NULL;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

int	ft_lstlen(t_cmd *lst)
{
	int		i;

	i = 0;
	if (!lst)
		return (0);
	while (lst->prev)
		lst = lst->prev;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

void	ft_lstfree(t_cmd **lst)
{
	t_cmd	*tmp;
	size_t	i;

	if (!lst || !ft_lstlen(*lst))
		return ;
	while ((*lst)->prev)
		*lst = (*lst)->prev;
	while (*lst)
	{
		i = 0;
		tmp = (*lst)->next;
		free((*lst)->cmdl);
		while ((*lst)->arg && (*lst)->arg[i])
			free((*lst)->arg[i++]);
		free((*lst)->arg);
		if ((*lst)->n_op)
			free((*lst)->n_op);
		free(*lst);
		*lst = tmp;
	}
}

t_cmd	*ft_cmdlast(t_cmd *lst)
{
	size_t	i;

	if (!lst)
		return (0);
	while (lst->prev)
		lst = lst->prev;
	i = ft_lstlen(lst);
	while (--i)
		lst = lst->next;
	return (lst);
}

void	ft_cmdadd_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*last;

	if (!new || !lst)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = ft_cmdlast(*lst);
	new->p_op = last->n_op;
	last->next = new;
	new->prev = last;
}
