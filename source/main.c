#include "../include/minishell.h"

void    leak()
{
    system("leaks minishell");
}

static int	line_check(char *line, t_list **token_lst)
{
	if (quote_check(line) == 1)
	{
		add_history(line);
		free(line);
		return (0);
	}
	*token_lst = tokenize(line);
	if (!(*token_lst) || syntax_check(*token_lst) == 1)
	{
		add_history(line);
		free(line);
		ft_lstclear(token_lst, free_token);
		return (0);
	}
	return (1);
}

static void    run_minishell(char *line, t_list **denv)
{
    t_list  *token_lst;
    t_list  *proc_lst;

    if (line)
    {
        if (!line_check(line, &token_lst))
			return ;
        erase_quotes(token_lst, *denv);
        proc_lst = make_proc_list(token_lst, denv); // envp, denv
        heredoc(proc_lst); //h_filename
        // printf("before: %p\n", denv);
        execute(proc_lst); // in_fd, out_fd, child_pid
        // printf("after: %p\n", denv);
        // printf("%p\n", ((t_proc_info *)(proc_lst->content))->denv);
        *denv = ((t_proc_info *)(proc_lst->content))->denv;
        add_history(line);
        free(line);
        ft_lstclear(&token_lst, free_token);
        ft_lstclear(&proc_lst, free_proc_info);
    }
    else
    {
        ft_lstclear(denv, free_env);
        printf("exit\n");
        exit(0);
    }
}

int main(int argc, char **argv, char **envp)
{
    // atexit(leak);
    char    *line;
    t_list  *denv;

    if (argc > 1 || argv[1])
        error(START);
    denv = envp_to_lst(envp); //환경변수 복제
    while (1)
    {
        print_off_signal();
        signal(SIGINT, sigint_handler);
        signal(SIGQUIT, SIG_IGN);
        line = readline("\033[1;34mminishell> \033[0m");
        run_minishell(line, &denv);
    }
    ft_lstclear(&denv, free_env);
    return (0);
}
