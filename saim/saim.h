/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   saim.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouab <ytouab@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 12:08:32 by sali              #+#    #+#             */
/*   Updated: 2022/06/12 17:48:57 by ytouab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SAIM_H
# define SAIM_H

# include "../minishell.h"

typedef struct s_redir
{
	char			*type;
	char			*name;
	int				fd;
	struct s_redir	*next;
}		t_redir;

typedef struct s_arrange_redir
{
	int		fd;
	int		herefd;
	int		opentype;
	char	*namein;
	char	*nameout;
	t_redir	*redir;
}		t_set_redir;

typedef struct s_arg
{
	char			**exec;
	t_redir			*redir;
	struct s_arg	*next;
	int				i;
}		t_arg;

int			ft_isspace(const char str);
void		ft_clear(void);
int			get_env_index(char *str);
void		init_heredoc(t_arg *exe);
void		close_heredoc(t_arg *exe);
long long	ft_atol(const char *str);
int			s_strncmp(char *s1, char *s2, int size);
int			is_builtin(char *str);
void		builtin_parent_child(t_arg *exe, t_ms *ms);
char		*file_append(char *path, char *exec_name);
char		*ft_getenv(char *str, t_ms *ms, int i, int j);
char		*file_path(char *exec_name, t_ms *ms);
void		new_line_check(int *newline, char **arry, int *i, int *j);
void		echo_n_skip(char **arry, int *i, int *j, int *newline);
void		ft_echo(char **arry);
void		ft_cd(char **arg);
void		ft_pwd(void);
void		ft_env(t_ms *ms);
void		free_redir(t_arg *arg, t_redir **rd_temp);
void		free_arg(t_arg *arg);
int			arry_size(char **arry);
void		print_error(char *cmd, char *arg, char *error);
void		free_env(char **env);
void		free_exit(t_ms *ms, t_arg *exe, int exitcode);
int			alpha_check(char **arry);
int			size_check(char **arry);
void		exit_mh(t_ms *ms, t_arg *exe, char **arg, int code);
int			builtin(t_ms *ms, t_arg *exe, pid_t pid);
int			exec_cmd(char **arg_list, t_ms *ms);
void		set_pipe(int i, int pipes, int *fd);
char		*expand_dollar(char *str, int i, t_ms *ms);
char		*expanded_string(char *before_dlr, int i, t_ms *ms, char *str);
int			env_expand(char **str, t_ms *ms);
void		heredoc(int *fd, char *end);
int			redirect_input(t_redir *redir, char **namein);
int			redirect(t_redir *r);
void		close_wait(t_ms *ms, int *fd, t_arg *exe);
int			*init_pipe(t_ms *ms);
void		exec_lst(t_ms *ms, t_arg *exe, int *fd);
void		execute(t_ms *ms, t_arg *exe);
t_arg		*new_arg(void);
t_redir		*new_redir(char *type, char *name);
void		free_arry(char **arg);
char		**reset_arry(char **arg, char *add);
void		set_new_redir(t_arg *arg, t_redir **head,
				t_cmd *ptr, char *type);
void		arrange_helper(t_arg *arg, t_cmd *ptr,
				t_redir **redir_head, int *i);
t_arg		*arrange_parse(t_cmd *ptr);
char		**set_environment(char **envp);
void		dup_redirections(t_set_redir *s_redir);
void		sig_handler(int sig);
void		ft_signals(void);
void		eof_check(void);
void		set_shell_level(int input);

#endif
