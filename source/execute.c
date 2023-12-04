/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonmiki <seonmiki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 16:54:45 by seonmiki          #+#    #+#             */
/*   Updated: 2023/12/03 18:55:18 by seonmiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	execute_only_builtin(t_list *proc_lst)
{
	t_proc_info	*proc;

	proc = proc_lst->content;
	if (proc_lst->next == NULL && is_builtin(proc->cmd_argv)) //only builtin
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
	// signal(SIGQUIT, SIG_DFL);
	if (proc_info->cmd_argv == NULL) //명령어가 없으면(리다이렉션만 존재)
		exit(0);
	else if (is_builtin(proc_info->cmd_argv)) //builtin 실행
	{
		execute_builtin(proc_info, proc_info->node_lst, 0);
		exit(g_exit_status); //자식 실행하고 종료시켜주는 코드 추가
	}
	else //execve 활용한 나머지 명령어
	{
		if (execve(proc_info->cmd_path, proc_info->cmd_argv, lst_to_envp(proc_info->denv, 0)) < 0)
		{
			if (proc_info->cmd_argv[0] == ft_strchr(proc_info->cmd_argv[0], '/'))
				error(NOT_CMD, proc_info->cmd_argv[0]);
			else
				error(NOT_FILE, proc_info->cmd_argv[0]);
		}
	}
}

void	process_child(t_list *iter, int fd[2], int prev_fd, t_list *proc_lst)
{
	t_proc_info	*proc_info;

	signal(SIGQUIT, SIG_DFL);
	proc_info = iter->content;
	proc_info->in_fd = find_in_fd(proc_info->node_lst, proc_info->h_filename);
	proc_info->out_fd = find_out_fd(proc_info->node_lst);
	if (iter != proc_lst && proc_info->in_fd == STDIN_FILENO) //이전 노드가 있고, 현재 노드의 infile이 stdin일 경우
		dup2(prev_fd, STDIN_FILENO); //이전 노드 파이프의 읽기 종단을 stdin으로
	else                                                                 //이전 노드가 없거나, 현재 노드의 infile이 stdin이 아닐 경우
		dup2(proc_info->in_fd, STDIN_FILENO); //현재 노드의 infile을 stdin으로
	if (iter->next != NULL && proc_info->out_fd == STDOUT_FILENO) //현재 노드의 outfile이 stdout일 경우(단, 마지막이면 패스)
		dup2(fd[WRITE], STDOUT_FILENO); //파이프의 쓰기 종단을 stdout으로
	else
		dup2(proc_info->out_fd, STDOUT_FILENO); //현재 노드의 outfile을 stdout으로
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

void	execute(t_list *proc_lst)
{
	t_list	*iter;
	t_proc_info	*proc_info;
	pid_t	pid;
	int		fd[2];
	int		prev_fd;

	print_on_signal();
	if (execute_only_builtin(proc_lst))
		return ;
	prev_fd = -1;
	iter = proc_lst;
	signal(SIGINT, sigint_last_child);
	signal(SIGQUIT, sigquit_last_child);
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
	wait_process(proc_lst);
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
	if (g_exit_status == -1) // heredoc sigint
		g_exit_status = 1;
	else if (g_exit_status == -130) //child sigint
		g_exit_status = 130;
	else if (g_exit_status == -131) //child sigquit
		g_exit_status = 131;
	else // 마지막 자식 종료코드
		g_exit_status = tmp;
}
