#include "../include/minishell.h"

static t_env	*make_envnode(char *key, char *value)
{
	t_env	*node;

	node = (t_env *)malloc(sizeof(t_env));
	node->key = key;
	node->value = value;
	return (node);
}

static void    renew_denv(t_list **denv, char *key, char *value, int flag)
{
    t_list  *iter;

    iter = *denv;
    while (iter)
    {
        if (!ft_strncmp(((t_env *)(iter->content))->key, key, ft_strlen(key))
		&& ft_strlen(((t_env *)(iter->content))->key) == ft_strlen(key))
        {
            if (flag != 0)
                ((t_env *)(iter->content))->value = value;
            return ;
        }
        iter = iter->next;
    }
    ft_lstadd_back(denv, ft_lstnew(make_envnode(key, value)));
}

static void    swap_env(char **now, char **next)
{
    char    *tmp;

    tmp = *now;
    *now = *next;
    *next = tmp;
}

static void    print_export(t_list *denv, t_proc_info *proc)
{
    char    **env;
    int     i;
    int     j;

    env = lst_to_envp(denv, 1);
    i = 0;
    while (env[i + 1])
    {
        j = i + 1;
        while (env[j])
        {
            if (ft_strncmp(env[i], env[j], ft_strchr(env[i], '=') - env[i]) > 0)
                swap_env(&env[i], &env[j]);
            j++;
        }
        i++;
    }
    print_envp(env, proc->out_fd);
    free_envp(env);
}

void    execute_export(char **cmd_argv, t_list *denv, t_proc_info *proc)
{
    int     i;
    int     j;
    char    *key;
    int     equal;

    if (cmd_argv[1] == NULL) //export만 들어오면 환경변수 알파벳정렬 출력
        print_export(denv, proc);
    else
    {
        i = 1;
        while (cmd_argv[i]) //인자 확인
        {
            if (ft_isdigit(cmd_argv[i][0])) //환경변수 이름은 숫자로 시작될 수 없음
            {
                write(2, "export: not a valid identifier\n", 31);
                g_exit_status = 1;
                return ;
            }
            else
            {
                equal = ft_strchr(cmd_argv[i], '=') - cmd_argv[i]; //value 값을 가지는지 확인
                if (equal == 0) //'='로 시작할 수는 없음
                {
                    write(2, "export: not a valid identifier\n", 31);
                    g_exit_status = 1;
                    return ;
                }
                if (equal < 0) //'='이 없을 때(key만 존재)
                    key = cmd_argv[i];
                else //'='이 있을 때(key, value가 존재)
                    key = ft_substr(cmd_argv[i], 0, equal);
                j = 0;
                while (key[j])
                {
                    if (!ft_isalnum(key[j]) && key[j] != '_') //환경변수 이름은 숫자 혹은 알파벳 혹은 _ 만 가능
                    {
                        write(2, "export: not a valid identifier\n", 31);
                        g_exit_status = 1;
                        return ;
                    }
                    j++;
                }
                if (key[j] != '\0') //key값에 오류가 있을 경우
                    continue;
                if (equal < 0) //'='이 없을 경우 value는 NULL
                    renew_denv(&denv, key, ft_strdup(""), 0);
                else
                    renew_denv(&denv, key, ft_substr(cmd_argv[i], equal + 1, ft_strlen(cmd_argv[i]) - equal - 1), 1);                    
            }
            i++;
        }
    }
    // ft_lstiter(denv, print_env);
}
