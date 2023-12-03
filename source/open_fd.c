/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonmiki <seonmiki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 17:33:20 by seonmiki          #+#    #+#             */
/*   Updated: 2023/12/03 17:45:36 by seonmiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	open_file(char *filename, int option)
{
	int	fd;

	fd = -1;
	if (option == 0) // <, <<
		fd = open(filename, O_RDONLY);
	else if (option == 1) // >
		fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0666);
	else if (option == 2) // >>
		fd = open(filename, O_CREAT | O_RDWR | O_APPEND, 0666);
	if (fd < 0)
	{
		perror(NULL);
		exit(1);
	}
	return (fd);
}

int	find_in_fd(t_list *lst, char *h_filename)
{
	int		fd;
	char	*infile_name;

	fd = 0;
	while (lst)
	{
		if (((t_node *)(lst->content))->type == IN)
		{
			infile_name = ((t_node *)(lst->next->content))->elem;
			fd = open(infile_name, O_RDONLY);
			if (fd < 0)
				error(OPEN_FAILED);
		}
		else if (((t_node *)(lst->content))->type == HEREDOC)
		{
			fd = open(h_filename, O_RDONLY);
			if (fd < 0)
				error(OPEN_FAILED);
		}
		lst = lst->next;
	}
	return (fd);
}

int	find_out_fd(t_list *lst)
{
	int		fd;
	char	*outfile_name;
	
	fd = 1;
	while (lst)
	{
		if ((((t_node *)(lst->content))->type) == OUT)
		{
			outfile_name = ((t_node *)(lst->next->content))->elem;
			fd = open(outfile_name, O_CREAT | O_RDWR | O_TRUNC, 0666);
			if (fd < 0)
				error(OPEN_FAILED);
		}
		if (((t_node *)(lst->content))->type == APPEND)
		{
			outfile_name = ((t_node *)(lst->next->content))->elem;
			fd = open(outfile_name, O_CREAT | O_RDWR | O_APPEND, 0666);
			if (fd < 0)
				error(OPEN_FAILED);
		}
		lst = lst->next;
	}
	return (fd);
}
