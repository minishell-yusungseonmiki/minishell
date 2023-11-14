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
            ft_lstiter(lst, print_elem);
            //syntax error check
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