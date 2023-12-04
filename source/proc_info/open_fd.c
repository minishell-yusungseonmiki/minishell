/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusung <yusung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 17:33:20 by seonmiki          #+#    #+#             */
/*   Updated: 2023/12/04 16:38:47 by yusung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
				error(FILE_ERROR, infile_name);
		}
		else if (((t_node *)(lst->content))->type == HEREDOC)
		{
			fd = open(h_filename, O_RDONLY);
			if (fd < 0)
				error(FILE_ERROR, infile_name);
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
				error(FILE_ERROR, outfile_name);
		}
		if (((t_node *)(lst->content))->type == APPEND)
		{
			outfile_name = ((t_node *)(lst->next->content))->elem;
			fd = open(outfile_name, O_CREAT | O_RDWR | O_APPEND, 0666);
			if (fd < 0)
				error(FILE_ERROR, outfile_name);
		}
		lst = lst->next;
	}
	return (fd);
}
