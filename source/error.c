/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonmiki <seonmiki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 16:54:38 by seonmiki          #+#    #+#             */
/*   Updated: 2023/12/03 16:54:40 by seonmiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	error(e_error err)
{
	if (err == SYNTAX)
		perror("syntax error");
	else if (err == MAX_HEREDOC)
	{
		perror("maximum here-document count exceeded");
		exit(1);
	}
	else if (err == INVALID_EXPORT)
	{
		write(2, "export: not a valid identifier\n", 31);
        g_exit_status = 1;
	}
	return (1);
}
