#include "../include/minishell.h"

void	execute_exit(t_proc_info *proc)
{
	char	*first_arg;
	int		i;

	first_arg = proc->cmd_argv[1];
	if (first_arg == NULL)
	{
		ft_putstr_fd("exit\n", 2);
		exit_code = 0;
		exit(exit_code);
	}
	i = 0;
	while (first_arg[i])
	{
		if (i == 0 && first_arg[i] == '-')
			i++;
		if (!ft_isdigit(first_arg[i])) //숫자가 아니면
		{
			ft_putstr_fd("exit: numeric argument required\n", 2);
			exit_code = 255;
			exit(exit_code);
		}
		i++;
	}
	exit_code = ft_atoi(first_arg);
	while (exit_code < 0)
	{
		exit_code *= -1;
		exit_code = 256 - exit_code;
	}
	exit_code = exit_code % 256;
	//printf("ec : %d\n", exit_code);
	if (proc->cmd_argv[2]) // 인자가 두개 이상이면
		ft_putstr_fd("exit: too many arguments\n", 2);
	else
		ft_putstr_fd("exit\n", 2);
	exit(exit_code);
}
