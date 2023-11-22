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

    child_cnt = 0;
    while (proc_lst)
    {
		if (((t_proc_info *)(proc_lst->content))->cmd_path == NULL)
		{
			printf("not exist\n");
			return;
		}
        if (pipe(fd) < 0)
			perror("pipe error");
        pid = fork();
        if (pid < 0)
            perror("fork error");
		if (pid == 0)
		{
			dup2(((t_proc_info *)(proc_lst->content))->prev, ((t_proc_info *)(proc_lst->content))->in_fd);
			if (proc_lst->next == NULL)
				dup2(((t_proc_info *)(proc_lst->content))->out_fd, STDOUT_FILENO);
			else
				dup2(fd[WRITE], ((t_proc_info *)(proc_lst->content))->out_fd);
			execve(((t_proc_info *)(proc_lst->content))->cmd_path, 
					((t_proc_info *)(proc_lst->content))->cmd_argv, 
					((t_proc_info *)(proc_lst->content))->envp);
			// error("execute failed");
		}
		else
		{
			dup2(fd[READ], ((t_proc_info *)(proc_lst->content))->prev);
			close(fd[WRITE]);
		}
		child_cnt++;
        proc_lst = proc_lst->next;
    }
	if (child_cnt)
		wait_process(child_cnt);
}
