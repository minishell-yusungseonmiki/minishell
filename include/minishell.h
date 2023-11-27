#ifndef MINISHELL_H
# define MINISHELL_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# if BUFFER_SIZE < 1
#  error BUFFER_SIZE is too small
# endif

# include "../libft/include/libft.h"
# include <signal.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

# define READ 0
# define WRITE 1

typedef enum {
	ARG,
	PIPE,
	IN,			// <
	OUT,		// >
	HEREDOC,	// <<
	APPEND		// >>
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
	int		prev;
	int		in_fd;
	int		out_fd;
	char	**cmd_argv;
	char	*cmd_path;
	char	**envp;
	char	*h_filename;
	t_list	*denv;
	int		blank;
	pid_t	child_pid;
}	t_proc_info;

typedef enum {
	SYNTAX,
	MAX_HEREDOC
}	e_error;

int	exit_status;

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
void    execute_export(char **cmd_argv, t_list *denv, t_proc_info *proc);

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
void	free_envp(char **envp);

// erase_quotes.c
char	*single_quote(char *elem, int *i);
char	*double_quote(char *elem, int *i, t_list *env);
char	*not_quote(char *elem, int *i, t_list *env);
void	erase_quotes(t_list *lst, t_list *env);

// error.c
int		error(e_error err);

// find_pipe_and_execute.c
void	find_pipe_and_execute(t_list *token_lst, t_list *denv, t_list *hfile_lst);
t_proc_info	*execute_pipe(t_list *sub_lst, t_proc_info *proc_info, t_proc_info *before, int last);
void	wait_process(int child_cnt, pid_t child_pid);

// get_next_line.c
char	*get_next_line(int fd);

// heredoc.c
t_list	*heredoc(t_list *lst);

// main.c
void	sigint_handler(int signum);

// pre_check.c
int    quote_check(char *s);
int    syntax_check(t_list *lst);

// set_proc_info.c
void	print_proc_info(t_proc_info *pi);
t_proc_info	*set_proc_info(t_list *sub_lst, t_list *denv, t_list *hfile_lst);
t_list	*separate_list_by_pipe(t_list *start, t_list *end);
void	check_redirection(t_list *lst);
int		find_in_fd(t_list *lst, char *h_filename);
int		find_out_fd(t_list *lst);
char	**find_cmd_argv(t_list *lst);
char	*find_cmd_path(char **cmd_argv, char **path_list);
char	**parse_envp(t_list *denv);

// tokenize.c
void	print_elem(void *token);
t_token	*make_token(char *elem, e_type type, int blank);
int		end_of_token(char *s);
int		check_special(t_list **lst, char *s, int *start, int *i);
t_list	*tokenize(char *s);

#endif
