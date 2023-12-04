/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonmiki <seonmiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 17:34:17 by seonmiki          #+#    #+#             */
/*   Updated: 2023/12/04 15:24:31 by seonmiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_same(char *a, char *b)
{
	if (ft_strncmp(a, b, ft_strlen(b)) == 0
		&& ft_strlen(a) == ft_strlen(b))
		return (1);
	return (0);
}

void	pipe_open(int fd[2])
{
	if (pipe(fd) < 0)
	{
		perror("pipe error");
		exit(1);
	}
}

pid_t	make_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork error");
		exit(1);
	}
	return (pid);
}

int	line_check(char *line, t_list **token_lst)
{
	if (quote_check(line) == 1)
	{
		add_history(line);
		free(line);
		return (0);
	}
	*token_lst = tokenize(line);
	if (!(*token_lst) || syntax_check(*token_lst) == 1)
	{
		add_history(line);
		free(line);
		ft_lstclear(token_lst, free_token);
		return (0);
	}
	return (1);
}

int	ft_isspace(char c)
{
	if (c == ' ')
		return (1);
	if (c == '\t')
		return (1);
	if (c == '\n')
		return (1);
	if (c == '\v')
		return (1);
	if (c == '\f')
		return (1);
	if (c == '\r')
		return (1);
	return (0);
}
