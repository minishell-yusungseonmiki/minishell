#include "../include/minishell.h"

t_list	*make_node_list(t_list *start, t_list *end)
{
	t_list	*sub_lst;
	t_list	*iter;
	
	sub_lst = NULL;
	iter = start;
	while (iter != end)
	{
		t_node	*node = (t_node *)malloc(sizeof(t_node));
		node->elem = ft_strdup(((t_token *)(iter->content))->elem);
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

static int	count_arg(t_list *lst)
{
	int	cnt;

	cnt = 0;
	while (lst)
	{
		if (((t_node *)(lst->content))->visited == 0)
			cnt++;
		lst = lst->next;
	}
	return (cnt);
}

// 명령어 인자 리스트 2차원 배열로 할당하여 반환하기
char	**find_cmd_argv(t_list *lst)
{
	char	**find_arg;
	int		arg_cnt;
	int		i;

	arg_cnt = count_arg(lst);
	if (arg_cnt == 0) // 실행할 명령어가 없는 경우
		return (NULL);
	find_arg = (char **)malloc(sizeof(char *) * (arg_cnt + 1));
	i = 0;
	while (lst)
	{
		if (((t_node *)(lst->content))->visited == 0)
		{
			find_arg[i] = ft_strdup(((t_node *)(lst->content))->elem);
			i++;
		}
		lst = lst->next;
	}
	find_arg[i] = NULL;
	return (find_arg);
}

static char	*free_and_return(char **pathlist, char *result)
{
	free_double_str(pathlist);
	return (result);
}

// 명령어 경로 찾기
char	*find_cmd_path(char **cmd_argv, char **path_list)
{
	int		i;
	char	*tmp;
	char	*path;
	char	*cmd;

	if (cmd_argv == NULL || is_builtin(cmd_argv))
		return (free_and_return(path_list, NULL));
	cmd = cmd_argv[0];
	i = 0;
	while (path_list && path_list[i])
	{
		tmp = ft_strjoin(path_list[i], "/");
		path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(path, X_OK) == 0)
			return (free_and_return(path_list, path));
		free(path);
		i++;
	}
	return (free_and_return(path_list, ft_strdup(cmd)));
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
