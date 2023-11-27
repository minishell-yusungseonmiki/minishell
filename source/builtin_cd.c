#include "../include/minishell.h"

void    execute_cd(t_proc_info *proc)
{
	// printf("my cd\n");
	if (proc->cmd_argv[1])
	{
		if (chdir(proc->cmd_argv[1]) < 0)
		{
			perror(NULL);
			exit(1);
		}
	}
}
