#include "../include/minishell.h"

int is_builtin(char **cmd_argv)
{
    char    *cmd;

    if (cmd_argv == NULL)
        return (0);
    cmd = (cmd_argv)[0];
    if (ft_strncmp(cmd, "echo", ft_strlen(cmd)) == 0 && ft_strlen(cmd) == ft_strlen("echo"))
        return (1);
    else if (ft_strncmp(cmd, "cd", ft_strlen(cmd)) == 0 && ft_strlen(cmd) == ft_strlen("cd"))
        return (1);
    else if (ft_strncmp(cmd, "pwd", ft_strlen(cmd)) == 0 && ft_strlen(cmd) == ft_strlen("pwd"))
        return (1);
    else if (ft_strncmp(cmd, "export", ft_strlen(cmd)) == 0 && ft_strlen(cmd) == ft_strlen("export"))
        return (1);
    else if (ft_strncmp(cmd, "unset", ft_strlen(cmd)) == 0 && ft_strlen(cmd) == ft_strlen("unset"))
        return (1);
    else if (ft_strncmp(cmd, "env", ft_strlen(cmd)) == 0 && ft_strlen(cmd) == ft_strlen("env"))
        return (1);
    else if (ft_strncmp(cmd, "exit", ft_strlen(cmd)) == 0 && ft_strlen(cmd) == ft_strlen("exit"))
        return (1);
    return (0);
}

void    execute_builtin(t_proc_info *proc, t_list *sub_lst)
{
    char    *cmd;

    if (proc->cmd_argv == NULL)
        return ;
    cmd = (proc->cmd_argv)[0];
    if (ft_strncmp(cmd, "echo", ft_strlen(cmd)) == 0 && ft_strlen(cmd) == ft_strlen("echo"))
        execute_echo(proc, sub_lst);
    else if (ft_strncmp(cmd, "cd", ft_strlen(cmd)) == 0 && ft_strlen(cmd) == ft_strlen("cd"))
        execute_cd(proc);
    else if (ft_strncmp(cmd, "pwd", ft_strlen(cmd)) == 0 && ft_strlen(cmd) == ft_strlen("pwd"))
        execute_pwd(proc);
    else if (ft_strncmp(cmd, "export", ft_strlen(cmd)) == 0 && ft_strlen(cmd) == ft_strlen("export"))
        execute_export(proc->cmd_argv, proc->denv, proc);
    else if (ft_strncmp(cmd, "unset", ft_strlen(cmd)) == 0 && ft_strlen(cmd) == ft_strlen("unset"))
        execute_unset(proc->cmd_argv, &proc->denv);
    else if (ft_strncmp(cmd, "env", ft_strlen(cmd)) == 0 && ft_strlen(cmd) == ft_strlen("env"))
        execute_env(proc->cmd_argv, &proc->denv);
    else if (ft_strncmp(cmd, "exit", ft_strlen(cmd)) == 0 && ft_strlen(cmd) == ft_strlen("exit"))
        execute_exit(proc);
}
