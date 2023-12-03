/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonmiki <seonmiki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 16:56:00 by seonmiki          #+#    #+#             */
/*   Updated: 2023/12/03 17:32:23 by seonmiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	run_heredoc(t_list *cur, char *h_filename)
{
	int		fd;
	char	*tmp;
	char	*limit;

	limit = ((t_token *)(cur->next->content))->elem;
	fd = open(h_filename, O_RDWR | O_CREAT | O_TRUNC, 0666);
	tmp = get_next_line(0);
	while (tmp)
	{
		if (!ft_strncmp(limit, tmp, ft_strlen(limit))
			&& (ft_strlen(limit) == ft_strlen(tmp) - 1))
		{
			free(tmp);
			break ;
		}
		write(fd, tmp, ft_strlen(tmp));
		free(tmp);
		tmp = get_next_line(0);
	}
	close(fd);
}

static char	*check_node_lst(t_list *proc_lst, int *cnt, int *flag, char *filename)
{
	t_list	*iter;
	char	*tmp;
	char	*h_filename;

	h_filename = NULL;
	iter = ((t_proc_info *)(proc_lst->content))->node_lst;
	while (iter)
	{
		if (((t_token *)(iter->content))->type == HEREDOC)
		{
			if (*flag == 0)
			{
				*cnt += 1;
				tmp = ft_itoa(*cnt);
				h_filename = ft_strjoin(filename, tmp);
				free(tmp);
			}
			*flag = 1;
			run_heredoc(iter, h_filename);
		}
		iter = iter->next;
	}
	return (h_filename);
}

static void	make_heredoc(t_list *proc_lst)
{
	char	*h_filename;
	char	*filename;
	int		cnt;
	int		flag;

	cnt = 0;
	filename = "/tmp/here_doc";
	while (proc_lst)
	{
		flag = 0;
		h_filename = check_node_lst(proc_lst, &cnt, &flag, filename);
		if (flag)
			((t_proc_info *)(proc_lst->content))->h_filename = h_filename;
		else
			((t_proc_info *)(proc_lst->content))->h_filename = NULL; 
		proc_lst = proc_lst->next;
	}
}

void	heredoc(t_list *proc_lst)
{
	int		backup_fd;

	backup_fd = dup(STDIN_FILENO);
	signal(SIGINT, sigint_heredoc);
	make_heredoc(proc_lst);
	dup2(backup_fd, STDIN_FILENO);
	close(backup_fd);
	signal(SIGINT, sigint_handler);
}
