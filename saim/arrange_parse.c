/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrange_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sali <sali@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 12:06:56 by sali              #+#    #+#             */
/*   Updated: 2022/05/25 12:06:59 by sali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**reset_arry(char **arry, char *add)
{
	int		i;
	int		size;
	char	**temp;

	size = 0;
	i = 0;
	temp = NULL;
	while (arry != NULL && arry[size] != NULL)
			size++;
	temp = (char **) malloc(sizeof(char *) * (size + 2));
	while (arry != NULL && arry[i] != NULL)
	{
		temp[i] = ft_strdup(arry[i]);
		i++;
	}
	temp[i] = ft_strdup(add);
	temp[i + 1] = NULL;
	if (arry != NULL)
		free_arry(arry);
	return (temp);
}

void	set_new_redir(t_arg *arg, t_redir **head, t_cmd *ptr, char *type)
{
	if (arg->redir == NULL)
	{
		arg->redir = new_redir(type, ptr->arg[0]);
		*head = arg->redir;
	}
	else
	{
		arg->redir->next = new_redir(type, ptr->arg[0]);
		arg->redir = arg->redir->next;
	}
	arg->i = arg->i + 1;
}

void	arrange_redir(t_cmd *ptr, t_arg *arg, t_redir **redir_head)
{
	arg->i = 0;
	if (s_strncmp(ptr->p_op, "<", 1) == 0)
		set_new_redir(arg, redir_head, ptr, "<");
	else if (s_strncmp(ptr->p_op, ">", 1) == 0)
		set_new_redir(arg, redir_head, ptr, ">");
	else if (s_strncmp(ptr->p_op, "<<", 2) == 0)
		set_new_redir(arg, redir_head, ptr, "<<");
	else if (s_strncmp(ptr->p_op, ">>", 2) == 0)
		set_new_redir(arg, redir_head, ptr, ">>");
	while (ptr->arg != NULL && ptr->arg[arg->i] != NULL)
	{
		arg->exec = reset_arry(arg->exec, ptr->arg[arg->i]);
		arg->i = arg->i + 1;
	}
}

void	arrange_parse_helper(t_cmd *ptr, t_arg *arg)
{
	t_redir	*redir_head;

	redir_head = NULL;
	while (ptr != NULL)
	{
		arrange_redir(ptr, arg, &redir_head);
		if (s_strncmp(ptr->n_op, "|", 1) == 0)
		{
			g_ms.pipe = g_ms.pipe + 1;
			arg->redir = redir_head;
			redir_head = NULL;
			arg->next = new_arg();
			arg = arg->next;
		}
		ptr = ptr->next;
	}
	arg->redir = redir_head;
}

t_arg	*arrange_parse(t_cmd *ptr)
{
	t_arg	*arg;
	t_arg	*arg_head;

	g_ms.pipe = 0;
	arg = NULL;
	arg_head = NULL;
	while (ptr->prev != NULL)
		ptr = ptr->prev;
	if (ptr != NULL)
	{
		arg = new_arg();
		arg_head = arg;
	}
	arrange_parse_helper(ptr, arg);
	return (arg_head);
}
