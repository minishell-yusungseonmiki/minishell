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
#include <termios.h>
#include <sys/stat.h>
#include <dirent.h>

# define READ 0
# define WRITE 1

typedef enum {
	ARG,
	PIPE,
	HEREDOC,	// <<
	APPEND,		// >>
	IN,			// <
	OUT			// >
}	e_type;

typedef struct s_token {
	char	*elem;
	e_type	type;
	int		before_blank;
}	t_token;

typedef struct s_env {
	char	*key;
	char	*value;
}	t_env;

typedef struct s_node {
	char	*elem;
	e_type	type;
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

typedef enum {
	START,
	SYNTAX,
	MAX_HEREDOC,
	INVALID_EXPORT,
	OPEN_FAILED
}	e_error;

int	g_exit_status;

// builtin_cd.c
void    execute_cd(t_proc_info *proc);
char	*find_value(t_list *denv, char *find);
void	set_value(t_list **denv, char *key, char *new_value);

// builtin_echo.c
void    execute_echo(t_proc_info *proc, t_list *sub_lst);

// builtin_env.c
void    execute_env(char **cmd_argv, t_list **denv);

//builtin_exit.c
void	execute_exit(t_proc_info *proc, int only_builtin);

// builtin_export.c
void    execute_export(char **cmd_argv, t_list **denv, t_proc_info *proc);
void    print_export(t_list **denv, t_proc_info *proc);
int		cmd_is_empty(char **cmd_argv);

// builtin_pwd.c
void    execute_pwd(t_proc_info *proc);

// builtin_unset.c
void    execute_unset(char **cmd_argv, t_list **denv);

// builtin.c
int		is_builtin(char **cmd_argv);
void    execute_builtin(t_proc_info *proc, t_list *sub_lst, int only_builtin);

// change_value.c
char	*find_env(char *str, t_list *env, int *i);
char	*not_env(char *str, int *i);
char	*change_value(char *str, t_list *env);

// env.c
t_env	*make_keyvalue(char *env);
t_list	*envp_to_lst(char **envp);
char	*keyvalue_to_str(t_env *node, int export);
char	**lst_to_envp(t_list *env_lst, int export);
void	print_env(void *token);
void	print_envp(char **envp, int out_fd);

// erase_quotes.c
char	*single_quote(char *elem, int *i);
char	*double_quote(char *elem, int *i, t_list *env);
char	*not_quote(char *elem, int *i, t_list *env);
void	erase_quotes(t_list *lst, t_list *env);

// error.c
int		error(e_error err);

// execute.c
void	execute(t_list *proc_lst);
void	execute_child(t_proc_info *proc_info);
int	execute_only_builtin(t_list *proc_lst);
void	wait_process(t_list *proc_lst);

// free.c
void	free_env(void *env);
void	free_proc_info(void *proc);
void	free_node_list(void	*node);
void	free_token(void *token);
void	free_double_str(char **envp);

// get_next_line.c
char	*get_next_line(int fd);

// heredoc.c
void	heredoc(t_list *proc_lst);

// main.c
void    run_minishell(char *line, t_list **denv);

// make_proc_list.c
t_list		*make_proc_list(t_list *token_lst, t_list **denv);
t_proc_info	*init_proc_info(t_list **denv, t_list *node_lst);

// open_fd.c
int	find_in_fd(t_list *lst, char *h_filename);
int	find_out_fd(t_list *lst);

// pre_check.c
int    quote_check(char *s);
int    syntax_check(t_list *lst);

// print.c
void	print_token(void *token);
void	print_proc_info(void *proc_info);

// make_proc_info.c
t_list	*make_node_list(t_list *start, t_list *end);
void	check_redirection(t_list *lst);
char	**find_cmd_argv(t_list *lst);
char	*find_cmd_path(char **cmd_argv, char **path_list);
char	**parse_envp(t_list *denv);

// signal.c
void	sigint_handler(int signum);
void	sigint_heredoc(int signum);
void	sigint_child(int signum);
void	print_off_signal(void);
void	print_on_signal(void);

// tokenize.c
t_list	*tokenize(char *s);

// util.c
int		is_same(char *a, char *b);
void	free_double_str(char **envp);
int		ft_isspace(char c);
void	pipe_open(int fd[2]);
pid_t	make_fork(void);
int		line_check(char *line, t_list **token_lst);

#endif
