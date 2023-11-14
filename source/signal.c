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
    perror("syntax error");+++
    exit(1);
}

void    syntax_check(t_list *lst)
{
    t_list  *cur;

    cur = lst;
    if (((t_token *)(cur->content))->type == PIPE)
        syntax_error();
    while (cur && cur->next)
    {
        if (((t_token *)(cur->content))->type != ARG)
        {
            if (((t_token *)(cur->content))->type == PIPE)
            {
                if (((t_token *)(cur->next->content))->type == PIPE)
                    syntax_error();
            }
            else if (((t_token *)(cur->next->content))->type != ARG)
                syntax_error();
        }
        cur = cur->next;
    }
    if (((t_token *)(cur->content))->type != ARG)
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