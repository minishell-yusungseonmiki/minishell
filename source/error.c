#include "../include/minishell.h"

int	error(e_error err)
{
	if (err == SYNTAX)
		perror("syntax error");
	if (err == MAX_HEREDOC)
	{
		perror("maximum here-document count exceeded");
		exit(1);
	}
	return (1);
}
