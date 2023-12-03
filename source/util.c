#include "../include/minishell.h"

int	is_same(char *a, char *b)
{
	if (ft_strncmp(a, b, ft_strlen(b)) == 0
		&& ft_strlen(a) == ft_strlen(b))
		return (1);
	return (0);
}

void	free_double_str(char **envp)
{
	int	i;

	if (!envp)
		return ;
	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

int	ft_isspace(char c)
{
	if (c == ' ')
		return (1);
	if (c == '\t')
		return (1);
	//if (c == '\n') 개행문자는 제외?
	//	return (1);
	if (c == '\v')
		return (1);
	if (c == '\f')
		return (1);
	if (c == '\r')
		return (1);
	return (0);
}
