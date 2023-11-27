#include "../include/minishell.h"

void    execute_pwd(t_proc_info *proc)
{
	// printf("my pwd\n");
	char	*result;
	char	*tmp;

	result = getcwd(NULL, 0);
	tmp = ft_strjoin(result, "\n");
	result = tmp;
	ft_putstr_fd(result, proc->out_fd);
	free(result);
}
