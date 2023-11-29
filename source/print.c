#include "../include/minishell.h"

void	print_token(void *token)
{
	printf("-----------\n");
	printf("content: %s@\n state: %d\n blank : %d\n", ((t_token *)token)->elem, ((t_token *)token)->type, ((t_token *)token)->before_blank);
	printf("-----------\n");
}
