/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonmiki <seonmiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 17:33:41 by seonmiki          #+#    #+#             */
/*   Updated: 2023/12/04 15:14:33 by seonmiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_envp(char **envp, int out_fd)
{
	int	i;

	i = 0;
	while (envp && envp[i])
	{
		ft_putstr_fd("declare -x ", out_fd);
		ft_putstr_fd(envp[i], out_fd);
		ft_putstr_fd("\n", out_fd);
		i++;
	}
}

void	print_env(void *token)
{
	if (((t_env *)token)->value[0] == '\0')
		return ;
	printf("%s=%s\n", ((t_env *)token)->key, ((t_env *)token)->value);
}
