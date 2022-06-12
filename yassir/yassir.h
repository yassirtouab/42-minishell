/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yassir.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouab <ytouab@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 15:34:28 by ytouab            #+#    #+#             */
/*   Updated: 2022/03/19 15:34:28 by ytouab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef YASSIR_H
# define YASSIR_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include "../libft/libft.h"

# define PROMPT "\033[1;32m✓\033[0;36m\033[1m Minishell \033[1;32m▶ \033[0m"

typedef struct s_cmd
{
	struct s_cmd	*prev;
	char			*p_op;
	char			*cmdl;
	char			**arg;
	char			*n_op;
	struct s_cmd	*next;
}				t_cmd;

typedef struct s_ms
{
	char		*line;
	char		**env;
	t_cmd		*lst;
	int			perror;
	int			pipe;
	int			error;
	int			quot;
	pid_t		pid;
}				t_ms;

t_ms	g_ms;

	// Quote Clean

char	*ft_quote_clean(char *s);
int		ft_quote_index(int i, char *s, int	*quote);
int		ft_index_out_quote(int i, char *s);
char	*ft_strjoin_free(char *s1, char *s2);

	// Quote Split

char	**ft_quote_split_charset(char *str, char *charset);
int		ft_quote_count_words(char *str, char *charset);
int		ft_inquote(char s, int *quote);
int		ft_delimiter(char c, char *charset);

	// Operations Split

void	ft_op_split(char *s, char *charset);
int		ft_count_words(char *str, char *charset);
char	**ft_split_charset(char *str, char *charset);
char	*ft_take_operator(char *s, size_t *i);

	// TOOLS

char	**ft_ms_init(int ac, char **av, char **env_vars);
void	ft_free_line(void);
void	ft_freedom(void);

	// list functions

t_cmd	*ft_cmdnew(void);
t_cmd	*ft_cmdlast(t_cmd *lst);
void	ft_cmdadd_back(t_cmd **lst, t_cmd	*new);
int		ft_lstlen(t_cmd *lst);
void	ft_lstfree(t_cmd **lst);
void	ft_lst_env_var(t_cmd *lst);

	// PARSING

void	ft_lstprint(t_cmd *lst);
void	ft_lst_splitargs(t_cmd *lst);
void	ft_lst_cleanquotes(t_cmd *lst);
void	ft_parse(void);

	// ENV

char	**ft_double_arr_dup(char **arr);
char	*ft_take_var_name(char	*env_var);
char	*ft_var_from_str(size_t *start, char *str);
char	*ft_var_value(char *var);
int		ft_valid_env_replace(char *s);
char	*ft_replace_env_var(char *s, int quote, size_t i, char *ret);
char	*ft_exit_value(char *var);

	// EXPORT

void	ft_arr_print(char **arr);
void	ft_export(char **arg);
char	**ft_export_var(char *var);
void	ft_replace_var(char *var);
int		ft_existing_var(char *var);

	// UNSET

// void	ft_unset(char **arg);
char	**ft_unset_index_arr(char **arr, int i);
void	ft_unset(char **arg);

	// ERROR HANDLING

int		ft_all_delimiter(char *s, char *charset);
int		ft_unclosed_quote(char *s);
void	ft_invalid_ops(char *s, size_t i, int quote, char *op);
void	ft_lst_operators_check(t_cmd *lst);
void	ft_check_perror(void);
void	ft_perror(int perror);

#endif
