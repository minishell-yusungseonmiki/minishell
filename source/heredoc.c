#include "../include/minishell.h"

static char	*run_heredoc(t_list *cur, char *filename, char *cnt)
{
	int		fd;
	char	*tmp;
	char	*limit;
	char	*h_filename;

	limit = ((t_token *)(cur->next->content))->elem;
	h_filename = ft_strjoin(filename, cnt);
	free(cnt);
	fd = open(h_filename, O_RDWR | O_CREAT | O_TRUNC, 0666);
	tmp = get_next_line(0);
	while (tmp)
	{
		if (!ft_strncmp(limit, tmp, ft_strlen(limit))
			&& (ft_strlen(limit) == ft_strlen(tmp) - 1))
		{
			free(tmp);
			break ;
		}
		write(fd, tmp, ft_strlen(tmp));
		free(tmp);
		tmp = get_next_line(0);
	}
	close(fd);
	return (h_filename);
}

static void	make_heredoc(t_list *cur, t_list *proc_lst, char *filename)
{
	char	*h_filename;
	int		cnt;

	h_filename = NULL;
	cnt = 1;
	ft_lstiter(proc_lst, print_proc_info);
	while (cur && proc_lst)
	{
		if (((t_token *)(cur->content))->type == PIPE)
		{
			if (h_filename)
				((t_proc_info *)(proc_lst->content))->h_filename = ft_strdup(h_filename);
			proc_lst = proc_lst->next;
			cnt++;
			h_filename = NULL;
		}
		if (((t_token *)(cur->content))->type == HEREDOC)
			h_filename = run_heredoc(cur, filename, ft_itoa(cnt));
		cur = cur->next;
	}
	if (h_filename)
		((t_proc_info *)(proc_lst->content))->h_filename = ft_strdup(h_filename);
}

void	heredoc(t_list *token_lst, t_list *proc_lst)
{
	char	*filename;
	int		backup_fd;

	backup_fd = dup(STDIN_FILENO);
	filename = "/tmp/here_doc";
	signal(SIGINT, sigint_heredoc);
	make_heredoc(token_lst, proc_lst, filename);
	dup2(backup_fd, STDIN_FILENO);
	signal(SIGINT, sigint_handler);
}
