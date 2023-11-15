#include "../include/minishell.h"

void sigint_handler(int signum)
{
    if (signum != SIGINT)
        return;
    printf("\n");
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

void    syntax_error(void)
{
    perror("syntax error");
    exit(1);
}

void    quote_check(char *s)
{
    char    q;
    int     i;

    q = 0;
    i = 0;
	while (s != 0 && s[i] != 0)
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			if (q == 0)
				q = s[i];
			else if (s[i] == q) //짝을 만나면 해제
				q = 0;
		}
        i++;
    }
    if (q != 0)
        syntax_error();
}

void    syntax_check(t_list *lst)
{
    t_list  *cur;

    cur = lst;
    if (((t_token *)(cur->content))->type == PIPE) // 첫 시작이 파이프인 경우
        syntax_error();
    while (cur && cur->next)
    {
        if (((t_token *)(cur->content))->type != ARG)
        {
            if (((t_token *)(cur->content))->type == PIPE)
            {
                if (((t_token *)(cur->next->content))->type == PIPE) // 연속 PIPE인 경우
                    syntax_error();
            }
            else if (((t_token *)(cur->next->content))->type != ARG) // REDIRECTION 다음이 ARG가 아닌 경우
                syntax_error();
        }
        cur = cur->next;
    }
    if (((t_token *)(cur->content))->type != ARG) // 맨 끝이 ARG가 아닌 경우
        syntax_error();
}

int main(void)
{
    char    *line;
    t_list  *lst;

    while (1)
    {
        signal(SIGINT, sigint_handler);
        signal(SIGQUIT, SIG_IGN);
        line = readline("input> ");
        if (line)
        {
            quote_check(line);
            lst = tokenize(line);
            syntax_check(lst);
            ft_lstiter(lst, print_elem); //토큰 확인
            //따옴표 제거 및 환경변수 치환 -> 실행
            add_history(line);
            free(line);
            line = NULL;
        }
        else
        {
            printf("exit");
            return (0);
        }
    }
    return (0);
}