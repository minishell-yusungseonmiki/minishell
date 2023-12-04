/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonmiki <seonmiki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 22:10:23 by yusung            #+#    #+#             */
/*   Updated: 2023/11/21 20:14:04 by seonmiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	size;
	size_t	i;
	char	*result;

	size = 0;
	if (start < ft_strlen(s))
	{
		while (s[start + size] && size < len)
			size++;
	}
	result = (char *)malloc(size + 1);
	if (result == 0)
		return (0);
	i = 0;
	while (i < size)
	{
		result[i] = s[start + i];
		i++;
	}
	result[i] = 0;
	return (result);
}
