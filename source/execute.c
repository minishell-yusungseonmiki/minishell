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
	signal(SIGQUIT, SIG_DFL);
	if (proc_info->cmd_argv == NULL) //명령어가 없으면(리다이렉션만 존재)
		exit(0);
	else if (is_builtin(proc_info->cmd_argv)) //builtin 실행
	{
		execute_builtin(proc_info, proc_info->node_lst, 0);
		exit(g_exit_status); //자식 실행하고 종료시켜주는 코드 추가
	}
	else //execve 활용한 나머지 명령어
	{
		if (access(proc_info->cmd_path, X_OK) != 0)
		{
			write(2, "command not found\n", 19);
			exit(127);
		}
		else if (execve(proc_info->cmd_path, proc_info->cmd_argv, lst_to_envp(proc_info->denv, 0)) < 0)
		{
			perror(NULL);
			exit(1);
		}
	}
}

void	execute(t_list *proc_lst)
{
	t_list	*iter;
	t_proc_info	*proc_info;
	pid_t	pid;
	int		fd[2];
	int		prev_fd;

	print_on_signal();
	signal(SIGINT, sigint_child);
	if (execute_only_builtin(proc_lst))
		return ;
	iter = proc_lst;
	// prev_fd = -1;
	while (iter)
	{
		proc_info = iter->content;
		if (pipe(fd) < 0)
			perror("pipe error");
		pid = fork();
		if (pid < 0)
			perror("fork error");
		if (pid == 0)
		{
			// 파일 열고, 이전 파이프와 연결하기 ->모든 명령어 동일
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
		else
		{
			proc_info->child_pid = pid;
			// if (prev_fd >= 0)
				close(prev_fd);
			prev_fd = dup(fd[READ]);
			close(fd[WRITE]);
			close(fd[READ]);
		}
		iter = iter->next;
	}
	close(prev_fd);
	wait_process(proc_lst);
}

void	wait_process(t_list *proc_lst)
{
	t_proc_info	*last_proc;

	last_proc = ft_lstlast(proc_lst)->content;
	waitpid(last_proc->child_pid, &g_exit_status, 0);
		g_exit_status = g_exit_status >> 8;
	while (waitpid(0, NULL, 0) > 0)
		;
	// printf("%d\n", stat);
	// while (proc_lst)
	// {
	// 	pid = wait3(&stat, 0, NULL);
	// 	last_proc = ft_lstlast(proc_lst)->content;
	// 	if (pid == last_proc->child_pid && !is_builtin(last_proc->cmd_argv))
	// 		g_exit_status = stat >> 8;
	// 	proc_lst = proc_lst->next;
	// }
}
