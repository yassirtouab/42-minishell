/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sali <sali@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 12:18:28 by sali              #+#    #+#             */
/*   Updated: 2022/05/25 12:18:29 by sali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	dup_redirections(t_set_redir *s_redir)
{
	if (s_redir->namein != NULL)
	{
		if (s_strncmp(s_redir->namein, "heredoc", 7) == 0)
		{
			dup2(s_redir->herefd, 0);
			close (s_redir->herefd);
		}
		else
		{
			s_redir->fd = open(s_redir->namein, O_RDONLY);
			dup2(s_redir->fd, 0);
			close (s_redir->fd);
		}
	}
	if (s_redir->nameout != NULL)
	{
		if (s_redir->opentype == 1)
			s_redir->fd = open(s_redir->nameout, O_WRONLY | O_TRUNC);
		else if (s_redir->opentype == 2)
			s_redir->fd = open(s_redir->nameout, O_WRONLY | O_APPEND);
		dup2(s_redir->fd, 1);
		close (s_redir->fd);
	}
}
