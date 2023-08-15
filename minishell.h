/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fila <rel-fila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 14:40:25 by mpezongo          #+#    #+#             */
/*   Updated: 2023/08/15 08:20:54 by rel-fila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

# define PIPE 6
# define RIN 5
# define ROUT 4
# define APPEND 3
# define HEREDOCUMENT 2
# define WORD 1
# define WELCOME_MSG	"\033[31m╔════════════════════════════════════════════════════════════════════════════════╗\033[0m\n\
\033[31m║                                                                                ║\033[0m\n\
\033[31m║                  \033[1;32m█▀█ █▀▀ █▀▀   █▀█ █▀█ █▀▀ █▀ █▀▀ █▄░█ ▀█▀ █▀                  \033[31m║\033[0m\n\
\033[31m║                  \033[1;32m█▀▀ █▀░ █▄▄   █▀▀ █▀▄ ██▄ ▄█ ██▄ █░▀█ ░█░ ▄█                  \033[31m║\033[0m\n\
\033[31m║                                                                                ║\033[0m\n\
\033[31m║      \033[32m ███╗░░░███╗██╗███╗░░██╗██╗░██████╗██╗░░██╗███████╗██╗░░░░░██╗░░░░░       \033[31m║\033[0m\n\
\033[31m║      \033[32m ████╗░████║██║████╗░██║██║██╔════╝██║░░██║██╔════╝██║░░░░░██║░░░░░       \033[31m║\033[0m\n\
\033[31m║      \033[32m ██╔████╔██║██║██╔██╗██║██║╚█████╗░███████║█████╗░░██║░░░░░██║░░░░░       \033[31m║\033[0m\n\
\033[31m║      \033[32m ██║╚██╔╝██║██║██║╚████║██║░╚═══██╗██╔══██║██╔══╝░░██║░░░░░██║░░░░░       \033[31m║\033[0m\n\
\033[31m║      \033[32m ██║░╚═╝░██║██║██║░╚███║██║██████╔╝██║░░██║███████╗███████╗███████╗       \033[31m║\033[0m\n\
\033[31m║      \033[32m ╚═╝░░░░░╚═╝╚═╝╚═╝░░╚══╝╚═╝╚═════╝░╚═╝░░╚═╝╚══════╝╚══════╝╚══════╝       \033[31m║\033[0m\n\
\033[31m║                                                                                ║\033[0m\n\
\033[31m║               Created by : Ridwane el filali  && Mickael Pezongo               ║\033[0m\n\
\033[31m╚══════════════════════════════════════════════════════════════════════\
══════════╝\033[0m"

# define PROMPT "\033[1;32mMinishell$ \033[0m"
# define EXIT_MSG "\033[1;31mexit\033[0m"
# define SYN_ERR "\033[1;31msyntaxe error\033[0m"

typedef struct s_global
{
	int	heredoc;
	int	exit_code;
	int	quitting;
}	t_global;

t_global	g_global;

typedef struct s_envp
{
	char			*name;
	char			*content;
	int				sign;
	struct s_envp	*next;
}	t_envp;

typedef struct s_parsing
{
	char				**words;
	int					out_file;
	int					in_file;
	struct s_parsing	*next;
}	t_parsing;

typedef struct s_lexer
{
	char			*str;
	int				banner;
	int				category;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}	t_lexer;

void		save_env(t_envp **envp, char **env);
size_t		ft_strlen(const char *s);
int			ft_atoi(const char *str);
char		*ft_strdup(const char *s1);
char		*ft_itoa(int n);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
t_envp		*ft_lst_new_env(char *name, char *content);
void		ft_lst_add_back_env(t_envp **lst, t_envp *new);
t_envp		*ft_lstlast(t_envp *lst);
char		**treate_empty_env(void);
t_envp		*get_var(t_envp **envp, char *str);
void		free_arg(char **env);
void		start_shell(t_envp **envp, t_parsing **parsings);
int			check_spaces(char *line);
int			check_line(char *line);
int			tokenization(char *data_entry, char **tmp, t_envp **envp);
void		get_str(t_lexer *lexer, char **tmp);
int			check_pipe(char *line);
int			check_redirections(char *line, char r);
int			check_quotes(char *line);
char		*divide_words(char *data_entry);
int			check_heredoc(char *str, int i);
int			create_lexer_list(t_lexer **lexer, char *line);
t_lexer		*ft_lexernew(char *str, int token);
void		ft_lexeradd_back(t_lexer **lst, t_lexer *new);
char		*ft_substr(char const *s, unsigned int start, size_t len);
void		pass_quotes(char *args, int *i, char quote);
int			is_whitespace(char c);
void		by_pass_whitespace(char *args, int *i);
int			check_lexer_list(t_lexer *lexer);
void		free_lexer(t_lexer **lst);
int			ft_lstsize(t_lexer *lst);
t_lexer		*expand(char *line, t_envp **envp);
char		*divide_words(char *data_entry);
void		add_spaces(int *i, int *j, char *str, char *data_entry);
char		**ft_split(char const *s, char c);
char		*ft_strtrim(char const *s1, char const *set);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
void		invert_inside_quotes(char *line);
char		*expand_word(char *str, t_envp *envp);
char		*expand_var(char *str, int *i, t_envp **envp);
char		*expand_insin_quote(char *str, int *i);
char		*ft_strjoin(char const *s1, char const *s2);
char		*expand_indoub_quote(char *str, int *i, t_envp **envp);
char		*get_char(char c);
void		check_inside_for_money(char *s, int *i, char **t, t_envp **e);
void		treate_operator(char *str, t_lexer **lexer, int *i);
int			is_operator(char c);
void		treate_word(char *str, t_lexer **lexer, int *i, t_envp **envp);
void		gather_words(t_lexer *lexer);
char		*ft_strchr(const char *s, int c);
char		*remove_quot(char *str);
void		remove_quot_keep_track(char *tmp, char *str, int *j);
int			parsing(t_lexer **lexer, t_parsing **parsing, t_envp **envp);
int			count_words(t_lexer *lexer);
void		ft_count_words(char *str, int *word_count);
void		parser_1(t_lexer *lexer, int *i, char **tmp);
int			treate_redirection_out(char *str, int check);
int			treate_redirection_in(char *str);
t_parsing	*ft_lst_new_parser(int in_file, int out_file, char **str);
t_parsing	*ft_lst_last_parsing(t_parsing *lst);
void		ft_lst_add_back_parser(t_parsing **lst, t_parsing *new);
void		free_arg(char **env);
int			get_heredocument_in(t_lexer *lexer, t_envp **envp);
char		*get_name_heredoc(void);
void		handle_signal(int sign);
void		set_up_signals(void);
void		init_signals(void);
void		ft_putstr_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
void		ft_putchar_fd(char c, int fd);
void		execute(t_envp *envp, t_parsing *parsing);
void		check_exit_code(t_envp *envp);
void		execute_one_command(t_parsing *parsing, t_envp *envp);
void		env_cmd(t_parsing *parsing, t_envp *envp);
void		pwd_cmd(t_parsing *parsing, t_envp *envp);
void		cd_cmd(t_parsing *parsing, t_envp *envp);
void		update_exit_code(t_envp *envp, int ret);
void		echo_cmd(t_parsing *parsing, t_envp *envp);
void		export_cmd(char **str, t_envp *envp);
char		*get_env_name(char *env);
char		*get_env_content(char *env);
t_envp		*get_envp(t_envp *envp, char *str);
int			check(char *str, t_envp *envp);
int			check_existed(t_envp *envp, char *name);
void		unset_cmd(char **str, t_envp **envp);
void		exit_cmd(char **str, t_envp *envp);
int			ft_lst_size_env(t_envp *lst);
void		execute_multiple_commands(t_parsing *p, t_envp *e, int *f);
void		get_exit_of_process(int ret, t_envp *envp);
char		**fill_table(t_envp	*env);
void		exec_error(char *tmp);
char		*ft_strjoin_add_bs(char *s1, char *s2);
char		**ft_get_path(t_envp *env);
void		ft_lst_add_fron_envp(t_envp **lst, t_envp *new);
int			open_heredoc(char *readln, int *file, char *str, t_envp **envp);
void		ft_lst_add_front_env(t_envp **lst, t_envp *new);
int			check_alphabet(int a);
void		sigint_handler(int sig);
void		treate_dollar(t_lexer **lexer, t_envp **envp, char *str, int *i);
t_envp		*envp_copy(t_envp *env);
int			check_sorted(t_envp *exp);
void		ft_lst_clear_envp(t_envp *envp);
void		print_envp(t_envp *envp, t_parsing *parsing);
void		free_name_content(char *name, char *content);
void		run_cmd(t_parsing *parsing, t_envp *envp, char **path, char *str);
int			chek_word(char const *a, char c);
char		**ft_chek(char const *s, char c, char **strings, int words_count);
char		**ft_split1(char const *s, char c);
char		**ft_get_path(t_envp *env);
void		close_all_fd(t_parsing *parsing, int *fd, int old);
void		duplicate(t_parsing *parc, int *fd, int old);
int			ft_execute_m_cmd(int *i, char **s, t_parsing	*pa, char **p);
char		*expand_var2(char *str, int *i, char *tmp1, t_envp **envp);
char		*expard_var3(char *str, int *i, t_envp **envp, t_envp *node);
int			check_is_2_quotes(char *tmp, int quote);
char		*expand_insin_quote2(char *tmp, int j);
void		open_heredoc2(char *readln, int *file, t_envp **envp);
int			set_operator(char *line, int *i, t_lexer **lexer_list);
int			treate_inf(char *line, int *i, t_lexer **lexer_list, t_lexer *new);
int			treate_sup(char *line, int *i, t_lexer **lexer_list, t_lexer *new);
void		treate_quote2(char *str, char **tmp, t_envp **envp, int *i);
void		treate_word2(char *str, char **tmp, int *i, t_envp **envp);
char		*treate_dou_quote(char *str, int *i, char *tmp, t_envp **envp);
char		*treate_sin_quote(char *str, int *i, char *tmp);
char		**treate_empty_env(void);
t_envp		*get_var(t_envp **envp, char *str);

#endif
