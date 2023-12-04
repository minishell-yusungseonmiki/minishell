/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_print.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusung <yusung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 16:50:03 by seonmiki          #+#    #+#             */
/*   Updated: 2023/12/04 16:45:12 by yusung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	print_envp(char **envp, int out_fd)
{
	int	i;

	i = 0;
	while (envp && envp[i])
	{
		ft_putstr_fd("declare -x ", out_fd);
		ft_putstr_fd(envp[i], out_fd);
		ft_putstr_fd("\n", out_fd);
		i++;
	}
}

static void	swap_env(char **now, char **next)
{
	char	*tmp;

	tmp = *now;
	*now = *next;
	*next = tmp;
}

void	print_export(t_list **denv, t_proc_info *proc)
{
	char	**env;
	int		i;
	int		j;

	env = lst_to_envp(*denv, 1);
	if (!env)
		return ;
	i = 0;
	while (env[i + 1])
	{
		j = i + 1;
		while (env[j])
		{
			if (ft_strncmp(env[i], env[j], ft_strchr(env[i], '=') - env[i]) > 0)
				swap_env(&env[i], &env[j]);
			j++;
		}
		i++;
	}
	print_envp(env, proc->out_fd);
	free_double_str(env);
}

int	cmd_is_empty(char **cmd_argv)
{
	int	i;

	i = 1;
	while (cmd_argv[i])
	{
		if (cmd_argv[i][0] != '\0')
			return (0);
		i++;
	}
	return (1);
}
