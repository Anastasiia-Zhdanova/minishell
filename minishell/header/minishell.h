/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbeata <lbeata@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 01:42:32 by lbeata            #+#    #+#             */
/*   Updated: 2022/02/14 16:23:29 by mvirgini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <string.h>
# include <fcntl.h>
# include <signal.h>
# include <termios.h>

int	g_status_for_sig_int;

typedef struct s_params
{
	int				flag_exit;
	int				status;
	int				child;
	int				count_pipes;
	int				status_parser;
	int				status_command;
	int				error_is_printed;
	int				*fd_here_doc;
	int				count_here_doc;
	char			**name_here_doc;
	struct termios	start_consol;
	struct termios	consol_ignore;
}	t_params;

typedef struct s_redirect
{
	int	count;
	int	*fd;
}	t_redirect;

typedef struct s_list
{
	char			*name;
	char			*value;
	struct s_list	*next;
}	t_list;

typedef struct s_quotes
{
	int	single_quote;
	int	double_quote;
}	t_quotes;

typedef struct s_env
{
	char	*name_tmp;
	char	*value_tmp;
	int		shlvl;
	int		shlvl_status;
	int		i;
	int		j;
}	t_env;

int			ft_parser(t_list **list_env);
int			ft_start_here_doc_pipes(t_params *params,
				t_list **list_str, char **str, t_list **list_env);
void		ft_write_error(t_params *params, char status);
int			ft_parser_inside(t_params *params, t_list **list_env,
				char **str, t_list **list_str);
t_list		*ft_create_element(char *name, char *value);
void		ft_delete_element(t_list *to_del, t_list **head);
t_list		*ft_lstlast(t_list *list);
void		ft_push_back(t_list **lst, t_list *new);
int			ft_lstsize(t_list *lst);
void		ft_free_list(t_list *list);
t_list		*ft_list_copy(t_list *lst_head, t_list *lst_last_el);
char		*ft_strjoin(char *s1, char simb);
size_t		ft_strlen(char *str);
char		*ft_strdup(char *s1);
char		*ft_substr(char *s, unsigned int start, size_t len);
int			ft_is_space(char simbol);
int			ft_find_env(char *str_dollar, t_list *env, char **str);
int			ft_parser_str(char *str, t_list	**list_env,
				t_list	**list_str, int status);
int			ft_parser_env(char **env, t_list **list_env);
int			ft_strcmp(char *s1, char *s2);
int			ft_cd(t_list *path, t_list **list_env);
int			ft_pwd(void);
void		ft_exit(t_list	*list_env, int status);
int			ft_exit_command(t_list	*list_args, int status);
void		ft_env(t_list *list_env);
void		ft_unset(t_list *list_args, t_list	**list_env);
int			ft_pars_for_export(t_list *for_export, t_list **list_env);
int			ft_export(t_list **list_env, t_list *to_add);
void		ft_sort_list(t_list *list_env_dup);
int			ft_duplicate_list(t_list *list_env);
char		*ft_itoa(int n);
void		ft_echo(t_list *list_args);
int			ft_export_one_variable(t_list **list_env, char *name, char *value);
char		*ft_get_env_value(t_list *list_env, char *name);
char		*ft_join_for_strs(char *s1, char *s2);
int			ft_str_error(char *command, char *arg);
int			ft_atoi(char *str);
int			ft_isdigit(int c);
int			ft_pipex(t_list *list_str, t_list **list_env, t_params *params);
int			ft_count_pipes(t_list *list_str);
int			ft_is_pipex_valid(t_list *list_head, t_list *list_last);
void		ft_error_pipex_not_valid(t_params *params);
int			ft_fork_pipes(int **pipe, t_list **list_pipes, t_list **list_env,
				t_params *params);
int			ft_err_pipex(int i, t_list **list, int status);
void		ft_free_pipex(t_list **list, int count_pipes);
void		ft_free_pipes(int **pipe, int count_pipes);
void		ft_close_pipes(int **pipe, int count_pipes);
int			ft_start_vars(int *i, t_list *list_str);
int			ft_parser_pipex(t_list *list_str, t_list **list);
int			ft_execute_command(t_list *list_commands,
				t_list **list_env, t_params *params);
int			ft_another_commands(t_list *list_commands,
				t_list **list_env, t_params *params);
char		*ft_if_arr_null(char **array, int i);
char		**ft_to_array_command(t_list *list);
char		*ft_if_str_null(char *str_tmp, char **array, int i);
char		**ft_to_array_env(t_list *list);
char		*ft_path(char *cmd, t_list *list_env);
char		*ft_strjoin_path(char *s1, char *s2);
int			ft_strchr(char *s, char c);
int			ft_execute_command(t_list *list_commands,
				t_list **list_env, t_params *params);
int			ft_free_str_list(char *str, char *str_s,
				t_list *list, int status);
int			ft_redirect(t_list *list_commands,
				t_params *params, t_list **list_env);
int			ft_check_redir(t_list *list_commands, t_params *params);
int			ft_here_doc(t_list *list_commands, t_params *params);
void		ft_signal_ctrl_c(int signal);
void		ft_signal_quit(int signal);
void		ft_delete_tmp_files(t_params *params);
int			ft_count_redirects(t_list *list_commands);
int			ft_redir_is_valid(t_list *list_commands, t_params *params);
int			ft_check_fd_second(t_redirect *redir, t_list *list_commands,
				t_params *params, int i);
int			ft_check_fd(t_redirect *redir, t_list *list_commands,
				t_params *params, int i);
void		ft_close_fd(t_redirect *redir);
int			ft_open_files(t_redirect *redir, t_list *list_commands,
				t_list **list_redirects, t_params *params);
int			ft_fill_list_redir(t_list *list, t_list **list_redirects);
int			ft_is_space(char simbol);
int			ft_find_env(char *str_dollar, t_list *env, char **str);
int			ft_write_here_doc(char *str, t_params *params);
int			ft_check_redir(t_list *list_commands, t_params *params);
int			ft_count_here_doc(t_list *list_commands);
int			ft_here_doc_is_valid(t_list *list_commands, t_params *params);
int			ft_if_error_here_doc(t_params *params, int i, int status);
int			ft_free_here_doc(t_params *params, int i);
int			ft_replace_here_doc(t_params *params,
				int *i, t_list **list_commands);
int			ft_child_here_doc(t_params *params, int *i, t_list *list_commands);
int			ft_start_values_here_doc(t_params *params, t_list *list_commands);
int			ft_open_here_doc(int *i, t_params *params, t_list *list_commands);
int			ft_dollar(char **str, t_list **list_env,
				char **str_tmp, int status);
int			ft_another_simbols(char **str_tmp, t_list **list_str,
				int single_quote, int double_quote);
int			ft_argument(char **str, char **str_tmp, t_list **list_env);
int			ft_if_question(char **str, char **str_tmp, int status);
int			ft_space(char **str_tmp, t_list **list_str);
void		ft_first_pipe_inside(t_params *params, int *id_process, int **pipe);
int			ft_first_pipe(int *id_process, t_params *params, int **pipe);
int			ft_middle_pipes_inside(t_params *params,
				int *id_process, int **pipe, int i);
int			ft_middle_pipes(int *id_process, t_params *params,
				int **pipe, t_list ***list_pipes);
void		ft_write_err_another_com(t_params *params, t_list *list_commands);
void		ft_check_arr_to_null(char **arr);

#endif
