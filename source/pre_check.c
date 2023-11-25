#include "../include/minishell.h"

int    quote_check(char *s)
{
    char    q;
    int     i;

    q = 0;
    i = 0;
	while (s != 0 && s[i] != 0)
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			if (q == 0 && (i == 0 || (i != 0 && s[i - 1] != '\\')))
				q = s[i];
            else if (q == '\"')
            {
                if (s[i] == q && s[i - 1] != '\\')
                    q = 0;
            }
            else if (q == '\'')
            {
                if (s[i] == q)
                    q = 0;
            }
		}
        i++;
    }
    if (q != 0)
        return (error(SYNTAX));
    return (0);
}

int    syntax_check(t_list *lst)
{
    t_list  *cur;
    int     hcnt;

    cur = lst;
    if (((t_token *)(cur->content))->type == PIPE) // 첫 시작이 파이프인 경우
        return (error(SYNTAX));
    hcnt = 0;
    while (cur && cur->next)
    {
        if (((t_token *)(cur->content))->type == HEREDOC)
            hcnt++;
        if (((t_token *)(cur->content))->type != ARG)
        {
            if (((t_token *)(cur->content))->type == PIPE)
            {
                if (((t_token *)(cur->next->content))->type == PIPE) // 연속 PIPE인 경우
                    return (error(SYNTAX));
            }
            else if (((t_token *)(cur->next->content))->type != ARG) // REDIRECTION 다음이 ARG가 아닌 경우
                return (error(SYNTAX));
        }
        cur = cur->next;
    }
    if (((t_token *)(cur->content))->type != ARG) // 맨 끝이 ARG가 아닌 경우
        return (error(SYNTAX));
    if (hcnt > 16)
        return (error(MAX_HEREDOC));
    return (0);
}
