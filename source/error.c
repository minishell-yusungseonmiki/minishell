/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonmiki <seonmiki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 16:54:38 by seonmiki          #+#    #+#             */
/*   Updated: 2023/12/03 19:21:44 by seonmiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	exit_error(e_error err, char *str)
{
	if (err == START)
	{
		write(2, "argument only ./minishell\n", 26);
		exit(1);
	}
	else if (err == MAX_HEREDOC)
	{
		write(2, "maximum here-document count exceeded\n", 37);
		exit(1);
	}
	else if (err == OPEN_FAILED)
	{
		write(2, str, ft_strlen(str));
		write(2, ": No such file or directory\n", 28); //permision deny 인 경우..?
		exit(1);
	}
	else if (err == NOT_CMD)
	{
		write(2, str, ft_strlen(str));
		write(2, ": No such file or directory\n", 29);
		exit(127);
	}
	else if (err == NOT_FILE)
	{
		write(2, str, ft_strlen(str));
		write(2, ": command not found\n", 21);
		exit(127);
	}
}

int	error(e_error err, char *str)
{
	exit_error(err, str);
	if (err == SYNTAX)
	{
		write(2, "syntax error\n", 13);
		g_exit_status = 1;
	}
	else if (err == INVALID_EXPORT)
	{
		write(2, "export: '", 9);
		write(2, str, ft_strlen(str));
		write(2, "': not a valid identifier\n", 26);
        g_exit_status = 1;
	}
	return (1);
}
