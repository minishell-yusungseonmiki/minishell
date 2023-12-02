#include "../include/minishell.h"

static t_env	*make_envnode(char *key, char *value)
{
	t_env	*node;

	node = (t_env *)malloc(sizeof(t_env));
	node->key = key;
	node->value = value;
	return (node);
}

static void	renew_denv(t_list **denv, char *key, char *value, int flag)
{
	t_list	*iter;
	char	*tmp;

	iter = *denv;
	// printf("key: %s, value: %s\n", key, value);
	while (iter)
	{
		if (!ft_strncmp(((t_env *)(iter->content))->key, key, ft_strlen(key))
		&& ft_strlen(((t_env *)(iter->content))->key) == ft_strlen(key))
		{
			if (flag != 0)
			{
				tmp = ((t_env *)(iter->content))->value;
				((t_env *)(iter->content))->value = value;
				free(tmp);
			}
			else
				free(value);
			free(key);
			return ;
		}
		iter = iter->next;
	}
	ft_lstadd_back(denv, ft_lstnew(make_envnode(key, value)));
}

char	*key_check(char *cmd_argv, int equal)
{
	char	*key;
	int		j;

	if (equal < 0)
		key = cmd_argv;
	else
		key = ft_substr(cmd_argv, 0, equal);
	j = 0;
	while (key[j])
	{
		if (!ft_isalnum(key[j]) && key[j] != '_')
		{
			error(INVALID_EXPORT);
			return (NULL);
		}
		j++;
	}
	return (key);
}

void	run_export(char *cmd_argv, t_list **denv)
{
	char	*key;
	int		equal;
	int		size;

	equal = ft_strchr(cmd_argv, '=') - cmd_argv;
	if (equal == 0)
	{
		error(INVALID_EXPORT);
		return ;
	}
	key = key_check(cmd_argv, equal);
	if (!key)
		return ;
	if (equal < 0)
		renew_denv(denv, key, ft_strdup(""), 0);
	else
	{
		size = ft_strlen(cmd_argv) - equal - 1;
		renew_denv(denv, key, ft_substr(cmd_argv, equal + 1, size), 1);
	}
}

void	execute_export(char **cmd_argv, t_list **denv, t_proc_info *proc)
{
	int	i;

	if (cmd_is_empty(cmd_argv))
		print_export(denv, proc);
	else
	{
		i = 1;
		while (cmd_argv[i])
		{
			if (ft_isdigit(cmd_argv[i][0]))
				error(INVALID_EXPORT);
			else
				run_export(cmd_argv[i], denv);
			i++;
		}
	}
	printf("export: %p\n", *denv);
}
