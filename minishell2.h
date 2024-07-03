/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell2.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amimouni <amimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 05:21:19 by amimouni          #+#    #+#             */
/*   Updated: 2022/11/27 08:17:38 by amimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL2_H
# define MINISHELL2_H

# include "dirent.h"
# include "libft/libft.h"
# include <curses.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <pthread.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <termios.h>
# include <unistd.h>

# define STDIN 0
# define STDOUT 1
# define STDERR 2
# define BUFF_SIZE 4000

//////////// parsing struct /////////////

enum					e_type
{
	CMD,
	ARG,
	INPUT_FILE,
	OUTPUT_FILE,
	HEREDOC,
	HEREDOC_OP,
	APPEND,
	INPUT_OP,
	OUTPUT_OP,
	APPEND_OP,
	PIPE,
	D_QUOTES,
	S_QUOTES,
	NO_QUOTES
};

typedef struct s_file
{
	int					fd;
	int					type;
}						t_file;

typedef struct s_minishell
{
	char				*data;
	int					type;
	t_file				file;
	int					quotes;
	struct s_minishell	*next;
}						t_minishell;

typedef struct s_token
{
	char				*parse_line;
	char				**pip_split;
	int					quotes;
	char				a;
	char				b;
	int					i;
	int					j;
	int					n;
	int					s_quot;
	int					d_quot;
	int					if_true;
}						t_token;

///////// execution struct ////////////////////////

typedef struct s_list
{
	void				*content;
	long				content_size;
	struct s_list		*next;
}						t_list;

typedef struct s_sig
{
	int					sigint;
	int					sigquit;
	pid_t				pid;
	int					exit_status;
	int					flag;
	int					hereflag;
}						t_sig;

typedef struct s_list_env
{
	char				*value;
	struct s_list_env	*next;

}						t_list_env;

typedef struct s_shell
{
	t_list_env			*export_env;
	t_list_env			*env;
	t_minishell			**start;
	int					in;
	int					out;
	int					fdin;
	int					fdout;
	int					here_in;
	int					pipin;
	int					pipout;
	int					pid;
	int					charge;
	int					parent;
	int					last;
	int					ret;
	int					exit;
	int					no_exec;
	int					n;
	int					tmp_fd;
	int					*pip;
}						t_shell;

t_sig					g_sig;
//////////// or Execution //////////////
void					replace_env(t_list_env **list, char *name, char *value);
char					*find_env(t_shell **list, char *name);
void					add_env(t_list_env **lst, t_list_env *new);
void					ft_list_sort_env(t_list_env **lst);
void					del_at_env(t_list_env **lst, char *str);
int						ft_cd(char **args, t_list_env *env,
							t_list_env *export_env);
int						ft_echo(char **argv);
int						run_env(t_list_env *env);
void					run_exit(char **av, t_shell *t_mini);
int						run_export(char **args, t_list_env *env,
							t_list_env *export_env);
int						ft_pwd(void);
int						run_unset(char **a, t_shell *mini);
void					free_tab(char **tabs);
void					sig_handler(int sig);
void					sig_handler_quit(int code);
void					print_prompt(int clear);
int						run_builtins(char **argv, t_shell *mini);
void					init_sig(void);
void					print_sorted_env(t_list_env *env);
int						is_valid_env(char *env);
void					exec_cmd(t_shell *mini, t_minishell *token);
int						run_bin(char **av, t_list_env *env, t_shell *mini);
char					*env_to_str(t_list_env *lst, int i, int j);
void					redir(t_shell *mini, t_minishell *token, int type);
void					input(t_shell *mini, t_minishell *token);
void					minipipe(t_shell *mini, t_minishell *token);
void					input(t_shell *mini, t_minishell *token);
int						is_in_env(t_list_env *env, char *args);
int						env_add(const char *value, t_list_env *env);
void					execution(t_shell *ptr);
void					reset_std(t_shell *mini);
void					close_fds(t_shell *mini);
void					reset_fds(t_shell *mini);
void					ft_close(int fd);
void					heredoc_func(t_shell *head, t_minishell *token);
void					redir_and_exec(t_shell *mini, t_minishell *token);
void					signals(void);
void					free_token(t_shell *t_mini);
void					init_shell(t_shell *t_mini);
int						init_env(t_shell *mini, char **env_array);
int						init_export_env(t_shell *mini, char **env_array);
int						update_oldpwd(t_list_env *env);
int						update_pwd(t_list_env *env);
void					free_node_export(t_shell *mini, t_list_env *env);
void					free_node(t_shell *mini, t_list_env *env);
int						env_add(const char *value, t_list_env *env);
int						error_print(char *path);
void					free_exit(char **env_arr, int ret);
int						exev(char *path, char **av, t_list_env *env);
void					signal_for_blocking_cmd(void);
void					export_enva(char *args, t_list_env *env_exp,
							int error_ret, t_list_env *env);
char					*get_env_path(t_list_env *env, const char *var,
							int len);
void					get_oldpwd(t_list_env *env, t_list_env *export_env,
							char *env_path);
void					updated_pwd(t_list_env *env, t_list_env *export_env);
////////////for the parsing//////////////

char					*handling_quotes(char *str, char a, char b);
char					*ft_strcpy(char *dst, const char *str);
//int			ft_strchr(const char *s, int c);
t_minishell				**parser(t_token *ptr, char **env, t_shell *mini);
int						ft_strnstr(const char *haystack, const char *needle);
char					**ft_split(char const *s, char c);
char					*ft_substr(char const *s, unsigned int start,
							size_t len);
char					*ft_strdup(const char *s1);
size_t					ft_strlen(const char *s);
int						ft_memcmp(const void *s1, const void *s2);
char					*ft_strjoin(char const *s1, char const *s2);
int						ft_isdigit(int c);
char					*copy_no_dollar(char *str, char *tmp, t_token *ptr);
int						quot_cont(char *str, int n, char sep);
int						check_dollar(char *str, int i);
int						cont_dollar(char *str, int i);
char					*copy_no_expand(char *str, char *tmp, t_token *ptr,
							t_shell *mini);
char					*digit_expand(char *str, char *tmp, t_token *ptr,
							char **env);
char					*dollar_expand(char *str, char *tmp, t_token *ptr,
							char **env);
char					*expand(char *str, int i, char **env);
char					**alloc_des(char **env);
void					ft_free(char **dst);
char					*count_space_and_alloc(char *str, char *dest, int i);
int						add_after_opirations(char **str, char **dest, int *i,
							int *j);
int						add_inside_quot(char **str, char **dest, int *i,
							int *j);
void					add_befor_opirations(char **str, char **dest, int *i,
							int *j);
char					*handling_spaces(char *str);
t_minishell				*fill_stack(t_minishell *stack_a, char **str,
							char **env, t_shell *mini);
char					*remove_quotes(char *str);
int						check_quot(char *str);
int						cont_quot(char *str);
char					*comper_to_env(char *dest, char **env);
char					*check_expand(char *str, char **env, int type,
							t_shell *mini);
char					**replace_in_quotes(char **str, char a, char b);
void					define_cmd(t_minishell **tokens);
t_minishell				**sep_split(char **str, char sep, char **env,
							t_shell *mini);
char					*get_next_line(int fd);
char					*ft_strrjoin(char const *s1, char const *s2);
char					*handling_tab(char *str);
char					**put_in_tab(t_shell *mini);
int						check_error(char **str);
int						check_error_2(char *str);
char					*copy(t_token *ptr, char *str, char *dest, char *tmp);
void					count_for_alloc(char *str, t_token *ptr);
int						error_unexpected(char **str, int i, int n,
							t_shell *mini);
char					*handling_and_expanding(char **str, int i, char **env,
							t_shell *mini);
void					init_tmp(t_minishell *tmp, char **str, int i);
int						get_type(int i, char **str);
int						cont_dif_puot(char *str, int *i);
void					copy_without_quot(char *str, char *dest, int *i,
							int *j);
int						replace_tab(char *str, char *dest, int *i, int *j);

#endif
