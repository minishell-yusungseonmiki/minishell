#include "../include/minishell.h"

int is_builtin(t_proc_info *proc_info)
{
    char    *cmd;

    if (proc_info->cmd_argv == NULL)
        return (0);
    cmd = (proc_info->cmd_argv)[0];
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

void    execute_builtin(char *cmd, char **cmd_argv, char **envp, t_list *denv, t_proc_info	*proc)
{
    (void) envp;
    // if (ft_strncmp(cmd, "echo", ft_strlen(cmd)) == 0 && ft_strlen(cmd) == ft_strlen("echo"))
    //     execute_echo(cmd, cmd_argv, envp);
    // else if (ft_strncmp(cmd, "cd", ft_strlen(cmd)) == 0 && ft_strlen(cmd) == ft_strlen("cd"))
    //     execute_cd(cmd, cmd_argv, envp);
    // else if (ft_strncmp(cmd, "pwd", ft_strlen(cmd)) == 0 && ft_strlen(cmd) == ft_strlen("pwd"))
    //     execute_pwd(cmd, cmd_argv, envp);
    if (ft_strncmp(cmd, "export", ft_strlen(cmd)) == 0 && ft_strlen(cmd) == ft_strlen("export"))
        execute_export(cmd_argv, denv, proc);
    else if (ft_strncmp(cmd, "unset", ft_strlen(cmd)) == 0 && ft_strlen(cmd) == ft_strlen("unset"))
        execute_unset(cmd_argv, &denv);
    else if (ft_strncmp(cmd_argv[0], "env", ft_strlen(cmd)) == 0 && ft_strlen(cmd_argv[0]) == ft_strlen("env"))
        execute_env(cmd_argv, &denv);
    // else if (ft_strncmp(cmd, "exit", ft_strlen(cmd)) == 0 && ft_strlen(cmd) == ft_strlen("exit"))
    //     execute_exit(cmd, cmd_argv, envp);
}
