#include "../include/minishell.h"

void	print_hfd(void	*h)
{	
	printf("filename : %s\n", (char *)h);
}

int main(int argc, char **argv, char **envp)
{
    char    *line;
    t_list  *lst;
    t_list  *denv;

    (void)argc;
    (void)argv;
    denv = envp_to_lst(envp); //환경변수 복제
    while (1)
    {
        print_off_signal();
        signal(SIGINT, sigint_handler);
        signal(SIGQUIT, SIG_IGN);
        line = readline("\033[1;34mminishell> \033[0m");
        if (line)
        {
            if (quote_check(line) == 1)
                continue;
            lst = tokenize(line);
            if (!lst || syntax_check(lst) == 1)
               continue;
            erase_quotes(lst, denv);
            find_pipe_and_execute(lst, denv, heredoc(lst));
            add_history(line);
            free(line);
        }
        else
        {
            printf("exit\n");
            return (0);
        }
    }
    return (0);
}