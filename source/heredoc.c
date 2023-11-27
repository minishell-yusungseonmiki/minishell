#include "../include/minishell.h"

void	sigint_heredoc(int signum)
{
	(void)signum;
	close(0);
}

t_list	*heredoc(t_list *lst)
{
	t_list 	*cur;
	char	*limit;
	char	*tmp;
	int		fd;
	t_list	*h_file;
	char	*filename;
	int		cnt;
	char	*h_filename;
	int		backup_fd;

	backup_fd = dup(0);
	cur = lst;
	h_file = NULL;
	h_filename = NULL;
	filename = "/tmp/here_doc";
	cnt = 1;
	signal(SIGINT, sigint_heredoc);
	signal(SIGQUIT, SIG_IGN);
	while (cur)
	{
		if (((t_token *)(cur->content))->type == PIPE)
		{
			ft_lstadd_back(&h_file, ft_lstnew(h_filename));
			cnt++;
			h_filename = NULL;
		}
		if (((t_token *)(cur->content))->type == HEREDOC)
		{
			limit = ((t_token *)(cur->next->content))->elem;
			h_filename = ft_strjoin(filename, ft_itoa(cnt)); //ft_itoa도 프리해야함
			// printf("h_F : %s\n", h_filename);
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
		}
		cur = cur->next;
	}
	ft_lstadd_back(&h_file, ft_lstnew(h_filename));
	dup2(backup_fd, 0);
	return (h_file);
}
