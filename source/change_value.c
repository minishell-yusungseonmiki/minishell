#include "../include/minishell.h"

char	*change_value(char *str, t_list *env)
{
	int		start;
	int		end;
	char	*tmp;
	char	*key;
	char	*new_str;
	int		i;
	t_list	*lst;

	i = 0;
	new_str = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '$')
		{
			start = i + 1;
			while (str[i] && str[i] != ' ' && str[i] != '\"')
				i++;
			end = i;
			key = ft_substr(str, start, end - start);
			// printf("key: %s\n", key);
			lst = env;
			while (lst)
			{
				if (!ft_strncmp(((t_env *)(env->content))->key, key, ft_strlen(key))
				&& ft_strlen(((t_env *)(env->content))->key) == ft_strlen(key))
				{
					tmp = ((t_env *)(env->content))->value;
					// printf("key: %s, value: %s\n", key, tmp);
					free(key);
					new_str = ft_strjoin(new_str, tmp);
					// printf("new_value: %s\n", new_str);
					break ;
				}
				lst = lst->next;
			}
		}
		else
		{
			start = i;
			while (str[i] && str[i] != '$')
				i++;
			end = i;
			tmp = ft_substr(str, start, end - start);
			new_str = ft_strjoin(new_str, tmp);
			free(tmp);
		}
	}
	free(str);
	return (new_str);
}
