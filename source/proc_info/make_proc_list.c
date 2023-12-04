/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_proc_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusung <yusung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 17:33:15 by seonmiki          #+#    #+#             */
/*   Updated: 2023/12/04 16:56:44 by yusung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_proc_info	*init_proc_info(t_list **denv, t_list *node_lst)
{
	t_proc_info	*proc;

	proc = (t_proc_info *)malloc(sizeof(t_proc_info));
	if (proc == NULL)
		return (NULL);
	proc->denv = *denv;
	proc->node_lst = node_lst;
	check_redirection(proc->node_lst);
	proc->cmd_argv = find_cmd_argv(proc->node_lst);
	proc->cmd_path = find_cmd_path(proc->cmd_argv, parse_envp(proc->denv));
	proc->h_filename = NULL;
	proc->in_fd = 0;
	proc->out_fd = 1;
	proc->child_pid = 0;
	return (proc);
}

t_list	*make_proc_list(t_list *tk_lst, t_list **denv)
{
	t_list	*proc_lst;
	t_list	*iter;

	proc_lst = NULL;
	iter = tk_lst;
	while (tk_lst)
	{
		if (iter == NULL || ((t_token *)(iter->content))->type == PIPE)
		{
			ft_lstadd_back(&proc_lst,
				ft_lstnew(init_proc_info(denv, make_node_list(tk_lst, iter))));
			if (iter == NULL)
				break ;
			tk_lst = iter->next;
		}
		iter = iter->next;
	}
	return (proc_lst);
}
