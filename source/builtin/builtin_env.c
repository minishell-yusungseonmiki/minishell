/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusung <yusung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 16:49:44 by seonmiki          #+#    #+#             */
/*   Updated: 2023/12/04 16:44:23 by yusung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	print_env(void *token)
{
	if (((t_env *)token)->value[0] == '\0')
		return ;
	printf("%s=%s\n", ((t_env *)token)->key, ((t_env *)token)->value);
}

void	execute_env(char **cmd_argv, t_list **denv)
{
	if (cmd_argv[1])
	{
		write(2, cmd_argv[1], ft_strlen(cmd_argv[1]));
		write(2, ": No such file or directory\n", 28);
		g_exit_status = 127;
	}
	else
	{
		if (denv && *denv)
			ft_lstiter(*denv, print_env);
	}
}
