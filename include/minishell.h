/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:58:33 by aselnet           #+#    #+#             */
/*   Updated: 2023/07/18 17:22:16 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <signal.h>
# include <sys/stat.h>

/////////////////////////// ENVIRONMENT //////////////////////////////////
typedef struct s_data_env
{
	int		size;
	char	**envp;
	int		stdin;
	int		stdout;
	char	*pwd;
	int		oldpwd_done;
}	t_data_env;

/////////////////////////////// PARSING //////////////////////////////////
//////////////////////////////////////////////////////////////////////////
typedef struct s_token //liste doublement chainée contenant deux variables
{
	char			*content;
	struct s_token	*prev;
	struct s_token	*next;
	char			type;
	char			delim_quote;
	char			join_prev;
	char			join_next;
	char			quote;
}	t_token;

typedef struct s_lexing
{
	t_token	*tklist_head;
	char	*input;
	int		tklist_size;
}	t_lexing;

// define.c
int				define_redirs(t_lexing *ltable);
int				define_delims(t_lexing *ltable);
int				define_files(t_lexing *ltable);

// define2.c
void			define_args(t_lexing *ltable);
int				merge_flags(t_lexing *ltable);
void			check_access(t_token *token, t_data_env *data_env);
int				define_cmds(t_lexing *ltable, t_data_env *data_env);

// define3.c
int				check_builtins(t_token *token);
int				check_path(char **envp);
char			*find_cmd_path(char	*cmd_name, char **envp);

// expand.c
char			*clean_up_quotes(
					char *oldcontent, t_lexing *ltable, t_data_env *data_env);
int				format_tokens(t_lexing *ltable, t_data_env *data_env);
int				expand_token_list(t_lexing *ltable, t_data_env *data_env);

//expand2.c
char			*replace_with_error_code(char *content, char **cursor);
char			*delete_name(char *content, char **cursor, int name_len);
char			*get_new_content(
					char *content, char **cursor, int name_len, char **env);
char			*expand_variable(char *content, t_data_env *data_env);
char			*expand_process(char *content, t_data_env *data_env);

//expand3.c
char			*extract_variable_value(char **env);
int				fetch_value_len(char **env);
void			update_content(
					char *new_content, char *content,
					char *variable, char **cursor);
void			update_with_error(
					char *new_content, char *content,
					char *error_code, char **cursor);
char			*replace_with_value(
					char *content, char **cursor,
					int name_len, char **env);

//expand4.c
void			copy_content_end(
					char *new_content, char *content, int i, int j);
char			*delete_num(char *content, char **cursor);

// lexing.c
int				create_redir_token(
					t_lexing *ltable, t_data_env *data_env, int *reader);
int				find_quote_len(t_lexing *ltable, int reader, char quote_char);
int				create_quoted_token(
					t_lexing *ltable, t_data_env *data_env, int *reader);
int				create_regular_token(
					t_lexing *ltable, t_data_env *data_env, int *reader);
int				create_token_list(t_lexing *ltable, t_data_env *data_env);

// lexing2.c
void			define_joins(
					t_lexing *ltable, t_token *quoted,
					int reader, int quote_len);
int				format_expands(t_lexing *ltable, t_data_env *data_env);

// parsing.c
char			last_char(char *str);
int				parse_token_list(t_lexing *ltable, t_data_env *data_env);
int				parse_redirections(t_lexing *ltable, t_data_env *data_env);
int				join_quotes(t_lexing *ltable, t_data_env *data_env);
int				no_alnum(char *content);

// parsing2.c
char			*replace_dollars(char *content);

// quit.c
int				free_array(char **arr);
void			set_error(int error_code);
int				free_structs(t_lexing *ltable,
					t_data_env *data_env, char *error_msg, char mode);

// tokens.c
t_token			*tk_new(char *content);
int				tk_size(t_token *token);
t_token			*tk_last(t_token *token);
void			tk_delone(t_token *token);
void			tk_clear(t_token **head);

// tokens2.c

void			tk_add_back(t_token **head, t_token *new);
void			tk_addto(t_token **head, t_token *new, int pos);
void			tk_moveto(t_token **head, t_token *token, int pos);
t_token			*tk_delone_and_link(t_token **head, t_token *token);

//tokens3.c
t_token			*tk_merge(t_token **head, t_token *token1, t_token *token2);
t_token			*tk_merge_quote(
					t_token **head, t_token *token1, t_token *token2);

/////////////////////////////// EXECUTION ////////////////////////////////
//////////////////////////////////////////////////////////////////////////
typedef struct s_cmd
{
	int		argc;
	char	**argv;
	int		pipe;
	int		pipefd[2];
	int		old_pipefd[2];
	int		final_cmd;
	int		fd_in;
	char	*error_fd;
	char	*filename;
	int		fd_out;
	int		pid;
	char	*cmd_path;
	int		final_pid;
	int		has_cmd;
	char	*first_arg;
	int		first_arg_done;
	int		fd_heredoc;
	int		inside_pipe;
}				t_cmd;

/////////////////////////// MINISHELL STRUCT //////////////////////////////
typedef struct s_minishell
{
	t_data_env	data_env;
	t_cmd		cmd;
	t_lexing	ltable;
	int			inside_heredoc;
}				t_minishell;

/////////////////////////// GLOBAL VARIABLE //////////////////////////////
typedef struct s_minishell_global
{
	int			exit_status;
	int			status_done;
	int			inside_heredoc;
}				t_minishell_g;

extern t_minishell_g	g_mini;

// free_heredoc.c
void			free_heredoc(t_lexing *ltable, t_data_env *data_env,
					char *error_msg);

// ft_all_redir.c
void			ft_all_redir(t_minishell *mini);
void			ft_redir_files(t_minishell *mini);
void			ft_error_redirections(t_minishell *mini);

// ft_close.c
void			ft_close(int *fd);
void			ft_close_all_fds(t_minishell *mini);

// ft_error_exec.c
void			ft_error_no_such_file(char *file);
void			ft_error_cmd_not_found(t_minishell *mini);
void			ft_filename_required(t_minishell *mini);
void			ft_error_cmd_not_found2(t_minishell *mini);
void			ft_error(int status, t_minishell *mini);

// ft_execute_bis.c
void			ft_before_launch_pipeline(t_minishell *mini);
int				ft_init_pipe_before(t_cmd *cmd);
void			ft_restore_before_next_prompt(t_minishell *mini);

// ft_execute.c
void			ft_execute(t_minishell_g *g_mini, t_minishell *mini);
void			ft_execute_cmd(t_minishell *mini, int builtin_done);
void			ft_prepare_before_next_cmd(
					t_minishell *mini, int *pipe_before, int *builtin_done);
void			ft_waitpid(t_minishell *mini);
int				ft_exe_builtin1(t_minishell *mini);

// ft_exit_exec.c
void			ft_exit_exec(int status, t_minishell *mini);

// ft_fill_cmd_type_r.c
void			ft_fill_cmd_for_type_r(t_minishell *mini, t_token *lst);
void			ft_fill_cmd_for_type_r2(t_cmd *cmd, t_token *lst);
int				ft_ambiguous_redir(t_cmd *cmd, t_token *lst);
void			ft_fill_cmd_for_type_r3(t_cmd *cmd, t_token *lst);

// ft_fill_cmd.c
void			ft_fill_cmd(t_minishell *minishell, t_token *lst);
void			ft_fill_argc_argv(t_minishell *mini, t_token *lst);
void			ft_split_cmd_option(t_minishell *mini, t_token *lst);
void			ft_malloc_argv(t_minishell *mini, t_token *lst);

// ft_fork.c
void			ft_fork(t_minishell *mini);
void			ft_get_cmd_path(t_minishell *mini);
void			ft_exec_not_builtin(t_minishell *mini);
void			ft_after_fork_parent(t_cmd *cmd);
void			ft_exe_builtin2(t_minishell *mini);

// ft_free_all_exec.c
void			ft_free_all_exec(t_minishell *mini);

// ft_free_cmd.c
void			ft_free_cmd(t_cmd *cmd);

// ft_get_cmd.c
t_token			*ft_get_cmd(
					t_token *tklist_head, t_minishell *mini, int pipe_before);

// ft_get_status.c
void			ft_get_status(int status);
void			ft_print_all_error_sig(int sig_status);
void			ft_print_stder(char *str);
void			ft_print_error_sig1(int sig_status);
void			ft_print_error_sig2(int sig_status);

// ft_init_cmd.c
void			ft_init_cmd(t_cmd *cmd);

// heredoc.c
void			fetch_heredoc(t_cmd *cmd, t_token *tklist_head,
					t_data_env *data_env, t_minishell *mini);

// heredo2c.c
char			*gnl(void);
t_token			*fetch_delim(t_token **cursor);
int				delim_len(char *delim, char *line);

/////////////////////////////// BUILTINS /////////////////////////////////
//////////////////////////////////////////////////////////////////////////

// ft_builtins_utils.c 
void			ft_error_identifier(char *builtin, char *identifier);
size_t			ft_strlen(const char *s);
char			*ft_strdup(const char *s);

// ft_builtins_utils_2.c
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_srch(char const c, char const *str);
int				ft_check_empty_var(char **argv, int *j, char *str);

// ft_cd.c
int				ft_cd_without_arg(t_minishell *mini);
void			ft_cd_too_many_args(t_minishell *mini);
int				ft_go_to_dir(t_minishell *mini);
void			ft_change_all_pwd(char *pwd, t_minishell *mini);
void			ft_cd(t_minishell *mini);

// ft_cd_utils.c
void			ft_update_oldpwd_utils(t_minishell *mini, char *oldpwd);
int				ft_update_oldpwd(t_minishell *mini);
void			ft_update_pwd(char *pwd, t_data_env *s_data_env);
char			*ft_get_pwd(t_minishell *mini);
void			ft_change_g_pwd(char *pwd, t_minishell *mini);

// ft_echo.c
int				ft_check_option(char *str);
int				ft_compute_start_arg(int has_option);
void			ft_echo(t_minishell *mini);

// ft_env.c
void			ft_env(t_minishell *mini);

// ft_environment_utils_2.c 
int				ft_strcmp_env(const char *s1, const char *s2);
int				ft_compute_env_len(char **envp);
int				ft_check_has_oldpwd(char **envp);
char			**ft_strdup_env_2(
					char **envp, char **env, int size, int take_oldpwd);
char			**ft_strdup_env(
					char **envp, int take_oldpwd, t_minishell *mini);

// ft_environment_utils.c
int				ft_remove_var_in_env(int i, t_data_env *s_data_env);
char			**ft_add_var_env(t_data_env *s_data_env, char *new_var);
void			ft_free_env(char **env, int size);

// ft_export_utils.c
int				ft_check_identifier(char **argv, int *j, int i);
void			ft_print_export(char *str);
void			ft_get_env_min(char **min, int *pos_min, int size, char **env);
int				ft_print_env_min(char **env, int size);
int				ft_check_is_first_digit(char **argv, int *j, char *cmd);

// ft_export.c
int				ft_check_var_format_export(char **argv, int *j);
int				ft_last_check_format_export(char **argv, int *j);
void			ft_export_without_arg(t_minishell *mini);
void			ft_export_with_arguments(t_minishell *mini, int j);
void			ft_export(t_minishell *mini);

// ft_pwd.c
char			*ft_get_pwd_env(char **envp);
void			ft_print_pwd(char *pwd, t_minishell *mini);
void			ft_pwd(t_minishell *mini);

// ft_unset.c
int				ft_check_var_format_unset(char **argv, int *j);
int				ft_unset_with_arg(char **argv, t_data_env *s_data_env, int j);
void			ft_unset(t_minishell *mini);

// ft_exit_utils.c
void			ft_exit_utils(
					int status, int no_exit_written, t_minishell *mini);
int				ft_check_all_digits(char *str);
void			ft_error_numeric(char *builtin, char *identifier);
int				ft_check_numeric_arg(t_minishell *mini);

// ft_exit.c
unsigned char	ft_atoi_exit(char *str);
void			ft_exit(t_minishell *mini);

/////////////////////////////// SIGNALS //////////////////////////////////
//////////////////////////////////////////////////////////////////////////

// ft_signals.c
void			handler_function(int signum, siginfo_t *siginfo, void *ptr);
void			ft_sigquit(int signum);
void			ft_init_signals(void);

/////////////////////////////// MAIN / INIT //////////////////////////////////
//////////////////////////////////////////////////////////////////////////

// ft_init.c
void			init_table(t_lexing *ltable);
void			ft_init_data_env(
					t_data_env *s_data_env, char **envp, t_minishell *mini);
char			*ft_init_pwd(char **envp);
void			ft_init_mini(
					t_minishell_g *g_mini, t_minishell *mini, char **envp);

// minishell.c
int				define_token_types(
					t_lexing *ltable, t_data_env *data_env, int monitor);
void			process_input(t_minishell_g *g_mini, t_minishell *mini);
void			ft_exit_eof(t_minishell_g *g_mini, t_minishell *mini);
void			minishell(t_minishell_g *g_mini, t_minishell *mini);

#endif