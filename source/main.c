#include "../include/minishell.h"

int main(int argc, char **argv, char **envp)
{
    char    *line;
    t_list  *token_lst;
    t_list  *proc_lst;
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
            	continue; //add_history &&free
            token_lst = tokenize(line);
            if (!token_lst || syntax_check(token_lst) == 1)
            	continue; //add_history &&free
            erase_quotes(token_lst, denv);
            proc_lst = make_proc_list(token_lst, envp, denv);
            heredoc(token_lst, proc_lst);
            ft_lstiter(proc_lst, print_proc_info);
            // find_pipe_and_execute(token_lst, proc_lst);
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
