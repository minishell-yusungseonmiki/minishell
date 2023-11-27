#include "../include/minishell.h"

void    execute_env(char **cmd_argv, t_list **denv)
{
    if (cmd_argv[1])
        write(2, "No such file or directory\n", 26);
    else
        ft_lstiter(*denv, print_env);
}