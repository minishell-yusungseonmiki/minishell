#include "../include/minishell.h"

//구조체 내부의 값 출력(테스트용 함수)
void	print_proc_info(void *proc_info)
{
	t_proc_info *pi;

	pi = (t_proc_info *)proc_info;
	printf("in_fd : %d, out_fd : %d\n", pi->in_fd, pi->out_fd);

	printf("cmd_argv\n");
	int	i = 0;
	while (pi->cmd_argv && (pi->cmd_argv)[i])
	{
		printf("%s\n", (pi->cmd_argv)[i]);
		i++;
	}
	printf("cmd_path\n");
	printf("%s\n", pi->cmd_path);
	printf("\n");
}

// 정보 구조체 담는 전체적인 흐름
// token 순회하면서 파이프 만나거나 token 끝나면 sub_lst 만들기
// sub_lst를 순회하면서 proc_info_lst에 정보 담기
void	find_pipe(t_list *token_lst)
{
	t_list	*iter;
	t_list	*sub_lst;
	t_list	*proc_info_lst;

	proc_info_lst = NULL;
	iter = token_lst;
	while (token_lst != NULL)
	{
		if (iter == NULL)
		{
			sub_lst = separate_list_by_pipe(token_lst, iter);
			ft_lstadd_back(&proc_info_lst, ft_lstnew(set_proc_info(sub_lst)));
			ft_lstclear(&sub_lst, free);
			break ;
		}
		if (((t_token *)(iter->content))->type == PIPE)
		{
			sub_lst = separate_list_by_pipe(token_lst, iter);
			ft_lstadd_back(&proc_info_lst, ft_lstnew(set_proc_info(sub_lst)));
			ft_lstclear(&sub_lst, free);
			token_lst = iter->next;
		}
		iter = iter->next;
	}
	ft_lstiter(proc_info_lst, print_proc_info);
}

// 전달받은 인덱스(start, end)로 새로운 리스트 생성
 //start는 포함, end는 미포함
t_list	*separate_list_by_pipe(t_list *start, t_list *end)
{
	t_list	*sub_lst;
	t_list	*iter;
	
	sub_lst = NULL;
	iter = start;
	while (iter != end)
	{
		t_node	*node = (t_node *)malloc(sizeof(t_node));
		node->elem = ((t_token *)(iter->content))->elem;
		node->type = ((t_token *)(iter->content))->type;
		node->visited = 0;
		ft_lstadd_back(&sub_lst, ft_lstnew(node));
		iter = iter->next;
	}
	return sub_lst;
}

// 프로세스 하나의 구조체를 생성하고 정보를 담는다
t_proc_info	*set_proc_info(t_list *sub_lst)
{
	t_proc_info	*proc_info;

	proc_info = (t_proc_info *)malloc(sizeof(t_proc_info));
	if (proc_info == NULL)
		return (NULL);
	proc_info->in_fd = find_in_fd(sub_lst);
	proc_info->out_fd = find_out_fd(sub_lst);
	proc_info->cmd_argv = find_cmd_argv(sub_lst);
	proc_info->cmd_path = find_cmd_path((proc_info->cmd_argv)[0]);
	return (proc_info);
}

int	find_in_fd(t_list *lst)
{
	int		fd;
	char	*infile_name;

	fd = 0;
	while (lst)
	{
		if ((((t_node *)(lst->content))->type == IN)
			|| ((t_node *)(lst->content))->type == HEREDOC)
		{
			infile_name = ((t_node *)(lst->next->content))->elem;
			fd = open(infile_name, O_RDONLY);
			((t_node *)(lst->content))->visited = 1; // 방문 여부 확인(리다이렉션)
			((t_node *)(lst->next->content))->visited = 1; // 방문 여부 확인(파일이름/리미터)
		}
		lst = lst->next;
	}
	return (fd);
}

int	find_out_fd(t_list *lst)
{
	int		fd;
	char	*outfile_name;
	
	fd = 1;
	while (lst)
	{
		if ((((t_node *)(lst->content))->type) == OUT)
		{
			outfile_name = ((t_node *)(lst->next->content))->elem;
			fd = open(outfile_name, O_CREAT | O_RDWR | O_TRUNC, 0666);
			((t_node *)(lst->content))->visited = 1; // 방문 여부 확인(리다이렉션)
			((t_node *)(lst->next->content))->visited = 1; // 방문 여부 확인(파일이름/리미터)
		}
		if (((t_node *)(lst->content))->type == APPEND)
		{
			outfile_name = ((t_node *)(lst->next->content))->elem;
			fd = open(outfile_name, O_CREAT | O_RDWR | O_APPEND, 0666);
			((t_node *)(lst->content))->visited = 1; // 방문 여부 확인(리다이렉션)
			((t_node *)(lst->next->content))->visited = 1; // 방문 여부 확인(파일이름/리미터)
		}
		lst = lst->next;
	}
	return (fd);
}

// 명령어 인자 리스트 2차원 배열로 할당하여 반한화기
char	**find_cmd_argv(t_list *lst)
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
	iter = lst;
	while (iter)
	{
		if (((t_node *)(iter->content))->visited == 0)
		{
			find_arg[i] = ft_strdup(((t_node *)(iter->content))->elem);
			i++;
		}
		iter = iter->next;
	}
	find_arg[i] = NULL;
	return (find_arg);
}

// 명령어 경로 찾기
char	*find_cmd_path(char *cmd)
{
	// int		i;
	// char	*tmp;
	// char	*path;

	if (access(cmd, X_OK) == 0)
		return (cmd);
	// i = 0;
	// while (path_list && path_list[i])
	// {
	// 	tmp = ft_strjoin(path_list[i], "/");
	// 	path = ft_strjoin(tmp, cmd);
	// 	free(tmp);
	// 	if (access(path, X_OK) == 0)
	// 		return (path);
	// 	free(path);
	// 	i++;
	// }
	// error(CMD_ERR);
	return (NULL);
}