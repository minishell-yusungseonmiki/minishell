/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusung <yusung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 19:58:52 by yusung            #+#    #+#             */
/*   Updated: 2023/03/24 00:28:09 by yusung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*result;
	int		start;
	int		end;

	start = 0;
	end = ft_strlen(s1);
	while (s1[start])
	{
		if (!ft_strchr(set, s1[start]))
			break ;
		start++;
	}
	while (start < end)
	{
		if (!ft_strchr(set, s1[end - 1]))
			break ;
		end--;
	}
	result = (char *)malloc(end - start + 1);
	if (result == 0)
		return (0);
	ft_strlcpy(result, &s1[start], end - start + 1);
	return (result);
}
