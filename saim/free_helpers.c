/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sali <sali@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 12:07:18 by sali              #+#    #+#             */
/*   Updated: 2022/05/25 13:18:30 by Sali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_arry(char **arry)
{
	int	i ;

	i = 0;
	while (arry[i] != NULL)
	{
		free (arry[i]);
		i++;
	}
	free (arry[i]);
	free (arry);
}

void	free_exit(t_ms *ms, t_arg *exe, int exitcode)
{
	ms->pipe = ms->pipe + 1;
	ms->pipe = ms->pipe - 1;
	free_arg(exe);
	ft_lstfree(&g_ms.lst);
	exit (exitcode);
}

void	free_arg(t_arg *arg)
{
	t_arg	*arg_temp;
	t_redir	*rd_temp;
	int		i;

	while (arg != NULL)
	{
		i = 0;
		while (arg->exec != NULL && arg->exec[i] != NULL)
		{
			free (arg->exec[i]);
			i++;
		}
		if (arg->exec != NULL)
			free (arg->exec[i]);
		free (arg->exec);
		free_redir(arg, &rd_temp);
		arg_temp = arg;
		arg = arg->next;
		free (arg_temp);
	}
}

void	free_redir(t_arg *arg, t_redir **rd_temp)
{
	while (arg->redir != NULL)
	{
		if (arg->redir->name != NULL)
			free(arg->redir->name);
		if (arg->redir->type != NULL)
			free(arg->redir->type);
		*rd_temp = arg->redir;
		arg->redir = arg->redir->next;
		free (*rd_temp);
	}
}

t_redir	*new_redir(char *type, char *name)
{
	t_redir	*temp;

	temp = (t_redir *) malloc(sizeof(t_redir) * 1);
	temp->type = ft_strdup(type);
	temp->name = ft_strdup(name);
	temp->next = NULL;
	temp->fd = -1;
	return (temp);
}
