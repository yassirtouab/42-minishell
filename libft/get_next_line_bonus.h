/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouab <ytouab@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 12:31:06 by ytouab            #+#    #+#             */
/*   Updated: 2022/04/02 08:14:16 by ytouab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*ft_read(int fd, char *save);
char	*ft_left_line(char *s);
char	*ft_line(char *s);
char	*get_next_line(int fd);
size_t	ft_strlen(const char *str);
char	*ft_strjoingnl(char *s1, char *s2);
size_t	ft_nl_index(char *str);

#endif
