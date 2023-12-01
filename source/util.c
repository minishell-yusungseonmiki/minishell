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

	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}