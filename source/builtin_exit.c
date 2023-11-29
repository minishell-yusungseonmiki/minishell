#include "../include/minishell.h"

void	execute_exit(t_proc_info *proc, int only_builtin)
{
	char	*first_arg;
	int		i;

	if (only_builtin) //builtin 하나인 경우만 exit 출력
		printf("exit\n");
	first_arg = proc->cmd_argv[1];
	if (first_arg == NULL)
	{
		g_exit_status = 0;
		exit(g_exit_status);
	}
	i = 0;
	while (first_arg[i])
	{
		if (i == 0 && first_arg[i] == '-')
			i++;
		if (!ft_isdigit(first_arg[i])) //숫자가 아니면
		{
			printf("exit: numeric argument required\n");
			g_exit_status = 255;
			exit(g_exit_status);
		}
		i++;
	}
	g_exit_status = ft_atoi(first_arg);
	while (g_exit_status < 0)
	{
		g_exit_status *= -1;
		g_exit_status = 256 - g_exit_status;
	}
	g_exit_status = g_exit_status % 256;
	//printf("ec : %d\n", g_exit_status);
	if (proc->cmd_argv[2]) // 인자가 두개 이상이면
		printf("exit: too many arguments\n");
	exit(g_exit_status);
}
