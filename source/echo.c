#include "../include/minishell.h"

// 해당 노드가 -n 옵션으로 판단되는지를 확인
static int	is_option(char *s)
{
	int	i;

	if (ft_strncmp(s, "-n", 2) != 0)
		return (0);
	i = 2;
	while (s[i])
	{
		if (s[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void    execute_echo(t_proc_info *proc, t_list *sub_lst)
{
	// printf("my echo\n");
	int		i;
	int		option;
	char	*result;
	char	*tmp;
	int		start;
	

	i = 1;
	sub_lst = sub_lst->next;
	option = 0;
	result = "";
	while (sub_lst && (proc->cmd_argv)[i])
	{
		// printf("%s %s\n", ((t_node *)(sub_lst->content))->elem, (proc->cmd_argv)[i]);
		if (ft_strncmp(((t_node *)(sub_lst->content))->elem, (proc->cmd_argv)[i], ft_strlen((proc->cmd_argv)[i])) == 0
			&& ft_strlen((proc->cmd_argv)[i]) == ft_strlen(((t_node *)(sub_lst->content))->elem))
		{
			if ((proc->cmd_argv)[i] == 0 || is_option((proc->cmd_argv)[i]) == 0)
				break ;
			option = 1;
			i++;
		}
		sub_lst = sub_lst->next;
	}
	start = i;
	while (sub_lst && (proc->cmd_argv)[i])
	{
		// printf("%s %s\n", ((t_node *)(sub_lst->content))->elem, (proc->cmd_argv)[i]);
		if (ft_strncmp(((t_node *)(sub_lst->content))->elem, (proc->cmd_argv)[i], ft_strlen((proc->cmd_argv)[i])) == 0
			&& ft_strlen((proc->cmd_argv)[i]) == ft_strlen(((t_node *)(sub_lst->content))->elem))
		{
			result = ft_strjoin(result, (proc->cmd_argv)[i]);
			i++;
			if (((t_node *)(sub_lst->content))->before_blank == 1 && i != start)
			{
				result = ft_strjoin(result, " ");
			}
		}
		sub_lst = sub_lst->next;
	}
	if (option == 0)
	{
		tmp = ft_strjoin(result, "\n");
		result = tmp;
	}
	ft_putstr_fd(result, proc->out_fd);
}
