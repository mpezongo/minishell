NAME = minishell.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
SRC = builtins/cd_cmd.c builtins/echo_cmd.c builtins/env_cmd.c builtins/exit_cmd.c builtins/export_cmd.c builtins/pwd_cmd.c builtins/unset_cmd.c builtins/utils.c \
	libft/ft_atoi.c libft/ft_fd.c libft/ft_itoa.c libft/ft_lstsize.c libft/ft_split.c libft/ft_strchr.c libft/ft_strdup.c libft/ft_strjoin.c libft/ft_strlcpy.c libft/ft_strlen.c \
	libft/ft_strncmp.c libft/ft_strtrim.c libft/ft_substr.c check_line_utils.c check_line.c execute_multiple_commands.c execute.c expand_word.c expand.c ft_free.c heredoc.c \
	lexer_list_checker.c lexer_utils.c lexer.c main.c parsing_redirection.c parsing_utils.c parsing.c remove_quot.c signal.c start_shell.c tokenization.c \
	treate_env_utils.c treate_env.c treate.c utils.c execute_utils.c execute_utils_2.c execute_utils_3.c execute_multiple_commands_utils.c expand2.c expand_word2.c expand_word3.c\
	lexer2.c treate2.c treate_env_utils2.c\

USER := $(shell id -un)

LDFLAGS= -L/goinfre/${USER}/homebrew/opt/readline/lib

CPPFLAGS= -I/goinfre/${USER}/homebrew/opt/readline/include

LIBS = -lreadline


OBJ = ${SRC:.c=.o}

all : $(NAME)

$(NAME) : $(OBJ) minishell.h
	@ar rc $(NAME) $(OBJ)
	@${CC} ${CFLAGS} ${LDFLAGS} ${CPPFLAGS} ${LIBS} main.c ${NAME} -o minishell

clean :
	@${RM} ${OBJ} minishell.a

fclean : clean
	@${RM} $(NAME) minishell

re : fclean all