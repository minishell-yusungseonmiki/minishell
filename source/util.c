/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonmiki <seonmiki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 17:34:17 by seonmiki          #+#    #+#             */
/*   Updated: 2023/12/03 17:34:17 by seonmiki         ###   ########.fr       */
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

void	free_double_str(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
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

