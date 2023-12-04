/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusung <yusung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 17:39:17 by yusung            #+#    #+#             */
/*   Updated: 2023/03/20 18:01:48 by yusung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	check_len(int n)
{
	int			len;
	long long	nbr;

	nbr = (long long)n;
	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		nbr *= -1;
		len++;
	}
	while (nbr > 0)
	{
		nbr /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char		*result;
	long long	nbr;
	int			i;
	int			end;

	result = (char *)malloc(check_len(n) + 1);
	if (result == 0)
		return (0);
	nbr = (long long)n;
	i = check_len(n);
	end = 0;
	if (nbr < 0)
	{
		nbr *= -1;
		result[0] = '-';
		end = 1;
	}
	result[i] = 0;
	while (i-- > end)
	{
		result[i] = nbr % 10 + '0';
		nbr /= 10;
	}
	return (result);
}
