/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   erase_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonmiki <seonmiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 16:54:26 by seonmiki          #+#    #+#             */
/*   Updated: 2023/12/04 15:15:13 by seonmiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*single_quote(char *elem, int *i)
{
	int		start;
	int		end;
	char	*tmp;
	char	q;

	q = elem[*i];
	start = *i;
	*i += 1;
	while (elem[*i] && elem[*i] != q)
		*i += 1;
	end = *i;
	tmp = ft_substr(elem, start + 1, end - start - 1);
	*i += 1;
	return (tmp);
}

char	*double_quote(char *elem, int *i, t_list *env)
{
	int		start;
	int		end;
	char	*tmp;
	char	q;
	int		flag;

	q = elem[*i];
	start = *i;
	*i += 1;
	flag = 0;
	while (elem[*i] && elem[*i] != q)
	{
		if (elem[*i] == '$' && elem[*i + 1] && elem[*i + 1] != ' '
			&& elem[*i + 1] != q)
			flag = 1;
		*i += 1;
	}
	end = *i;
	tmp = ft_substr(elem, start + 1, end - start - 1);
	*i += 1;
	if (flag)
		return (change_value(tmp, env));
	return (tmp);
}

char	*not_quote(char *elem, int *i, t_list *env)
{
	int		start;
	int		end;
	char	*tmp;
	int		flag;

	if (elem[*i] == '\\')
		*i += 1;
	start = *i;
	flag = 0;
	while (elem[*i] && elem[*i] != '\'' && elem[*i] != '\"')
	{
		if (elem[*i] == '$' && elem[*i + 1] && elem[*i + 1] != ' ')
			flag = 1;
		*i += 1;
	}
	end = *i;
	tmp = ft_substr(elem, start, end - start);
	if (flag)
		return (change_value(tmp, env));
	return (tmp);
}

static void	erase_quotes_arg(t_list *lst, t_list *env)
{
	char	*elem;
	char	*new_elem;
	char	*str;
	char	*tmp;
	int		i;

	elem = ((t_token *)(lst->content))->elem;
	new_elem = ft_strdup("");
	i = 0;
	while (elem[i])
	{
		if (elem[i] == '\'')
			str = single_quote(elem, &i);
		else if (elem[i] == '\"')
			str = double_quote(elem, &i, env);
		else
			str = not_quote(elem, &i, env);
		tmp = new_elem;
		new_elem = ft_strjoin(tmp, str);
		free(str);
		free(tmp);
	}
	free(((t_token *)(lst->content))->elem);
	((t_token *)(lst->content))->elem = new_elem;
}

void	erase_quotes(t_list *lst, t_list *env)
{
	while (lst)
	{
		if (((t_token *)(lst->content))->type == ARG)
			erase_quotes_arg(lst, env);
		lst = lst->next;
	}
}
