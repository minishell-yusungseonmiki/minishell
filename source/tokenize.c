#include "../include/minishell.h"

void	print_elem(void *token)
{
	printf("-----------\n");
	printf("content: %s\n state: %d\n", ((t_token *)token)->elem, ((t_token *)token)->type);
	printf("-----------\n");
}

t_token	*make_token(char *elem, e_type type)
{
	t_token *token = (t_token *)malloc(sizeof(t_token));
	token->elem = elem;
	token->type = type;
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

int	check_special(t_list **lst, char *s, int *start, int *i)
{
	if (ft_strncmp(&s[*i], "<<", 2) == 0)
	{
		ft_lstadd_back(lst, ft_lstnew(make_token("<<", HEREDOC)));
		(*i) += 2;
	}
	else if (ft_strncmp(&s[*i], ">>", 2) == 0)
	{
		ft_lstadd_back(lst, ft_lstnew(make_token(">>", APPEND)));
		(*i) += 2;
	}
	else if (s[*i] == '|')
	{
		ft_lstadd_back(lst, ft_lstnew(make_token("|", PIPE)));
		(*i)++;
	}
	else if (s[*i] == '<')
	{
		ft_lstadd_back(lst, ft_lstnew(make_token("<", IN)));
		(*i)++;
	}
	else if (s[*i] == '>')
	{
		ft_lstadd_back(lst, ft_lstnew(make_token(">", OUT)));
		(*i)++;
	}
	else if (s[*i] == ' ')
		(*i)++;
	else // 명령어나 공백이 아니면(=인덱스 증가가 없으면) check가 0
		return (0);
	*start = *i;
	return (1); // 명령어나 공백이면(=인덱스 증가가 있으면) check가 1
}


t_list *tokenize(char *s)
{
	t_list *lst;
	int	i;
	char q;
	int	start = 0;

	int	check = 0;
	i = 0;
	lst = NULL;
	q = 0;
	while (s != 0 && s[i] != 0)
	{
		check = 0;
		if (s[i] == '\'' || s[i] == '\"')
		{
			if (q == 0)
				q = s[i];
			else if (s[i] == q) //짝을 만나면 해제
				q = 0;
			i++;
			check = 1;
		}
		if (q == 0)
		{
			if (end_of_token(&s[i]) == 0) //명령어 이전까지(start~i-1)의 arg 저장
			{
				if (i != start) // 공백인 경우에 들어오면 i==start인 노드가 생겨버리는 것을 방지
					ft_lstadd_back(&lst, ft_lstnew(make_token(ft_substr(s, start, i - start), ARG)));
				start = i;
			}
			check += check_special(&lst, s, &start, &i);
		}
		if (check == 0)
			i++;
	}
	if (i != start)
		ft_lstadd_back(&lst, ft_lstnew(make_token(ft_substr(s, start, i - start), ARG)));
	// ft_lstiter(lst, print_elem);
	return (lst);
}
