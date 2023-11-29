#include "../include/minishell.h"

void    execute_pwd(t_proc_info *proc)
{
	char	*result;
	char	*tmp;

	result = getcwd(NULL, 0);
	if (!result)
	{
		perror(NULL);
		g_exit_status = 1;
		return ;
	}
	tmp = ft_strjoin(result, "\n");
	result = tmp;
	ft_putstr_fd(result, proc->out_fd);
	free(result);
}
