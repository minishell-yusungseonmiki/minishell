#include "minishell.h"

void	print_elem(void *token)
{
	printf("%s\n", ((t_token *)token)->elem);
}

t_token	*make_token(char *elem, e_type type)
{
	t_token *token = (t_token *)malloc(sizeof(t_token));
	token->elem = elem;
	token->type = type;
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

t_list *tokenize(char *s)
{
	int	i;
	char q;
	int	start = 0;
	t_list *lst;

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
			if (ft_strncmp(&s[i], "<<", 2) == 0)
			{
				ft_lstadd_back(&lst, ft_lstnew(make_token("<<", HEREDOC)));
				i += 2;
				start = i;
				check = 1;
			}
			else if (ft_strncmp(&s[i], ">>", 2) == 0)
			{
				ft_lstadd_back(&lst, ft_lstnew(make_token(">>", APPEND)));
				i += 2;
				start = i;
				check = 1;
			}
			else if (s[i] == '|')
			{
				ft_lstadd_back(&lst, ft_lstnew(make_token("|", PIPE)));
				i++;
				start = i;
				check = 1;
			}
			else if (s[i] == '<')
			{
				ft_lstadd_back(&lst, ft_lstnew(make_token("<", IN)));
				i++;
				start = i;
				check = 1;
			}
			else if (s[i] == '>')
			{
				ft_lstadd_back(&lst, ft_lstnew(make_token(">", OUT)));
				i++;
				start = i;
				check = 1;
			}
			else if (s[i] == ' ')
			{
				i++;
				start = i;
				check = 1;
			}
		}
		if (check == 0)
			i++;
	}
	if (i != start)
		ft_lstadd_back(&lst, ft_lstnew(make_token(ft_substr(s, start, i - start), ARG)));
	// ft_lstiter(lst, print_elem);
	return (lst);
}

// int main(int argc, char **argv)
// {
// 	printf("%s\n", argv[1]);
// 	if (argc == 2)
// 		tokenize(argv[1]);
// 	return (0);
// }
