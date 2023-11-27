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

char	*keyvalue_to_str(t_env *node, int export)
{
	char	*str;
	char	*tmp;

	str = ft_strdup(node->key);
	if (export && node->value[0] != '\0')
	{
		tmp = ft_strjoin(str, "=\"");
		free(str);
		str = ft_strjoin(tmp, node->value);
		free(tmp);
		tmp = ft_strjoin(str, "\"");
		free(str);
			return (tmp);
	}
	tmp = ft_strjoin(str, "=");
	free(str);
	if (export && node->value[0] == '\0')
		return (tmp);
	str = ft_strjoin(tmp, node->value);
	free(tmp);
	return (str);
}

char	**lst_to_envp(t_list *env_lst, int export)
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
		envp[i] = keyvalue_to_str(((t_env *)(env_lst->content)), export);
		env_lst = env_lst->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}

void	free_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

void	print_envp(char **envp, int out_fd)
{
	int	i;
	
	i = 0;
	while (envp && envp[i])
	{
		ft_putstr_fd("declare -x ", out_fd);
		ft_putstr_fd(envp[i], out_fd);
		ft_putstr_fd("\n", out_fd);
		i++;
	}
}

// void	print_envp(char **envp)
// {
// 	int	i = 0;
// 	while (envp && envp[i])
// 	{
// 		printf("%s\n", envp[i++]);
// 	}
// }

// void	print_env(void *token)
// {
// 	printf("declare -x ");
// 	printf("%s", ((t_env *)token)->key);
// 	printf("=");
// 	printf("\"%s\"\n", ((t_env *)token)->value);
// }

void	print_env(void *token)
{
	if (((t_env *)token)->value[0] == '\0')
		return ;
	printf("%s=%s\n", ((t_env *)token)->key, ((t_env *)token)->value);
}
