#include "../include/minishell.h"

void handler(int signum)
{
    if (signum != SIGINT)
        return;
    rl_on_new_line();
    rl_replace_line("", 1);
    rl_redisplay();
}

int main(void)
{
    int ret = 0;
    char *line;

    signal(SIGINT, handler);
    while (1)
    {
        line = readline("input> ");
        if (line)
        {
            if (!ret)
                printf("output> %s\n", line);
            add_history(line);
            free(line);
            line = NULL;
        }
        else
        {
            printf("exit\n");
			return (0);
        }
    }
    return (0);
}