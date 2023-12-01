#include "../include/minishell.h"

void	print_token(void *token)
{
	printf("-----------\n");
	printf("content: %s\n state: %d\n blank : %d\n", ((t_token *)token)->elem, ((t_token *)token)->type, ((t_token *)token)->before_blank);
	printf("-----------\n");
}

void	print_node(void *node)
{
	printf("%s\n", ((t_node *)node)->elem);
}
//구조체 내부의 값 출력(테스트용 함수)
void	print_proc_info(void *proc_info)
{
	t_proc_info *pi;

	pi = (t_proc_info *)proc_info;
	printf("--HEREDOC_FILE\n");
	printf("%s\n", pi->h_filename);
	printf("IN_FD : %d, OUT_FD : %d\n", pi->in_fd, pi->out_fd);
	printf("--CMD_ARGV--\n");
	int	i = 0;
	while (pi->cmd_argv && (pi->cmd_argv)[i])
	{
		printf("%s\n", (pi->cmd_argv)[i]);
		i++;
	}
	printf("--CMD_PATH--\n");
	printf("%s\n", pi->cmd_path);

	printf("--NODE_LIST--\n");
	ft_lstiter(pi->node_lst, print_node);
	printf("\n");
}