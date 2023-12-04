/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusung <yusung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 16:14:07 by yusung            #+#    #+#             */
/*   Updated: 2023/12/04 17:07:54 by yusung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

static char	*make_result(char *ret, t_list *sub_lst, t_proc_info *proc, int i)
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
				tmp = ft_strjoin(ret, " ");
				free(ret);
				ret = tmp;
			}
			tmp = ft_strjoin(ret, (proc->cmd_argv)[i]);
			free(ret);
			ret = tmp;
			i++;
		}
		sub_lst = sub_lst->next;
	}
	return (ret);
}

static char	*add_newline(char *result)
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
