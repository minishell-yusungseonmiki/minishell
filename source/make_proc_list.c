#include "../include/minishell.h"

t_list	*make_proc_list(t_list *token_lst, char **envp, t_list *denv)
{
	t_list	*proc_lst;

	proc_lst = NULL;
	while (token_lst)
	{
		if (((t_token *)(token_lst->content))->type == PIPE)
			ft_lstadd_back(&proc_lst, ft_lstnew(init_proc_info(envp, denv)));
		token_lst = token_lst->next;
	}
	ft_lstadd_back(&proc_lst, ft_lstnew(init_proc_info(envp, denv)));
	return (proc_lst);
}

t_proc_info	*init_proc_info(char **envp, t_list *denv)
{
	t_proc_info	*proc_info;

	proc_info = (t_proc_info *)malloc(sizeof(t_proc_info));
	if (proc_info == NULL)
		return (NULL);
	proc_info->envp = envp;
	proc_info->denv = denv;
	proc_info->h_filename = NULL;
	proc_info->in_fd = 0;
	proc_info->out_fd = 1;
	proc_info->cmd_argv = NULL;
	proc_info->cmd_path = NULL;
	proc_info->child_pid = 0;
	return (proc_info);
}