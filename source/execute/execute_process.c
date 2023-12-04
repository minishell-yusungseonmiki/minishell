/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusung <yusung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 15:44:30 by seonmiki          #+#    #+#             */
/*   Updated: 2023/12/04 16:38:03 by yusung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	process_child(t_list *iter, int fd[2], int prev_fd, t_list *proc_lst)
{
	t_proc_info	*proc_info;

	signal(SIGQUIT, SIG_DFL);
	proc_info = iter->content;
	proc_info->in_fd = find_in_fd(proc_info->node_lst, proc_info->h_filename);
	proc_info->out_fd = find_out_fd(proc_info->node_lst);
	if (iter != proc_lst && proc_info->in_fd == STDIN_FILENO)
		dup2(prev_fd, STDIN_FILENO);
	else
		dup2(proc_info->in_fd, STDIN_FILENO);
	if (iter->next != NULL && proc_info->out_fd == STDOUT_FILENO)
		dup2(fd[WRITE], STDOUT_FILENO);
	else
		dup2(proc_info->out_fd, STDOUT_FILENO);
	close(fd[READ]);
	close(fd[WRITE]);
	execute_child(proc_info);
}

void	process_parent(t_proc_info *proc_info, int fd[2], int *prev_fd, int pid)
{
	proc_info->child_pid = pid;
	close(*prev_fd);
	*prev_fd = dup(fd[READ]);
	close(fd[WRITE]);
	close(fd[READ]);
}

void	wait_process(t_list *proc_lst)
{
	t_proc_info	*last_proc;
	int			tmp;

	last_proc = ft_lstlast(proc_lst)->content;
	waitpid(last_proc->child_pid, &tmp, 0);
		tmp = tmp >> 8;
	signal(SIGINT, sigint_child);
	signal(SIGQUIT, sigquit_child);
	while (waitpid(0, NULL, 0) > 0)
		;
	if (g_exit_status == -1)
		g_exit_status = 1;
	else if (g_exit_status == -130)
		g_exit_status = 130;
	else if (g_exit_status == -131)
		g_exit_status = 131;
	else
		g_exit_status = tmp;
}
