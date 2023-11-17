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
	int		in_fd;
	int		out_fd;
	char	**cmd_argv;
	char	*cmd_path;
}	t_proc_info;

t_list *tokenize(char *s);
void	print_elem(void *token);

char	*heredoc(t_list *lst);
char	*get_next_line(int fd);


void	print_proc_info(void *proc_info);
void	set_process_info(t_list *token_lst);
void	init_proc_info(t_proc_info *proc_info);
t_list	*make_node_list(t_list *token_lst);
t_list	*make_process_info_list(t_list *lst);
void	find_in_out(t_list *lst, t_proc_info *proc_info);
void	find_cmd_argv(t_list *lst, t_proc_info *proc_info);


#endif
