#include "../include/minishell.h"

void sigint_handler(int signum)
{
    if (signum != SIGINT)
        return;
    printf("\n");
    rl_on_new_line();
    // rl_replace_lmakeine("", 0);
    rl_redisplay();
}

int    syntax_error(void)
{
    perror("syntax error");
    return (1);
}

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
			if (q == 0)
				q = s[i];
			else if (s[i] == q) //짝을 만나면 해제
				q = 0;
		}
        i++;
    }
    if (q != 0)
        return (syntax_error());
    return (0);
}

int    syntax_check(t_list *lst)
{
    t_list  *cur;

    cur = lst;
    if (((t_token *)(cur->content))->type == PIPE) // 첫 시작이 파이프인 경우
        return (syntax_error());
    while (cur && cur->next)
    {
        if (((t_token *)(cur->content))->type != ARG)
        {
            if (((t_token *)(cur->content))->type == PIPE)
            {
                if (((t_token *)(cur->next->content))->type == PIPE) // 연속 PIPE인 경우
                    return (syntax_error());
            }
            else if (((t_token *)(cur->next->content))->type != ARG) // REDIRECTION 다음이 ARG가 아닌 경우
                return (syntax_error());
        }
        cur = cur->next;
    }
    if (((t_token *)(cur->content))->type != ARG) // 맨 끝이 ARG가 아닌 경우
        return (syntax_error());
    return (0);
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
            if (quote_check(line) == 1)
                continue;
            lst = tokenize(line);
            //if (syntax_check(lst) == 1)
            //    continue;
            // ft_lstiter(lst, print_elem); //토큰 확인
            //따옴표 제거 및 환경변수 치환 -> 실행
            // printf("%s", heredoc(lst)); //히어독 먼저 처리, 마지막 히어독 리턴

            find_pipe(lst); //파이프별로 프로세스 정보 구조체에 담기
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