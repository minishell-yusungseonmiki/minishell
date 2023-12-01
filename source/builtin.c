#include "../include/minishell.h"

int is_builtin(char **cmd_argv)
{
    char    *cmd;

    if (cmd_argv == NULL)
        return (0);
    cmd = (cmd_argv)[0];
    if (is_same(cmd, "echo"))
        return (1);
    else if (is_same(cmd, "cd"))
        return (1);
    else if (is_same(cmd, "pwd"))
        return (1);
    else if (is_same(cmd, "export"))
        return (1);
    else if (is_same(cmd, "unset"))
        return (1);
    else if (is_same(cmd, "env"))
        return (1);
    else if (is_same(cmd, "exit"))
        return (1);
    return (0);
}

void    execute_builtin(t_proc_info *proc, t_list *sub_lst, int only_builtin)
{
    char    *cmd;

    if (proc->cmd_argv == NULL)
        return ;
    cmd = (proc->cmd_argv)[0];
    if (is_same(cmd, "echo"))
        execute_echo(proc, sub_lst);
    else if (is_same(cmd, "cd"))
        execute_cd(proc);
    else if (is_same(cmd, "pwd"))
        execute_pwd(proc);
    else if (is_same(cmd, "export"))
        execute_export(proc->cmd_argv, proc->denv, proc);
    else if (is_same(cmd, "unset"))
        execute_unset(proc->cmd_argv, &proc->denv);
    else if (is_same(cmd, "env"))
        execute_env(proc->cmd_argv, &proc->denv);
    else if (is_same(cmd, "exit"))
        execute_exit(proc, only_builtin);
}
