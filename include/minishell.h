#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/include/libft.h"
# include <signal.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>

typedef enum {
	ARG,
	PIPE,
	IN,			// <
	OUT,		// >
	HEREDOC,	// <<
	APPEND		// >>
}	e_type;

typedef struct s_struct {
	char	*elem;
	e_type	type;
}	t_token;

t_list *tokenize(char *s);


#endif
