#include "../include/minishell.h"

void    execute_unset(char **cmd_argv, t_list **denv)
{
	int		i;
	char	*key;
	t_list	*iter;
	t_list	*before;

	i = 1;
	before = NULL;
	while (cmd_argv[i])
	{
		if (ft_isdigit(cmd_argv[i][0]) || ft_strchr(cmd_argv[i], '='))
		{
			write(2, "export: not a valid identifier\n", 31);
			exit_status = 1;
		}
		else
		{
			iter = *denv;
			key = cmd_argv[i];
			while (iter)
			{
				if (!ft_strncmp(((t_env *)(iter->content))->key, key, ft_strlen(key))
				&& ft_strlen(((t_env *)(iter->content))->key) == ft_strlen(key))
				{
					if (before)
						before->next = iter->next;
					else
						*denv = iter->next;
					free(((t_env *)(iter->content))->key);
					free(((t_env *)(iter->content))->value);
					break ;
					
				}
				before = iter;
				iter = iter->next;
			}
		}
		i++;
	}
}
