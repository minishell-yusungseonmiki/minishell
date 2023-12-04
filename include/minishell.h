/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusung <yusung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 16:11:19 by yusung            #+#    #+#             */
/*   Updated: 2023/12/04 17:11:14 by yusung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include "../libft/include/libft.h"
# include <signal.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <termios.h>

# define READ 0
# define WRITE 1

typedef enum type {
	ARG,
	PIPE,
	HEREDOC,
	APPEND,
	IN,
	OUT
}	t_type;

typedef struct s_token {
	char	*elem;
	t_type	type;
	int		before_blank;
}	t_token;

typedef struct s_env {
	char	*key;
	char	*value;
}	t_env;

typedef struct s_node {
	char	*elem;
	t_type	type;
	int		visited;
	int		before_blank;
}	t_node;

typedef struct s_proc_info {
	t_list	*denv;
	char	*h_filename;
	char	**cmd_argv;
	char	*cmd_path;
	t_list	*node_lst;
	int		in_fd;
	int		out_fd;
	pid_t	child_pid;
	int		prev;
}	t_proc_info;

typedef enum error{
	START,
	SYNTAX,
	MAX_HEREDOC,
	INVALID_EXPORT,
	FILE_ERROR,
	NOT_CMD,
	NOT_FILE
}	t_error;

int	g_exit_status;

// builtin_cd.c
void		execute_cd(t_proc_info *proc);

// builtin_echo.c
void		execute_echo(t_proc_info *proc, t_list *sub_lst);

// builtin_env.c
void		execute_env(char **cmd_argv, t_list **denv);

//builtin_exit.c
void		execute_exit(t_proc_info *proc, int only_builtin);

// builtin_export.c
void		execute_export(char **cmd_argv, t_list **denv, t_proc_info *proc);
void		print_export(t_list **denv, t_proc_info *proc);
int			cmd_is_empty(char **cmd_argv);

// builtin_pwd.c
void		execute_pwd(t_proc_info *proc);

// builtin_unset.c
void		execute_unset(char **cmd_argv, t_list **denv);

// builtin.c
int			is_builtin(char **cmd_argv);
void		execute_builtin(t_proc_info *proc, t_list *sub_lst, int only_built);

// execute_process.c
void		process_child(t_list *iter, int fd[2], int prev_fd, t_list *p_lst);
void		process_parent(t_proc_info *p_info, int fd[2], int *p_fd, int pid);
void		wait_process(t_list *proc_lst);

// execute.c
void		execute_child(t_proc_info *proc_info);
void		execute(t_list *proc_lst);

// change_value.c
char		*change_value(char *str, t_list *env);

// erase_quotes.c
void		erase_quotes(t_list *lst, t_list *env);

// pre_check.c
int			quote_check(char *s);
int			syntax_check(t_list *lst);

//tokenize_util.c
int			meet_special(char c);
int			in_quote(char c, char *q, int *i);
void		set_index(int type, int *i, int *start);

// tokenize.c
t_list		*tokenize(char *s);

// env.c
t_list		*envp_to_lst(char **envp);
char		**lst_to_envp(t_list *env_lst, int export);

// heredoc.c
void		heredoc(t_list *proc_lst);

// make_proc_info.c
t_list		*make_node_list(t_list *start, t_list *end);
char		**find_cmd_argv(t_list *lst);
char		*find_cmd_path(char **cmd_argv, char **path_list);
char		**parse_envp(t_list *denv);

// make_proc_list.c
t_list		*make_proc_list(t_list *tk_lst, t_list **denv);

// make_proc_util.c
void		check_redirection(t_list *lst);
int			get_arg_cnt(t_list *lst);
char		*free_and_return(char **pathlist, char *result);

// open_fd.c
int			find_in_fd(t_list *lst, char *h_filename);
int			find_out_fd(t_list *lst);

// signal
void		sigint_handler(int signum);
void		sigint_heredoc(int signum);
void		sigint_child(int signum);
void		sigquit_child(int signum);
void		sigint_last_child(int signum);
void		sigquit_last_child(int signum);
void		print_off_signal(void);
void		print_on_signal(void);

// error.c
int			error(t_error err, char *str);

// free.c
void		free_env(void *env);
void		free_proc_info(void *proc);
void		free_node_list(void	*node);
void		free_token(void *token);
void		free_double_str(char **envp);

// get_next_line.c
char		*get_next_line(int fd);

// util.c
int			is_same(char *a, char *b);
void		pipe_open(int fd[2]);
pid_t		make_fork(void);
int			line_check(char *line, t_list **token_lst);
int			ft_isspace(char c);

// main.c
void		run_minishell(char *line, t_list **denv);

#endif
