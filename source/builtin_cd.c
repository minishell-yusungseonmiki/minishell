#include "../include/minishell.h"

//void	change_env(t_list **denv)
//{
//	t_list	*iter;
//
//	iter = *denv;
//	while (iter)
//	{
//		if (!ft_strncmp(((t_env *)(iter->content))->key, "PWD", ft_strlen("PWD"))
//		&& ft_strlen(((t_env *)(iter->content))->key) == ft_strlen("PWD"))
//		{
//
//		}
//
//		iter = iter->next;
//	}
//}

void    execute_cd(t_proc_info *proc)
{
	// printf("my cd\n");
	if (proc->cmd_argv[1])
	{
		if (chdir(proc->cmd_argv[1]) < 0)
		{
			perror(NULL);
		}
	}
	//change_env(&proc->denv);
}
