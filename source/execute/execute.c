/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusung <yusung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 16:54:45 by seonmiki          #+#    #+#             */
/*   Updated: 2023/12/04 16:48:46 by yusung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	execute_only_builtin(t_list *proc_lst)
{
	t_proc_info	*proc;

	proc = proc_lst->content;
	if (proc_lst->next == NULL && is_builtin(proc->cmd_argv))
	{
		proc->in_fd = find_in_fd(proc->node_lst, proc->h_filename);
		proc->out_fd = find_out_fd(proc->node_lst);
		g_exit_status = 0;
		execute_builtin(proc, proc->node_lst, 1);
		return (1);
	}
	return (0);
}

void	execute_child(t_proc_info *proc_info)
{
	if (proc_info->cmd_argv == NULL)
		exit(0);
	else if (is_builtin(proc_info->cmd_argv))
	{
		execute_builtin(proc_info, proc_info->node_lst, 0);
		exit(g_exit_status);
	}
	else
	{
		if (execve(proc_info->cmd_path, proc_info->cmd_argv,
				lst_to_envp(proc_info->denv, 0)) < 0)
		{
			if (proc_info->cmd_argv[0]
				== ft_strchr(proc_info->cmd_argv[0], '/'))
				error(NOT_CMD, proc_info->cmd_argv[0]);
			else
				error(NOT_FILE, proc_info->cmd_argv[0]);
		}
	}
}

void	execute(t_list *proc_lst)
{
	t_list		*iter;
	t_proc_info	*proc_info;
	pid_t		pid;
	int			fd[2];
	int			prev_fd;

	print_on_signal();
	signal(SIGINT, sigint_last_child);
	signal(SIGQUIT, sigquit_last_child);
	if (execute_only_builtin(proc_lst))
		return ;
	prev_fd = -1;
	iter = proc_lst;
	while (iter)
	{
		proc_info = iter->content;
		pipe_open(fd);
		pid = make_fork();
		if (pid == 0)
			process_child(iter, fd, prev_fd, proc_lst);
		else
			process_parent(proc_info, fd, &prev_fd, pid);
		iter = iter->next;
	}
	close(prev_fd);
}
