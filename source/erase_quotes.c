#include "../include/minishell.h"

//따옴표 지우기
//원본을 먼저 저장해두고 새로운 결과값을 빈 문자열로 세팅 후 순회
//1. 따옴표 만나면 다음 따옴표 만날 때까지 사이값을 새로운 결과값에 추가
//2. 따옴표가 아닌 경우 따옴표 만날 때까지 문자열을 새로운 결과값에 추가
void	erase_quotes(t_list *lst)
{
	int		start;
	int		end;
	char	*elem;
	char	*new_elem;
	char	*tmp;
	char	q;
	int		i;

	while (lst)
	{
		if (((t_token *)(lst->content))->type == ARG) //argument인 경우에만
		{
			elem = ((t_token *)(lst->content))->elem; //원본 저장
			new_elem = ""; //빈 문자열로 초기세팅
			i = 0;
			q = 0;
			while (elem[i])
			{
				if (elem[i] == '\'' || elem[i] == '\"') //1.따옴표 만나면
				{
					q = elem[i];
					start = i;
					i++;
					while (elem[i] && elem[i] != q)
						i++;
					end = i;
					q = 0;
					tmp = ft_substr(elem, start + 1, end - start - 1);
					new_elem = ft_strjoin(new_elem, tmp);
					free(tmp);
					i++;
				}
				else //2.따옴표 아닌경우
				{
					start = i;
					while (elem[i] && elem[i] != '\'' && elem[i] != '\"')
						i++;
					end = i;
					tmp = ft_substr(elem, start, end - start);
					new_elem = ft_strjoin(new_elem, tmp);
					free(tmp);
				}
			}
			free(((t_token *)(lst->content))->elem);
			((t_token *)(lst->content))->elem = new_elem;
		}
		lst = lst->next;
	}
}

//바보같은 삽질의 흔적ㅠㅠ
// void    erase_quotes(t_list *lst)
// {
//     int     start;
//     int     end;
//     char    *new_elem;
// 	char	*elem;
//     char    *new;
// 	int		i;
// 	int		quote;

//     while (lst)
//     {
//         if (((t_token *)(lst->content))->type == ARG)
//         {
//             elem = ((t_token *)(lst->content))->elem;
// 			new_elem = ft_strdup(elem);
// 			i = 0;
// 			quote = 0;
// 			while (elem[i])
// 			{
// 				if (ft_strchr(elem + i, '\"'))
// 				{
// 					printf("new_elem: %s\n", new_elem);
// 					start = ft_strchr(elem, '\"') - elem;
// 					end = ft_strchr(elem + start + 1, '\"') - elem;
// 					printf("start: %d, end: %d, len: %d\n", start, end, end - start - 1);
// 					new_elem[start - quote] = '\0';
// 					if (end - start - 1 != 0)
// 					{
// 						new = ft_substr(elem, start + 1, end - start - 1);
// 						printf("new: %s\n", new);
// 						new_elem = ft_strjoin(new_elem, new);
// 						free(new);
// 						printf("strjoin: %s\n", new_elem);
// 					}
// 					quote += 2;
// 					i = end;
// 				}
// 				i++;
// 			}
// 			free(((t_token *)(lst->content))->elem);
// 			((t_token *)(lst->content))->elem = new_elem;
// 			printf("ret: %s\n", ((t_token *)(lst->content))->elem);
//         }
//         lst = lst->next;
//     }
// }