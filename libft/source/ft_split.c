/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusung <yusung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 17:48:06 by yusung            #+#    #+#             */
/*   Updated: 2023/03/24 03:29:02 by yusung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	all_free(char **result, int n)
{
	int	i;

	i = 0;
	while (i < n)
		free(result[i++]);
	free(result);
}

int	check_cnt(const char *str, char c)
{
	int	cnt;
	int	flag;
	int	i;

	cnt = 0;
	flag = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] == c)
			i++;
		while (str[i] && str[i] != c)
		{
			flag++;
			i++;
		}
		if (flag != 0)
		{
			cnt++;
			flag = 0;
		}
	}
	return (cnt);
}

void	ft_strncpy(char *dest, const char *src, int n)
{
	int	i;

	i = 0;
	while (src[i] != 0 && i < n)
	{
		dest[i] = src[i];
		i += 1;
	}
	dest[i] = 0;
}

char	**allocate_len(char **result, const char *s, char c, int cnt)
{
	int	flag;
	int	i;

	i = -1;
	while (++i < cnt)
	{
		flag = 0;
		while (*s == c)
			s++;
		while (s[flag] && s[flag] != c)
			flag++;
		if (flag != 0)
		{
			result[i] = (char *)malloc(sizeof(char) * (flag + 1));
			if (result[i] == 0)
			{
				all_free(result, i);
				return (0);
			}
			ft_strncpy(result[i], s, flag);
			s += flag;
		}
	}
	result[i] = 0;
	return (result);
}

char	**ft_split(const char *s, char c)
{
	char	**result;
	int		cnt;

	cnt = check_cnt(s, c);
	result = (char **)malloc(sizeof(char *) * (cnt + 1));
	if (result == 0)
		return (0);
	result = allocate_len(result, s, c, cnt);
	return (result);
}
