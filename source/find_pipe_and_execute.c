#include "../include/minishell.h"

// 토큰을 순회하면서 파이프를 만나면 리스트 생성 및 명령어 수행 함수를 호출한다
void	find_pipe_and_execute(t_list *token_lst, t_list *denv, t_list *hfile_lst)
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
		if (iter == NULL || ((t_token *)(iter->content))->type == PIPE)
		{
			sub_lst = separate_list_by_pipe(token_lst, iter);
			proc = set_proc_info(sub_lst, denv, hfile_lst);
			if (proc->cmd_argv != NULL)
				child_cnt++;
			if (iter == NULL)
			{
				if (!before && is_builtin(proc->cmd_argv)) // 빌트인 하나인 경우에만 child_cnt줄이기
					child_cnt--;
				before = execute_pipe(sub_lst, proc, before, 0);
			}
			else
				before = execute_pipe(sub_lst, proc, before, 1);
			ft_lstclear(&sub_lst, free);
			if (iter == NULL)
				break ;
			token_lst = iter->next;
			hfile_lst = hfile_lst->next;
		}
		iter = iter->next;
	}
	if (child_cnt)
		wait_process(child_cnt, before->child_pid);
}

// 자식 프로세스 및 파이프를 생성하고 명령어를 실행
// fork 이후에 자식 프로세스에서 리다이렉션 파일을 열어준다
// 반환값 : 현재 실행한 파이프의 구조체 (before로 이용하기 위해서)
t_proc_info	*execute_pipe(t_list *sub_lst, t_proc_info *proc_info, t_proc_info *before, int last)
{
    pid_t   pid;
    int     fd[2];
	// printf("-----------\n");
	// print_proc_info(proc_info);
	if (proc_info->cmd_argv == NULL)
	{
		proc_info->in_fd = find_in_fd(sub_lst, proc_info->h_filename);
		proc_info->out_fd = find_out_fd(sub_lst);
		return (proc_info);
	}
	if (!before && is_builtin(proc_info->cmd_argv) && last == 0) // 빌트인 하나인 경우 -> before, last 모두 확인 필요
	{
		proc_info->in_fd = find_in_fd(sub_lst, proc_info->h_filename);
		proc_info->out_fd = find_out_fd(sub_lst);
		execute_builtin(proc_info, sub_lst, 1);
		return (proc_info);	
	}
	if (pipe(fd) < 0)
		perror("pipe error");
	pid = fork();
	if (pid < 0)
		perror("fork error");
	if (pid == 0)
	{
		proc_info->in_fd = find_in_fd(sub_lst, proc_info->h_filename);
		proc_info->out_fd = find_out_fd(sub_lst);
		if (before && proc_info->in_fd == STDIN_FILENO) //이전 노드가 있고, 현재 노드의 infile이 stdin일 경우
			dup2(before->prev, STDIN_FILENO); //이전 노드 파이프의 읽기 종단을 stdin으로
		else                                                                 //이전 노드가 없거나, 현재 노드의 infile이 stdin이 아닐 경우
			dup2(proc_info->in_fd, STDIN_FILENO); //현재 노드의 infile을 stdin으로
		if (last == 1 && proc_info->out_fd == STDOUT_FILENO) //현재 노드의 outfile이 stdout일 경우(단, 마지막이면 패스)
			dup2(fd[WRITE], STDOUT_FILENO); //파이프의 쓰기 종단을 stdout으로
		else
			dup2(proc_info->out_fd, STDOUT_FILENO); //현재 노드의 outfile을 stdout으로
		if (is_builtin(proc_info->cmd_argv))
		{
			execute_builtin(proc_info, sub_lst, 0);
			exit(0); //자식 실행하고 종료시켜주는 코드 추가
		}
		else
		{
			if (access(proc_info->cmd_path, X_OK) != 0)
			{
				write(2, "command not found\n", 19);
				exit(127);
			}
			else if (execve(proc_info->cmd_path, proc_info->cmd_argv, proc_info->envp) < 0)
			{
				perror(NULL);
				exit(1);
			}
		}
	}
	else
	{
		proc_info->child_pid = pid;
		proc_info->prev = fd[READ];
		close(fd[WRITE]);
	}
	return (proc_info);
}

void	wait_process(int child_cnt, pid_t child_pid)
{
	int	i;

	i = 0;
	while (i < child_cnt - 1)
	{
		if (wait(NULL) < 0)
			perror("wait error");
		i++;
	}
	waitpid(child_pid, &exit_status, 0);
	exit_status = exit_status >> 8;
}
