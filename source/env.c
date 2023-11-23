#include "../include/minishell.h"

t_env	*make_keyvalue(char *env)
{
	t_env	*node;
	int		equal;

	node = (t_env *)malloc(sizeof(t_env));
	equal = ft_strchr(env, '=') - env;
	node->key = ft_substr(env, 0, equal);
	node->value = ft_substr(env, equal + 1, ft_strlen(env) - equal - 1);
	return (node);
}

t_list	*envp_to_lst(char **envp)
{
	t_list	*env_lst;
	int		i;

	if (!envp)
		return (NULL);
	env_lst = NULL;
	i = 0;
	while (envp[i])
	{
		ft_lstadd_back(&env_lst, ft_lstnew(make_keyvalue(envp[i])));
		i++;
	}
	return (env_lst);
}

char	**lst_to_envp(t_list *env_lst)
{
	char	**envp;
	t_list	*iter;
	int		cnt;
	int		i;

	cnt = 0;
	iter = env_lst;
	while (iter)
	{
		cnt++;
		iter = iter->next;
	}
	if (cnt == 0)
		return (NULL);
	envp = (char **)malloc(sizeof(char*) * (cnt + 1));
	i = 0;
	while (env_lst)
	{
		envp[i] = ft_strdup(((char *)(env_lst->content)));
		env_lst = env_lst->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}
void	print_env_lst(void *env)
{
	printf("%s\n", (char *)env);
}

void	print_envp(char **envp)
{
	int	i = 0;
	while (envp && envp[i])
	{
		printf("%s\n", envp[i++]);
	}
}