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
}	t_token;

typedef struct s_node {
	char	*elem;
	e_type	type;
	int		visited;
}	t_node;

typedef struct s_proc_info {
	int		prev;
	int		in_fd;
	int		out_fd;
	char	**cmd_argv;
	char	*cmd_path;
	char	**envp;
}	t_proc_info;

t_list 		*tokenize(char *s);
void		print_elem(void *token);

char		*heredoc(t_list *lst);
char		*get_next_line(int fd);

void		print_proc_info(void *proc_info);
t_list		*find_pipe(t_list *token_lst, char **envp);
t_list		*separate_list_by_pipe(t_list *start, t_list *end);
t_proc_info	*set_proc_info(t_list *sub_lst, char **envp);
int			find_in_fd(t_list *lst);
int			find_out_fd(t_list *lst);
char		**find_cmd_argv(t_list *lst);
char		*find_cmd_path(char *cmd, char **path_list);
char		**parse_envp(char **envp);

void    	erase_quotes(t_list *lst);
void    	exeute_pipe(t_list *proc_lst);
#endif
