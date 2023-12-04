/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusung <yusung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:05:41 by yusung            #+#    #+#             */
/*   Updated: 2023/12/04 16:53:06 by yusung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_token	*make_token(const char *elem, t_type type)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	token->elem = ft_strdup(elem);
	token->type = type;
	token->before_blank = 0;
	return (token);
}

static int	make_special_token(t_list **lst, char *s)
{
	const char	special[5][3] = {"|", "<<", ">>", "<", ">"};
	int			i;

	if (ft_isspace(*s))
		return (3);
	i = 0;
	while (i < 5)
	{
		if (ft_strncmp(s, special[i], ft_strlen(special[i])) == 0)
		{
			ft_lstadd_back(lst, ft_lstnew(make_token(special[i], i + 1)));
			return (ft_strlen(special[i]));
		}
		i++;
	}
	return (0);
}

static void	make_arg_token(t_list **lst, char *s, int i, int start)
{
	char	*elem;

	elem = ft_substr(s, start, i - start);
	ft_lstadd_back(lst, ft_lstnew(make_token(elem, ARG)));
	free(elem);
}

static void	set_before_blank(t_list *lst, char *s)
{
	t_token	*token;
	int		i;
	int		blank;

	i = 0;
	blank = 0;
	while (s && s[i] && lst)
	{
		if (i != 0 && (s[i - 1] == ' ' || s[i - 1] == '\t'))
			blank = 1;
		token = lst->content;
		if (ft_strncmp(&s[i], token->elem, ft_strlen(token->elem)) == 0)
		{
			if (blank)
				token->before_blank = 1;
			lst = lst->next;
			i += ft_strlen(token->elem);
			blank = 0;
		}
		else
			i++;
	}
}

t_list	*tokenize(char *s)
{
	t_list	*lst;
	int		i;
	int		start;
	char	q;

	i = 0;
	start = 0;
	lst = NULL;
	q = 0;
	while (s && s[i])
	{
		if (in_quote(s[i], &q, &i))
			continue ;
		if (meet_special(s[i]))
		{
			if (i != start)
				make_arg_token(&lst, s, i, start);
			start = i;
		}
		set_index(make_special_token(&lst, &s[i]), &i, &start);
	}
	if (i != start)
		make_arg_token(&lst, s, i, start);
	set_before_blank(lst, s);
	return (lst);
}
