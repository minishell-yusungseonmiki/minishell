/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonmiki <seonmiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 15:06:44 by seonmiki          #+#    #+#             */
/*   Updated: 2023/12/04 15:44:58 by seonmiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_list	*denv;

	if (argc > 1 || argv[1])
		error(START, NULL);
	denv = envp_to_lst(envp);
	while (1)
	{
		print_off_signal();
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, SIG_IGN);
		line = readline("\033[1;34mminishell> \033[0m");
		run_minishell(line, &denv);
	}
	ft_lstclear(&denv, free_env);
	return (0);
}

void	run_minishell(char *line, t_list **denv)
{
	t_list	*token_lst;
	t_list	*proc_lst;

	if (line)
	{
		if (!line_check(line, &token_lst))
			return ;
		erase_quotes(token_lst, *denv);
		proc_lst = make_proc_list(token_lst, denv);
		heredoc(proc_lst);
		execute(proc_lst);
		wait_process(proc_lst);
		*denv = ((t_proc_info *)(proc_lst->content))->denv;
		add_history(line);
		free(line);
		ft_lstclear(&token_lst, free_token);
		ft_lstclear(&proc_lst, free_proc_info);
	}
	else
	{
		ft_lstclear(denv, free_env);
		printf("exit\n");
		exit(0);
	}
}
