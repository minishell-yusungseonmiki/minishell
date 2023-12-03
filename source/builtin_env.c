/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonmiki <seonmiki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 16:49:44 by seonmiki          #+#    #+#             */
/*   Updated: 2023/12/03 19:36:30 by seonmiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void    execute_env(char **cmd_argv, t_list **denv)
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
