#include "../include/minishell.h"

void	set_process_info(t_list *token_lst)
{
	t_list	*node_lst;
	t_proc_info	**proc_lst;

	node_lst = make_node_list(token_lst);
	proc_lst = make_process_info_list(node_lst);
	
}


// process information 초기화
void	init_proc_info(t_proc_info *proc_info)
{
	proc_info->in_fd = 0;
	proc_info->out_fd = 1;
	proc_info->cmd_argv = NULL;
	proc_info->cmd_path = NULL;
}

// 파이프 기준으로 새로운 리스트 만들기(따옴표 제거 및 환경변수 확장 작업 추가 필요)
t_list	*make_node_list(t_list *token_lst)
{
	t_token	*token;
	t_node	*node;
	t_list	*node_lst;

	while (token_lst)
	{
		token = (t_token *)(token_lst->content); // 처음 파싱한 토큰
		node = (t_node *)malloc(sizeof(t_node)); // 새로운 노드(따옴표 제거, 환경변수 확장된 노드) 일단 지금은 토큰 그대로 받아오기
		node->elem = token->elem;
		node->type = token->type;
		node->visited = 0;
		ft_lstadd_back(node_lst, node);
		token_lst = token_lst->next;
	}
	return node_lst;
}

// 프로세스의 정보 담은 구조체 리스트 만들기
t_proc_info	**make_process_info_list(t_list *lst)
{
	t_proc_info	**proc_lst;
	int			pipe_cnt;
	int			i;
	t_list		*iter;

	pipe_cnt = 0;
	iter = lst;
	while (iter)
	{
		if (((t_node *)(iter->content))->type == PIPE)
			pipe_cnt++;
		iter = iter->next;
	}
	proc_lst = (t_proc_info **)malloc(sizeof(t_proc_info *) * (pipe_cnt + 1));
	i = 0;
	iter = lst;
	while (i < pipe_cnt)
	{
		proc_lst[i] = (t_proc_info *)malloc(sizeof(t_proc_info));
		init_proc_info(proc_lst[i]);
		find_in_out(iter, proc_lst[i]);
		find_cmd_argv(iter, proc_lst[i]);
		i++;
		while (iter)
		{
			if (((t_node *)(iter->content))->type == PIPE)
				break ;
			iter = iter->next;
		}
		iter = iter->next;
	}
	return proc_lst;
}

// 하나의 파이프 내부 순회하면서 infile, outfile 결정하기
void	find_in_out(t_list *lst, t_proc_info *proc_info)
{
	char	*infile_name;
	char	*outfile_name;
	
	while (lst)
	{
		if ((((t_node *)(lst->content))->type == IN)
			|| ((t_node *)(lst->content))->type == HEREDOC)
		{
			infile_name = ((t_node *)(lst->next->content))->elem;
			proc_info->in_fd = open(infile_name, O_RDONLY);
			((t_node *)(lst->content))->visited = 1; // 방문 여부 확인(리다이렉션)
			((t_node *)(lst->next->content))->visited = 1; // 방문 여부 확인(파일이름/리미터)
		}
		if ((((t_node *)(lst->content))->type == OUT))
		{
			outfile_name = ((t_node *)(lst->next->content))->elem;
			proc_info->out_fd = open(outfile_name, O_CREAT | O_RDWR | O_TRUNC, 0666);
			((t_node *)(lst->content))->visited = 1; // 방문 여부 확인(리다이렉션)
			((t_node *)(lst->next->content))->visited = 1; // 방문 여부 확인(파일이름/리미터)
		}
		if (((t_node *)(lst->content))->type == APPEND)
		{
			outfile_name = ((t_node *)(lst->next->content))->elem;
			proc_info->out_fd = open(outfile_name, O_CREAT | O_RDWR | O_APPEND, 0666);
			((t_node *)(lst->content))->visited = 1; // 방문 여부 확인(리다이렉션)
			((t_node *)(lst->next->content))->visited = 1; // 방문 여부 확인(파일이름/리미터)
		}
		lst = lst->next;
	}
}

// 명령어 인자들 찾아서 넣기
void	find_cmd_argv(t_list *lst, t_proc_info *proc_info)
{
	char	**find_arg;
	int		arg_cnt;
	t_list	*iter;
	int		i;

	arg_cnt = 0;
	iter = lst;
	while (iter)
	{
		if (((t_node *)(iter->content))->visited == 0)
			arg_cnt++;
		iter = iter->next;
	}
	find_arg = (char **)malloc(sizeof(char *) * (arg_cnt + 1));
	i = 0;
	while (iter)
	{
		if (((t_node *)(iter->content))->visited == 0)
		{
			find_arg[i] = ft_strdup(((t_node *)(iter->content))->elem);
			i++;
		}
		iter = iter->next;
	}
	proc_info->cmd_argv = find_arg;
}