#include "../include/minishell.h"

t_list	*make_proc_list(t_list *token_lst, t_list *denv)
{
	t_list	*proc_lst;
	t_list	*iter;

	proc_lst = NULL;
	iter = token_lst;
	while (token_lst)
	{
		if (iter == NULL || ((t_token *)(iter->content))->type == PIPE)
		{
			ft_lstadd_back(&proc_lst,
				ft_lstnew(init_proc_info(denv, make_node_list(token_lst, iter))));
			if (iter == NULL)
				break ;
			token_lst = iter->next;
		}
		iter = iter->next;
	}
	return (proc_lst);
}

t_proc_info	*init_proc_info(t_list *denv, t_list *node_lst)
{
	t_proc_info	*proc_info;

	proc_info = (t_proc_info *)malloc(sizeof(t_proc_info));
	if (proc_info == NULL)
		return (NULL);
	proc_info->denv = denv;
	proc_info->node_lst = node_lst;
	check_redirection(proc_info->node_lst);
	proc_info->cmd_argv = find_cmd_argv(proc_info->node_lst);
	proc_info->cmd_path = find_cmd_path(proc_info->cmd_argv, parse_envp(proc_info->denv));		
	proc_info->h_filename = NULL;
	proc_info->in_fd = 0;
	proc_info->out_fd = 1;
	proc_info->child_pid = 0;
	return (proc_info);
}
