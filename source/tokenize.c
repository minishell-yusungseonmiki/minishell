/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusung <yusung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:05:41 by yusung            #+#    #+#             */
/*   Updated: 2023/11/29 22:03:08 by yusung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token	*make_token(const char *elem, e_type type)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	token->elem = strdup(elem);
	token->type = type;
	token->before_blank = 0;
	return (token);
}

int	meet_special(char c)
{
	if (c == '|')
		return (1);
	if (c == '<')
		return (1);
	if (c == '>')
		return (1);
	if (c == ' ')
		return (1);
	return (0);
}

// 반환값 : arg 0, special(리다이렉션이나 파이프) 1 또는 2, blank(공백) 3
int	make_special_token(t_list **lst, char *s)
{
	const char	special[5][3] = {"|", "<<", ">>", "<", ">"};
	int			i;

	if (*s == ' ')
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

void	make_arg_token(t_list **lst, char *s, int i, int start)
{
	char	*elem;

	elem = ft_substr(s, start, i - start);
	ft_lstadd_back(lst, ft_lstnew(make_token(elem, ARG)));
	free(elem);
}

int	is_quote(char c, int *i)
{
	char	q;
	int		check;

	q = 0;
	check = 0;
	if (c == '\'' || c == '\"')
	{
		if (q == 0)
			q = c;
		else if (c == q)
			q = 0;
		check = 1;
		(*i) += 1;
	}
	return (check);
}

void	set_index(int type, int *i, int *start)
{
	if (type == 0) //arg
		(*i) += 1;
	else if (type == 1 || type == 2) //파이프, 리다이렉션
	{	
		(*i) += type;
		(*start) = (*i);
	}
	else if (type == 3) //공백
	{
		(*i) += 1;
		(*start) = (*i);
	}
}

void	set_before_blank(t_list *lst, char *s)
{
	t_token	*token;
	int		i;
	int		blank;

	i = 0;
	blank = 0;
	while (s && s[i] && lst)
	{
		if (i != 0 && s[i - 1] == ' ')
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

	i = 0;
	start = 0;
	lst = NULL;
	while (s && s[i])
	{
		if (is_quote(s[i], &i) == 1)
			continue ;
		if (meet_special(s[i])) //명령어 이전까지(start~i-1)의 arg 저장
		{
			if (i != start) // 공백인 경우에 들어오면 i==start인 노드가 생겨버리는 것을 방지
				make_arg_token(&lst, s, i, start);
			start = i;
		}
		set_index(make_special_token(&lst, &s[i]), &i, &start);
	}
	if (i != start)
		make_arg_token(&lst, s, i, start);
	set_before_blank(lst, s);
	ft_lstiter(lst, print_token);
	return (lst);
}
