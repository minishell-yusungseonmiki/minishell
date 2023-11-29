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

static void	make_heredoc(t_list *cur, t_list **h_file, char *filename)
{
	char	*h_filename;
	int		cnt;

	h_filename = NULL;
	cnt = 1;
	while (cur)
	{
		if (((t_token *)(cur->content))->type == PIPE)
		{
			ft_lstadd_back(h_file, ft_lstnew(h_filename));
			cnt++;
			h_filename = NULL;
		}
		if (((t_token *)(cur->content))->type == HEREDOC)
			h_filename = run_heredoc(cur, filename, ft_itoa(cnt));
		cur = cur->next;
	}
	ft_lstadd_back(h_file, ft_lstnew(h_filename));
}

t_list	*heredoc(t_list *lst)
{
	t_list	*h_file;
	char	*filename;
	int		backup_fd;

	backup_fd = dup(STDIN_FILENO);
	h_file = NULL;
	filename = "/tmp/here_doc";
	signal(SIGINT, sigint_heredoc);
	make_heredoc(lst, &h_file, filename);
	dup2(backup_fd, STDIN_FILENO);
	signal(SIGINT, sigint_handler);
	return (h_file);
}
