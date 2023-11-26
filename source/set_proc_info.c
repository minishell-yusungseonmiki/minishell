#include "../include/minishell.h"

//구조체 내부의 값 출력(테스트용 함수)
void	print_proc_info(t_proc_info *pi)
{
	// t_proc_info *pi;

	// pi = (t_proc_info *)proc_info;
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

// 구조체 할당항 프로세스 정보 담기
// 파일은 열지 않고 0,1로 초기화 시켜둔다
t_proc_info	*set_proc_info(t_list *sub_lst, t_list *denv, t_list *hfile_lst)
{
	t_proc_info	*proc_info;

	proc_info = (t_proc_info *)malloc(sizeof(t_proc_info));
	if (proc_info == NULL)
		return (NULL);
	check_redirection(sub_lst);
	proc_info->cmd_argv = find_cmd_argv(sub_lst);
	proc_info->cmd_path = find_cmd_path(proc_info->cmd_argv, parse_envp(denv));
	proc_info->envp = lst_to_envp(denv);
	if (is_builtin(proc_info->cmd_path))
		proc_info->denv = denv;
	else
		proc_info->denv = NULL;
	proc_info->in_fd = 0;
	proc_info->out_fd = 1;
	proc_info->h_filename = hfile_lst->content;
	return (proc_info);
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

// cmd_argv 담기 전에 리다이렉션은 visited 1로 설정해두기
void	check_redirection(t_list *lst)
{
	while (lst)
	{
		if (((t_node *)(lst->content))->type == IN
			|| ((t_node *)(lst->content))->type == OUT
			|| ((t_node *)(lst->content))->type == HEREDOC
			|| ((t_node *)(lst->content))->type == APPEND
		)
		{
			((t_node *)(lst->content))->visited = 1; // 방문 여부 확인(리다이렉션)
			((t_node *)(lst->next->content))->visited = 1; // 방문 여부 확인(파일이름/리미터)
		}
		lst = lst->next;
	}
}

int	find_in_fd(t_list *lst, char *h_filename)
{
	int		fd;
	char	*infile_name;

	fd = 0;
	while (lst)
	{
		if (((t_node *)(lst->content))->type == IN)
		{
			infile_name = ((t_node *)(lst->next->content))->elem;
			fd = open(infile_name, O_RDONLY);
			if (fd < 0)
			{
				perror(NULL);
				exit(1);
			}
		}
		else if (((t_node *)(lst->content))->type == HEREDOC)
		{
			fd = open(h_filename, O_RDONLY);
			if (fd < 0)
			{
				perror(NULL);
				exit(1);
			}
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
			if (fd < 0)
			{
				perror(NULL);
				exit(1);
			}
		}
		if (((t_node *)(lst->content))->type == APPEND)
		{
			outfile_name = ((t_node *)(lst->next->content))->elem;
			fd = open(outfile_name, O_CREAT | O_RDWR | O_APPEND, 0666);
			if (fd < 0)
			{
				perror(NULL);
				exit(1);
			}
		}
		lst = lst->next;
	}
	return (fd);
}

// 명령어 인자 리스트 2차원 배열로 할당하여 반환하기
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
	if (arg_cnt == 0) // 실행할 명령어가 없는 경우
		return (NULL);
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
char	*find_cmd_path(char **cmd_argv, char **path_list)
{
	int		i;
	char	*tmp;
	char	*path;
	char	*cmd;

	if (cmd_argv == NULL)
		return (NULL);
	cmd = cmd_argv[0];
	i = 0;
	while (path_list && path_list[i])
	{
		tmp = ft_strjoin(path_list[i], "/");
		path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (cmd);
}

// 환경변수 path parsing하기
char	**parse_envp(t_list *denv)
{
	char	**path_list;

	path_list = NULL;
	while (denv)
	{
		if (ft_strncmp(((t_env *)(denv->content))->key, "PATH", 4) == 0
			&& ft_strlen(((t_env *)(denv->content))->key) == 4)
		{
			path_list = ft_split(((t_env *)(denv->content))->value, ':');
			break ;
		}
		denv = denv->next;
	}
	return (path_list);
}
