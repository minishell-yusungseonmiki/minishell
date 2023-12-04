/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_proc_info.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusung <yusung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 17:33:09 by seonmiki          #+#    #+#             */
/*   Updated: 2023/12/04 16:55:44 by yusung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_list	*make_node_list(t_list *start, t_list *end)
{
	t_list	*sub_lst;
	t_list	*iter;
	t_node	*node;

	sub_lst = NULL;
	iter = start;
	while (iter != end)
	{
		node = (t_node *)malloc(sizeof(t_node));
		node->elem = ft_strdup(((t_token *)(iter->content))->elem);
		node->type = ((t_token *)(iter->content))->type;
		node->visited = 0;
		node->before_blank = ((t_token *)(iter->content))->before_blank;
		ft_lstadd_back(&sub_lst, ft_lstnew(node));
		iter = iter->next;
	}
	return (sub_lst);
}

char	**find_cmd_argv(t_list *lst)
{
	char	**find_arg;
	int		arg_cnt;
	int		i;

	arg_cnt = get_arg_cnt(lst);
	if (arg_cnt == 0)
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
