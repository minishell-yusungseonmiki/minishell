#include "../include/minishell.h"

void	free_env(void	*env)
{
	t_env	*e;

	e = env;
	free(e->key);
	free(e->value);
}

void	free_proc_info(void *proc_info)
{
	t_proc_info	*proc;

	proc = proc_info;
	if (proc->h_filename)
	{
		unlink(proc->h_filename);
		free(proc->h_filename);
	}
	if (proc->cmd_argv)
		free_double_str(proc->cmd_argv);
	if (proc->cmd_path)
		free(proc->cmd_path);
	ft_lstclear(&proc->node_lst, free_node_list);
}

void	free_node_list(void	*node)
{
	t_node	*n;

	n = node;
	free(n->elem);
}

void	free_token(void *token)
{
	t_token	*t;

	t = token;
	free(t->elem);
}
