# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Sali <sali@student.42abudhabi.ae>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/17 14:55:51 by ytouab            #+#    #+#              #
#    Updated: 2022/05/25 13:40:25 by Sali             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= minishell

LIBFT_DIR	=	libft

LIBFT		=	libft.a

OBJS		= ${SRC:.c=.o}

WHITE		=	"\033[0m"
RED			=	"\033[0;31m"
GREEN		=	"\033[1;32m"
YELLOW		=	"\033[0;33m"

RM			=	rm -f

CC		=	gcc -g

CF		=	-Wall -Wextra -Werror

RLF		=	-lreadline

YS			=	yassir/error.c \
				yassir/env.c \
				yassir/env_2.c \
				yassir/env_3.c \
				yassir/parse.c \
				yassir/op_split.c \
				yassir/quote_clean.c \
				yassir/quote_split.c \
				yassir/tools/list_utils.c \
				yassir/tools/main_utils.c \
				yassir/tools/parse_lst_utils.c \
				yassir/tools/parse_utils.c \

SM			=	saim/arrange_parse.c\
				saim/builtins.c\
				saim/echo.c\
				saim/exec.c\
				saim/exit-status.c\
				saim/exit.c\
				saim/free_helpers.c\
				saim/heredoc.c\
				saim/parse_builtin.c\
				saim/pipes.c\
				saim/redirections.c\
				saim/redirection_utils.c\
				saim/utils_two.c\
				saim/utils.c\
				saim/signals.c


SRCS		=	 \


SRC			=	minishell.c \
				${YS} \
				${SM} \
				${SRCS} \

RL_MAC		= -L /usr/local/Cellar/readline/8.1/lib -I /usr/local/Cellar/readline/8.1/include

RL_INC_MAC = -I /usr/local/Cellar/readline/8.1/include

.c.o:
		@${CC} ${CF} -c ${RL_INC_MAC} $< -o ${<:.c=.o}


$(NAME):	${OBJS} ${LIBFT}
		@${CC} ${CF} ${OBJS} $(LIBFT_DIR)/$(LIBFT) -o ${NAME} ${RLF} ${RL_MAC}
		@echo ${GREEN}"Compilation Done ✅"

${LIBFT}:
		@make -C $(LIBFT_DIR) bonus
		@make -C $(LIBFT_DIR) clean

all:	${NAME}

clean:
		@${RM} ${OBJS}
		@echo ${RED}"Object Files Deleted ✅"${WHITE}

fclean:	clean
		@make -C $(LIBFT_DIR) fclean
		@${RM} ${NAME}
		@echo ${RED}"Executable File Deleted ✅"${WHITE}

re:		fclean all

.PHONY:		all clean fclean re
