#include "../include/minishell.h"

// 해당 노드가 -n 옵션으로 판단되는지를 확인
static int	is_option(char *s)
{
	int	i;

	if (ft_strncmp(s, "-n", 2) != 0)
		return (0);
	i = 2;
	while (!s[i])
	{
		if (s[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void    execute_echo(char **cmd_argv)
{
	// printf("my echo\n");
	int		i;
	int		option;
	char	*result;
	char	*tmp;

	i = 1;
	option = 0;
	result = "";
	while (cmd_argv[i] && is_option(cmd_argv[i]) == 1)
	{
		option = 1;
		i++;
	}
	while (cmd_argv[i])
	{
		tmp = ft_strjoin(result, cmd_argv[i]);
		result = tmp;
		i++;
	}
	printf("%s", result);
	if (option == 0)
		printf("\n");
}
