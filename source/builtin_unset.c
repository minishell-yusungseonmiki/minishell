/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonmiki <seonmiki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 16:50:42 by seonmiki          #+#    #+#             */
/*   Updated: 2023/12/03 18:28:16 by seonmiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	unset_keyvalue(t_list **denv, char *key)
{
	t_list	*iter;
	t_list	*before;

	if (!denv)
		return ;
	iter = *denv;
	before = NULL;
	while (iter)
	{
		if (!ft_strncmp(((t_env *)(iter->content))->key, key, ft_strlen(key))
		&& ft_strlen(((t_env *)(iter->content))->key) == ft_strlen(key))
		{
			if (before)
				before->next = iter->next;
			else
				*denv = iter->next;
			free(((t_env *)(iter->content))->key);
			free(((t_env *)(iter->content))->value);
			free(iter->content);
			free(iter);
			return ;
		}
		before = iter;
		iter = iter->next;
	}
}

void	execute_unset(char **cmd_argv, t_list **denv)
{
	int		i;

	i = 1;
	while (cmd_argv[i])
	{
		if (ft_isdigit(cmd_argv[i][0]) || ft_strchr(cmd_argv[i], '='))
		{
			write(2, "unset: '", 9);
			write(2, cmd_argv[i], ft_strlen(cmd_argv[i]));
			write(2, "': not a valid identifier\n", 27);
			g_exit_status = 1;
		}
		else
			unset_keyvalue(denv, cmd_argv[i]);
		i++;
	}
}
