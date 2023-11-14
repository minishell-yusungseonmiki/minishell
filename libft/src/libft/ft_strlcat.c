/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusung <yusung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 19:06:36 by yusung            #+#    #+#             */
/*   Updated: 2023/03/18 20:46:31 by yusung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	len_d;
	size_t	len_s;
	size_t	i;
	size_t	j;

	len_d = ft_strlen(dst);
	len_s = ft_strlen(src);
	if (dstsize < len_d)
		return (len_s + dstsize);
	i = len_d;
	j = 0;
	while (i + 1 < dstsize && src[j])
		dst[i++] = src[j++];
	dst[i] = 0;
	return (len_d + len_s);
}
