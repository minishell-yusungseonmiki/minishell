#include "../include/minishell.h"

int	quote_check(char *s)
{
	char	q;
	int		i;

	q = 0;
	i = 0;
	while (s != 0 && s[i] != 0)
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			if (q == 0)
				q = s[i];
			else if (q == s[i])
				q = 0;
		}
		i++;
	}
	if (q != 0)
		return (error(SYNTAX));
	return (0);
}

static int	heredoc_cnt(t_list *lst)
{
	t_list	*cur;
	int		hcnt;

	hcnt = 0;
	cur = lst;
	while (cur)
	{
		if (((t_token *)(cur->content))->type == HEREDOC)
			hcnt++;
		cur = cur->next;
	}
	return (hcnt);
}

int	syntax_check(t_list *lst)
{
	t_list	*cur;

	cur = lst;
	if (((t_token *)(cur->content))->type == PIPE)
		return (error(SYNTAX));
	while (cur && cur->next)
	{
		if (((t_token *)(cur->content))->type != ARG)
		{
			if (((t_token *)(cur->content))->type == PIPE)
			{
				if (((t_token *)(cur->next->content))->type == PIPE)
					return (error(SYNTAX));
			}
			else if (((t_token *)(cur->next->content))->type != ARG)
				return (error(SYNTAX));
		}
		cur = cur->next;
	}
	if (((t_token *)(cur->content))->type != ARG)
		return (error(SYNTAX));
	if (heredoc_cnt(lst) > 16)
		return (error(MAX_HEREDOC));
	return (0);
}
