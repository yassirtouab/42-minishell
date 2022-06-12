/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sali <sali@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 12:07:39 by sali              #+#    #+#             */
/*   Updated: 2022/05/25 12:07:40 by sali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	redirect_input(t_redir *redir, char **namein)
{
	if (access(redir->name, F_OK | R_OK) == 0)
		*namein = redir->name;
	else
	{
		if (errno == 13)
			print_error(redir->name, NULL, "permission denied");
		else
			print_error(redir->name, NULL, "No such file or directory");
		g_ms.error = 1;
		return (-1);
	}
	return (0);
}

int	out_redir(t_set_redir *s_redir)
{
	if (access(s_redir->redir->name, F_OK) != 0)
	{
		s_redir->fd = open(s_redir->redir->name, O_CREAT);
		close (s_redir->fd);
		s_redir->opentype = 1;
		s_redir->nameout = s_redir->redir->name;
	}
	else
	{
		if (access(s_redir->redir->name, F_OK | W_OK) == 0)
		{
			s_redir->fd = open(s_redir->redir->name, O_CREAT);
			close (s_redir->fd);
			s_redir->opentype = 1;
			s_redir->nameout = s_redir->redir->name;
		}
		else
		{
			write(2, "error file permissions\n", 24);
			return (-1);
		}
	}
	return (0);
}

int	append_redir(t_set_redir *s_redir)
{
	if (access(s_redir->redir->name, F_OK) != 0)
	{
		s_redir->fd = open(s_redir->redir->name, O_CREAT);
		close (s_redir->fd);
		s_redir->opentype = 2;
		s_redir->nameout = s_redir->redir->name;
	}
	else
	{
		if (access(s_redir->redir->name, F_OK | W_OK) == 0)
		{
			s_redir->opentype = 2;
			s_redir->nameout = s_redir->redir->name;
		}
		else
		{
			write(2, "error file permissions\n", 24);
			return (-1);
		}
	}
	return (0);
}

int	pick_redir(t_set_redir *s_redir)
{
	while (s_redir->redir != NULL)
	{
		if (ft_strncmp(s_redir->redir->type, "<", 2) == 0)
		{
			if (redirect_input(s_redir->redir, &s_redir->namein) == -1)
				return (-1);
		}
		else if (ft_strncmp(s_redir->redir->type, ">", 2) == 0)
		{
			if (out_redir(s_redir) == -1)
				return (-1);
		}
		else if (ft_strncmp(s_redir->redir->type, ">>", 3) == 0)
		{
			if (append_redir(s_redir) == -1)
				return (-1);
		}
		else if (ft_strncmp(s_redir->redir->type, "<<", 3) == 0)
		{
			s_redir->herefd = s_redir->redir->fd;
			s_redir->namein = "heredoc";
		}
		s_redir->redir = s_redir->redir->next;
	}
	return (0);
}

int	redirect(t_redir *r)
{
	t_set_redir	s_redir;

	s_redir.redir = r;
	s_redir.namein = NULL;
	s_redir.nameout = NULL;
	s_redir.herefd = -1;
	s_redir.opentype = 0;
	if (pick_redir(&s_redir) == -1)
		return (-1);
	dup_redirections(&s_redir);
	return (0);
}
