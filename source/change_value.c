#include "../include/minishell.h"

char	*find_env(char *str, t_list *env, int *i)
{
	int		start;
	int		end;
	char	*key;
	char	*tmp;
	t_list	*lst;

	start = *i + 1;
	if (str[start] == '\0')
	{
		*i += 1;
		return (ft_strdup("$"));
	}
	if (str[start] == '?')
	{
		*i += 2;
		return (ft_itoa(g_exit_status));
	}
	while (str[*i] && str[*i] != ' ' && str[*i] != '\'' && str[*i] != '=' && str[*i] != '\\')
		*i += 1;
	end = *i;
	key = ft_substr(str, start, end - start);
	// printf("key: %s\n", key);
	lst = env;
	while (lst)
	{
		if (!ft_strncmp(((t_env *)(lst->content))->key, key, ft_strlen(key))
		&& ft_strlen(((t_env *)(lst->content))->key) == ft_strlen(key))
		{
			tmp = ((t_env *)(lst->content))->value;
			// printf("key: %s, value: %s\n", key, tmp);
			free(key);
			return (tmp);
		}
		lst = lst->next;
	}
	return (NULL);
}

char	*not_env(char *str, int *i)
{
	int	start;
	int	end;

	start = *i;
	while (str[*i] && str[*i] != '$')
		*i += 1;
	end = *i;
	return (ft_substr(str, start, end - start));
}

char	*change_value(char *str, t_list *env)
{
	char	*tmp;
	char	*new_str;
	int		i;

	i = 0;
	new_str = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '$')
		{
			tmp = find_env(str, env, &i);
			if (tmp)
				new_str = ft_strjoin(new_str, tmp);
		}
		else
		{
			tmp = not_env(str, &i);
			new_str = ft_strjoin(new_str, tmp);
			free(tmp);
		}
	}
	free(str);
	return (new_str);
}
