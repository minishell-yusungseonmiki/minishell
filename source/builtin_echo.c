/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusung <yusung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 16:14:07 by yusung            #+#    #+#             */
/*   Updated: 2023/11/29 16:55:18 by yusung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	is_same(char *node, char *cmd)
{
	if (ft_strncmp(node, cmd, ft_strlen(cmd)) == 0
		&& ft_strlen(cmd) == ft_strlen(node))
		return (1);
	return (0);
}

char	*make_result(char *result, t_list *sub_lst, t_proc_info *proc, int i)
{
	char	*tmp;
	int		start;

	start = i;
	while (sub_lst && (proc->cmd_argv)[i])
	{
		if (is_same(((t_node *)(sub_lst->content))->elem, (proc->cmd_argv)[i]))
		{
			if (((t_node *)(sub_lst->content))->before_blank == 1 && i != start)
			{
				tmp = ft_strjoin(result, " ");
				free(result);
				result = tmp;
			}
			tmp = ft_strjoin(result, (proc->cmd_argv)[i]);
			free(result);
			result = tmp;
			i++;
		}
		sub_lst = sub_lst->next;
	}
	return (result);
}

char	*add_newline(char *result)
{
	char	*tmp;

	tmp = ft_strjoin(result, "\n");
	free(result);
	result = tmp;
	return (result);
}

void	execute_echo(t_proc_info *proc, t_list *sub_lst)
{
	int		i;
	int		option;
	char	*result;

	i = 1;
	sub_lst = sub_lst->next;
	option = 0;
	while (sub_lst && (proc->cmd_argv)[i])
	{
		if (is_same(((t_node *)(sub_lst->content))->elem, (proc->cmd_argv)[i]))
		{
			if ((proc->cmd_argv)[i] == 0 || is_option((proc->cmd_argv)[i]) == 0)
				break ;
			option = 1;
			i++;
		}
		sub_lst = sub_lst->next;
	}
	result = ft_strdup("");
	result = make_result(result, sub_lst, proc, i);
	if (option == 0)
		result = add_newline(result);
	ft_putstr_fd(result, proc->out_fd);
	free(result);
}
