#include "../include/minishell.h"

char	*heredoc(t_list *lst)
{
	t_list 	*cur;
	char	*limit;
	char	*tmp;
	char	*ret;

	cur = lst;
	while (cur)
	{
		if (((t_token *)(cur->content))->type == HEREDOC)
		{
			limit = ((t_token *)(cur->next->content))->elem;
			ret = "";
			tmp = get_next_line(0);
			while (tmp)
			{
				if (!ft_strncmp(limit, tmp, ft_strlen(limit)))
					break ;
				ret = ft_strjoin(ret, tmp);
				free(tmp);
				tmp = get_next_line(0);
			}
		}
		cur = cur->next;
	}
	return (ret);
}
