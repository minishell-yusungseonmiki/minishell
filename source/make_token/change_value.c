/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusung <yusung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 16:51:39 by seonmiki          #+#    #+#             */
/*   Updated: 2023/12/04 16:49:56 by yusung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*switch_value(t_list *env, char *key)
{
	t_list	*lst;
	char	*tmp;

	lst = env;
	while (lst)
	{
		if (!ft_strncmp(((t_env *)(lst->content))->key, key, ft_strlen(key))
		&& ft_strlen(((t_env *)(lst->content))->key) == ft_strlen(key))
		{
			tmp = ft_strdup(((t_env *)(lst->content))->value);
			free(key);
			return (tmp);
		}
		lst = lst->next;
	}
	free(key);
	return (NULL);
}

static char	*find_env(char *str, t_list *env, int *i)
{
	int		start;
	int		end;

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
	while (str[*i] && str[*i] != ' ' && str[*i] != '\''
		&& str[*i] != '=' && str[*i] != ':')
		*i += 1;
	end = *i;
	return (switch_value(env, ft_substr(str, start, end - start)));
}

static char	*not_env(char *str, int *i)
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
	char	*new_str;
	char	*get_str;
	char	*tmp;
	int		i;

	i = 0;
	new_str = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '$')
			get_str = find_env(str, env, &i);
		else
			get_str = not_env(str, &i);
		if (get_str)
		{
			tmp = new_str;
			new_str = ft_strjoin(tmp, get_str);
			free(tmp);
			free(get_str);
		}
	}
	free(str);
	return (new_str);
}
