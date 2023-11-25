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

void	print_hfd(void	*h)
{	
	printf("fd : %d\n", *(int *)h);
}

int main(int argc, char **argv, char **envp)
{
    char    *line;
    t_list  *lst;
    t_list  *denv;

    if (argc != 1 && ft_strncmp(*argv, "./minishell", ft_strlen(*argv)))
        return (1);
    denv = envp_to_lst(envp); //환경변수 복제
    // ft_lstiter(denv, print_env); //환경변수 복제 잘 되었는지 확인
    // char **ddenv = lst_to_envp(denv); //환경변수 다시 2차원 배열로
    // print_envp(ddenv); //2차원 배열 잘 만들어지는지 확인
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
            if (!lst || syntax_check(lst) == 1)
               continue;
            // ft_lstiter(lst, print_elem); //토큰 확인
            erase_quotes(lst, denv); //따옴표 제거만 (환경변수 처리안함)
            // ft_lstiter(lst, print_elem);
        	ft_lstiter(heredoc(lst), print_hfd); //히어독 먼저 처리, 마지막 히어독 리턴
            find_pipe_and_execute(lst, denv); //파이프 단위로 새로운 리스트 생성하여 실행
            add_history(line);
            free(line);
            // line = NULL;
        }
        else
        {
            printf("exit\n");
            return (0);
        }
    }
    return (0);
}