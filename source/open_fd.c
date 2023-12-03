#include "../include/minishell.h"

static int	open_file(char *filename, int option)
{
	int	fd;

	fd = -1;
	if (option == 0) // <, <<
		fd = open(filename, O_RDONLY);
	else if (option == 1) // >
		fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0666);
	else if (option == 2) // >>
		fd = open(filename, O_CREAT | O_RDWR | O_APPEND, 0666);
	if (fd < 0)
	{
		perror(NULL);
		exit(1);
	}
	return (fd);
}

int	find_in_fd(t_list *lst, char *h_filename)
{
	int		fd;
	char	*infile_name;

	fd = 0;
	while (lst)
	{
		if (((t_node *)(lst->content))->type == IN)
		{
			infile_name = ((t_node *)(lst->next->content))->elem;
			fd = open_file(infile_name, 0);
		}
		else if (((t_node *)(lst->content))->type == HEREDOC)
			fd = open_file(h_filename, 0);
		lst = lst->next;
	}
	return (fd);
}

int	find_out_fd(t_list *lst)
{
	int		fd;
	char	*outfile_name;
	
	fd = 1;
	while (lst)
	{
		if ((((t_node *)(lst->content))->type) == OUT)
		{
			outfile_name = ((t_node *)(lst->next->content))->elem;
			fd = open_file(outfile_name, 1);
		}
		if (((t_node *)(lst->content))->type == APPEND)
		{
			outfile_name = ((t_node *)(lst->next->content))->elem;
			fd = open_file(outfile_name, 2);
		}
		lst = lst->next;
	}
	return (fd);
}
