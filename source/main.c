#include "../include/minishell.h"

void    leak()
{
    system("leaks minishell");
}

int main(int argc, char **argv, char **envp)
{
    atexit(leak);
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
            proc_lst = make_proc_list(token_lst, denv); // envp, denv
            heredoc(proc_lst); //h_filename
			execute(proc_lst); // in_fd, out_fd, child_pid
            add_history(line);
            free(line);
            ft_lstclear(&token_lst, free_token);
            ft_lstclear(&proc_lst, free_proc_info);
        }
        else
        {
            ft_lstclear(&denv, free_env);
            printf("exit\n");
            return (0);
        }
    }
    ft_lstclear(&denv, free_env);
    return (0);
}
