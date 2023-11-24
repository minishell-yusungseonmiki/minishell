#include "../include/minishell.h"

void	find_pipe(t_list *token_lst, char **envp)
{
	t_list	*iter;
	t_list	*sub_lst;
	int		child_cnt;
	t_proc_info	*proc;
	t_proc_info	*before;

	child_cnt = 0;
	iter = token_lst;
	before = NULL;
	while (token_lst != NULL)
	{
		if (iter == NULL)
		{
			sub_lst = separate_list_by_pipe(token_lst, iter);
			proc = set_proc_cmd_info(sub_lst, envp);
			if (proc->cmd_argv != NULL)
				child_cnt++;
			before = execute_cmd(sub_lst, proc, before, 0);
			ft_lstclear(&sub_lst, free);
			break ;
		}
		if (((t_token *)(iter->content))->type == PIPE)
		{
			sub_lst = separate_list_by_pipe(token_lst, iter);
			proc = set_proc_cmd_info(sub_lst, envp);
			if (proc->cmd_argv != NULL)
				child_cnt++;
			before = execute_cmd(sub_lst, proc, before, 1);
			ft_lstclear(&sub_lst, free);
			token_lst = iter->next;
		}
		iter = iter->next;
	}
	if (child_cnt)
		wait_process(child_cnt);
}

t_proc_info	*set_proc_cmd_info(t_list *sub_lst, char **envp)
{
	t_proc_info	*proc_info;

	proc_info = (t_proc_info *)malloc(sizeof(t_proc_info));
	if (proc_info == NULL)
		return (NULL);
	check_redirection(sub_lst);
	proc_info->cmd_argv = find_cmd_argv(sub_lst);
	proc_info->cmd_path = find_cmd_path(proc_info->cmd_argv, parse_envp(envp));
	proc_info->envp = envp;
	proc_info->in_fd = 0;
	proc_info->out_fd = 1;
	return (proc_info);
}

t_proc_info	*execute_cmd(t_list *sub_lst, t_proc_info *proc_info, t_proc_info *before, int last)
{
    pid_t   pid;
    int     fd[2];
	
	if (proc_info->cmd_path == NULL)
		return (proc_info);
	if (pipe(fd) < 0)
		perror("pipe error");
	pid = fork();
	if (pid < 0)
		perror("fork error");
	if (pid == 0)
	{
		proc_info->in_fd = find_in_fd(sub_lst);
		proc_info->out_fd = find_out_fd(sub_lst);
		if (before && proc_info->in_fd == STDIN_FILENO) //이전 노드가 있고, 현재 노드의 infile이 stdin일 경우
			dup2(before->prev, STDIN_FILENO); //이전 노드 파이프의 읽기 종단을 stdin으로
		else                                                                 //이전 노드가 없거나, 현재 노드의 infile이 stdin이 아닐 경우
			dup2(proc_info->in_fd, STDIN_FILENO); //현재 노드의 infile을 stdin으로
		if (last == 1 && proc_info->out_fd == STDOUT_FILENO) //현재 노드의 outfile이 stdout일 경우(단, 마지막이면 패스)
			dup2(fd[WRITE], STDOUT_FILENO); //파이프의 쓰기 종단을 stdout으로
		else
			dup2(proc_info->out_fd, STDOUT_FILENO); //현재 노드의 outfile을 stdout으로
		if (execve(proc_info->cmd_path, proc_info->cmd_argv, proc_info->envp) < 0)
		{
			ft_putstr_fd("command not found\n", 2);
			exit(1);
		}
	}
	else
	{
		proc_info->prev = fd[READ];
		close(fd[WRITE]);
	}
	return (proc_info);
}
