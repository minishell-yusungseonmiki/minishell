/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigquit_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusung <yusung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 15:37:19 by seonmiki          #+#    #+#             */
/*   Updated: 2023/12/04 16:38:54 by yusung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	sigquit_child(int signum)
{
	(void) signum;
	SIG_DFL ;
}

void	sigquit_last_child(int signum)
{
	(void) signum;
	g_exit_status = -131;
	SIG_DFL ;
}
