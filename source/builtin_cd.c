#include "../include/minishell.h"

char	*find_value(t_list *denv, char *find)
{
	while (denv)
	{
		if (!ft_strncmp(((t_env *)(denv->content))->key, find, ft_strlen(find))
		&& ft_strlen(((t_env *)(denv->content))->key) == ft_strlen(find))
			return (((t_env *)(denv->content))->value);
		denv = denv->next;
	}
	return (NULL);
}

void	set_value(t_list **denv, char *key, char *new_value)
{
	t_list	*iter;

	iter = *denv;
	while (iter)
	{
		if (!ft_strncmp(((t_env *)(iter->content))->key, key, ft_strlen(key))
		&& ft_strlen(((t_env *)(iter->content))->key) == ft_strlen(key))
		{
			free(((t_env *)(iter->content))->value);
			((t_env *)(iter->content))->value = ft_strdup(new_value);
		}
		iter = iter->next;
	}
}

void    execute_cd(t_proc_info *proc)
{
	char	*old_pwd;
	char	*now_pwd;

	old_pwd = find_value(proc->denv, "PWD");
	if (proc->cmd_argv[1])
	{
		if (chdir(proc->cmd_argv[1]) < 0)
		{
			perror(NULL);
			return ;
		}
	}
	set_value(&proc->denv, "OLDPWD", old_pwd);
	now_pwd = getcwd(NULL, 0);
	set_value(&proc->denv, "PWD", now_pwd);
}
