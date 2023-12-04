/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_proc_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusung <yusung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 15:30:24 by seonmiki          #+#    #+#             */
/*   Updated: 2023/12/04 16:38:42 by yusung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	check_redirection(t_list *lst)
{
	while (lst)
	{
		if (((t_node *)(lst->content))->type == IN
			|| ((t_node *)(lst->content))->type == OUT
			|| ((t_node *)(lst->content))->type == HEREDOC
			|| ((t_node *)(lst->content))->type == APPEND)
		{
			((t_node *)(lst->content))->visited = 1;
			((t_node *)(lst->next->content))->visited = 1;
		}
		lst = lst->next;
	}
}

int	get_arg_cnt(t_list *lst)
{
	t_list	*iter;
	int		arg_cnt;

	arg_cnt = 0;
	iter = lst;
	while (iter)
	{
		if (((t_node *)(iter->content))->visited == 0)
			arg_cnt++;
		iter = iter->next;
	}
	return (arg_cnt);
}

char	*free_and_return(char **pathlist, char *result)
{
	free_double_str(pathlist);
	return (result);
}
