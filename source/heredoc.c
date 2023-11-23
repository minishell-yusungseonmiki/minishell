#include "../include/minishell.h"

void	heredoc(t_list *lst)
{
	t_list 	*cur;
	char	*limit;
	char	*tmp;
	int		fd;

	cur = lst;
	while (cur)
	{
		if (((t_token *)(cur->content))->type == HEREDOC)
		{
			limit = ((t_token *)(cur->next->content))->elem;
			fd = open("/tmp/here_doc", O_RDWR | O_CREAT | O_TRUNC, 0666);
			tmp = get_next_line(0);
			while (tmp)
			{
				if (!ft_strncmp(limit, tmp, ft_strlen(limit)))
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
}
