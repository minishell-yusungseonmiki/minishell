/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigint_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusung <yusung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 17:33:50 by seonmiki          #+#    #+#             */
/*   Updated: 2023/12/04 16:38:49 by yusung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	sigint_handler(int signum)
{
	(void) signum;
	g_exit_status = 1;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sigint_heredoc(int signum)
{
	(void) signum;
	g_exit_status = -1;
	printf("\n");
	close(0);
}

void	sigint_child(int signum)
{
	(void) signum;
	printf("\n");
}

void	sigint_last_child(int signum)
{
	(void) signum;
	g_exit_status = -130;
	printf("\n");
}
