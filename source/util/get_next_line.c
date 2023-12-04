/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusung <yusung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 16:53:09 by seonmiki          #+#    #+#             */
/*   Updated: 2023/12/04 17:01:12 by yusung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	have_endline(char *backup)
{
	int	i;

	i = 0;
	while (backup[i])
	{
		if (backup[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static char	*gnl_get_read(int fd, char **backup)
{
	char	buf[BUFFER_SIZE + 1];
	int		read_size;
	char	*tmp;

	while (!have_endline(*backup))
	{
		read_size = read(fd, buf, BUFFER_SIZE);
		if (read_size < 0)
			return (NULL);
		if (read_size == 0)
			break ;
		buf[read_size] = '\0';
		tmp = ft_strjoin(*backup, buf);
		if (!tmp)
			return (NULL);
		free(*backup);
		*backup = tmp;
	}
	return (*backup);
}

static char	*gnl_cutbynl(char *result)
{
	char	*newbackup;
	int		i;

	i = 0;
	while (!(result[i] == '\n' || result[i] == '\0'))
		i++;
	if (result[i] == '\0')
		return (NULL);
	newbackup = ft_substr(result, i + 1, ft_strlen(result) - i);
	if (!newbackup)
		return (NULL);
	if (newbackup[0] == '\0')
	{
		free(newbackup);
		newbackup = NULL;
		return (NULL);
	}
	result[i + 1] = '\0';
	return (newbackup);
}

char	*get_next_line(int fd)
{
	char		*result;
	static char	*backup;

	if (fd < 0)
		return (NULL);
	if (!backup)
	{
		backup = ft_strdup("");
		if (!backup)
			return (NULL);
	}
	result = gnl_get_read(fd, &backup);
	if (!result || result[0] == '\0')
	{
		free(backup);
		backup = NULL;
		return (NULL);
	}
	backup = gnl_cutbynl(result);
	return (result);
}
