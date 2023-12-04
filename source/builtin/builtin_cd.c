/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusung <yusung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 16:13:11 by yusung            #+#    #+#             */
/*   Updated: 2023/12/04 16:42:01 by yusung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	builtin_cd_error(char *str)
{
	write(2, "cd: ", 5);
	write(2, str, ft_strlen(str));
	write(2, ": ", 3);
	perror(NULL);
	g_exit_status = 1;
}

static char	*find_value(t_list *denv, char *find)
{
	while (denv)
	{
		if (!ft_strncmp(((t_env *)(denv->content))->key, find, ft_strlen(find))
		&& ft_strlen(((t_env *)(denv->content))->key) == ft_strlen(find))
			return (((t_env *)(denv->content))->value);
		denv = denv->next;
	}
	return (NULL);
}

static void	set_value(t_list **denv, char *key, char *new_value)
{
	t_list	*iter;

	iter = *denv;
	while (iter)
	{
		if (!ft_strncmp(((t_env *)(iter->content))->key, key, ft_strlen(key))
		&& ft_strlen(((t_env *)(iter->content))->key) == ft_strlen(key))
		{
			free(((t_env *)(iter->content))->value);
			((t_env *)(iter->content))->value = ft_strdup(new_value);
		}
		iter = iter->next;
	}
}

void	execute_cd(t_proc_info *proc)
{
	char	*old_pwd;
	char	*now_pwd;

	old_pwd = find_value(proc->denv, "PWD");
	if (proc->cmd_argv[1])
	{
		if (chdir(proc->cmd_argv[1]) < 0)
			builtin_cd_error(proc->cmd_argv[1]);
	}
	set_value(&proc->denv, "OLDPWD", old_pwd);
	now_pwd = getcwd(NULL, 0);
	set_value(&proc->denv, "PWD", now_pwd);
	free(now_pwd);
}
