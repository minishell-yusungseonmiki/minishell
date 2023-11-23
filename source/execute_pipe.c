#include "../include/minishell.h"

void	wait_process(int child_cnt)
{
	int	i;

	i = 0;
	while (i < child_cnt)
	{
		if (wait(NULL) < 0)
			perror("wait error");
		i++;
	}
}

void    exeute_pipe(t_list *proc_lst)
{
    pid_t   pid;
    int     fd[2];
    int     child_cnt;
	t_list	*before;

    child_cnt = 0;
	before = NULL;
    while (proc_lst)
    {
        if (pipe(fd) < 0)
			perror("pipe error");
        pid = fork();
        if (pid < 0)
            perror("fork error");
		if (pid == 0)
		{
			if (before && ((t_proc_info *)(proc_lst->content))->in_fd == STDIN_FILENO) //이전 노드가 있고, 현재 노드의 infile이 stdin일 경우
				dup2(((t_proc_info *)(before->content))->prev, STDIN_FILENO); //이전 노드 파이프의 읽기 종단을 stdin으로
			else                                                                 //이전 노드가 없거나, 현재 노드의 infile이 stdin이 아닐 경우
				dup2(((t_proc_info *)(proc_lst->content))->in_fd, STDIN_FILENO); //현재 노드의 infile을 stdin으로
			if (proc_lst->next != NULL && ((t_proc_info *)(proc_lst->content))->out_fd == STDOUT_FILENO) //현재 노드의 outfile이 stdout일 경우(단, 마지막이면 패스)
				dup2(fd[WRITE], STDOUT_FILENO); //파이프의 쓰기 종단을 stdout으로
			else
				dup2(((t_proc_info *)(proc_lst->content))->out_fd, STDOUT_FILENO); //현재 노드의 outfile을 stdout으로
			if (execve(((t_proc_info *)(proc_lst->content))->cmd_path, 
					((t_proc_info *)(proc_lst->content))->cmd_argv, 
					((t_proc_info *)(proc_lst->content))->envp) < 0)
			{
				ft_putstr_fd("command not found\n", 2);
				exit(1);
			}
			// error("execute failed");
		}
		else
		{
			// if (proc_lst->next == NULL)
				// close(fd[READ]);
			// else
				((t_proc_info *)(proc_lst->content))->prev = fd[READ];
				// dup2(fd[READ], ((t_proc_info *)(proc_lst->content))->prev);
			close(fd[WRITE]);
		}
		child_cnt++;
		before = proc_lst;
        proc_lst = proc_lst->next;
    }
	if (child_cnt)
		wait_process(child_cnt);
}
