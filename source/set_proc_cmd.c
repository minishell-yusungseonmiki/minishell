#include "../include/minishell.h"

void	set_cmd_info(t_list *token_lst, t_list *proc_lst)
{
	t_list		*iter;
	t_proc_info	*proc_info;
	char		**find_path;

	iter = token_lst;
	while (token_lst && proc_lst)
	{
		if (iter == NULL || ((t_token *)(iter->content))->type == PIPE)
		{
			proc_info = proc_lst->content;
			proc_info->node_lst = separate_list_by_pipe(token_lst, iter);
			check_redirection(proc_info->node_lst);
			proc_info->cmd_argv = find_cmd_argv(proc_info->node_lst);
			//proc_info->cmd_path = find_cmd_path(proc_info->cmd_argv, parse_envp(proc_info->denv));

			find_path = parse_envp(proc_info->denv);
			proc_info->cmd_path = find_cmd_path(proc_info->cmd_argv, find_path);
			//free_double_str(find_path);
			if (iter == NULL)
				break ;
			token_lst = iter->next;
			proc_lst = proc_lst->next;
		}
		iter = iter->next;
	}
}

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
		node->before_blank = ((t_token *)(iter->content))->before_blank;
		ft_lstadd_back(&sub_lst, ft_lstnew(node));
		iter = iter->next;
	}
	return (sub_lst);
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
	if (is_builtin(cmd_argv))
		return (NULL);
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
	return (ft_strdup(cmd));
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
