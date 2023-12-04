/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusung <yusung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 16:55:58 by yusung            #+#    #+#             */
/*   Updated: 2023/12/04 16:42:41 by yusung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	cal_exit_status(char *first_arg)
{
	g_exit_status = ft_atoi(first_arg);
	while (g_exit_status < 0)
	{
		g_exit_status *= -1;
		g_exit_status = 256 - g_exit_status;
	}
	g_exit_status = g_exit_status % 256;
}

static void	check_numeric_first_arg(char *first_arg)
{
	int	i;

	i = 0;
	while (first_arg[i])
	{
		if (i == 0 && first_arg[i] == '-')
			i++;
		if (!ft_isdigit(first_arg[i]))
		{
			write(2, "exit: ", 7);
			write(2, first_arg, ft_strlen(first_arg));
			write(2, ": numeric argument required\n", 29);
			g_exit_status = 255;
			exit(g_exit_status);
		}
		i++;
	}
}

void	execute_exit(t_proc_info *proc, int only_builtin)
{
	char	*first_arg;

	if (only_builtin)
		write(2, "exit\n", 6);
	first_arg = proc->cmd_argv[1];
	if (first_arg == NULL)
	{
		g_exit_status = 0;
		exit(g_exit_status);
	}
	check_numeric_first_arg(first_arg);
	cal_exit_status(first_arg);
	if (proc->cmd_argv[2])
		write(2, "exit: too many arguments\n", 26);
	exit(g_exit_status);
}
