/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusung <yusung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:05:41 by yusung            #+#    #+#             */
/*   Updated: 2023/11/29 16:12:28 by yusung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token	*make_token(char *elem, e_type type, int blank)
{
	t_token *token = (t_token *)malloc(sizeof(t_token));
	token->elem = strdup(elem);
	token->type = type;
	token->before_blank = 0;
	if (blank == 2)
		token->before_blank = 1;
	return (token);
}

int	end_of_token(char *s)
{
	if (*s == '|')
		return (0);
	if (*s == '<')
		return (0);
	if (*s == '>')
		return (0);
	if (*s == ' ')
		return (0);
	return (1);
}

int	check_special(t_list **lst, char *s, int *start, int *s_idx)
{
	char	special[5][3] = {"|", "<<", ">>", "<", ">"};
	int	return_value; // arg 0, special(리다이렉션이나 파이프) 1, blank(공백) 2
	int	i;

	i = 0;
	return_value = 0;
	while (i < 5)
	{
		if (ft_strncmp(&s[*s_idx], special[i], ft_strlen(special[i])) == 0)
		{
			ft_lstadd_back(lst, ft_lstnew(make_token(special[i], i + 1, 0)));
			(*s_idx) += ft_strlen(special[i]);
			*start = *s_idx;
			return (1);
		}
		i++;
	}
	if (s[*s_idx] == ' ')
	{
		(*s_idx)++;
		*start = *s_idx;
		return (2);
	}
	return (0);
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
		(*i)++;
		check = 1;
	}
	return (check);
}


t_list *tokenize(char *s)
{
	t_list *lst;
	int	i;
	int	start = 0;
	int	check;
	int	blank;
	int	ch_sp;
	char	*elem;

	i = 0;
	lst = NULL;
	blank = 0;
	while (s != 0 && s[i] != 0)
{
		check = is_quote(s[i], &i);
		if (check == 0) // 따옴표 안에 있는게 아니면
		{
			if (end_of_token(&s[i]) == 0) //명령어 이전까지(start~i-1)의 arg 저장
			{
				if (i != start) // 공백인 경우에 들어오면 i==start인 노드가 생겨버리는 것을 방지
				{
					elem = ft_substr(s, start, i - start);
					ft_lstadd_back(&lst, ft_lstnew(make_token(elem, ARG, blank)));
					free(elem);
					blank = 0;
				}
				start = i;
			}
			ch_sp = check_special(&lst, s, &start, &i);
			if (ch_sp == 2)
				blank = 2;
			check += ch_sp;
		}
		if (check == 0)
			i++;
	}
	if (i != start)
	{
		elem = ft_substr(s, start, i - start);
		ft_lstadd_back(&lst, ft_lstnew(make_token(elem, ARG, blank)));
		free(elem);
	}
	//ft_lstiter(lst, print_token);
	return (lst);
}
