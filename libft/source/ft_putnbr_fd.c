/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusung <yusung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 21:18:57 by yusung            #+#    #+#             */
/*   Updated: 2023/03/20 21:40:44 by yusung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	re_putnbr(int n, int fd)
{
	if (n == 0)
		return ;
	re_putnbr(n / 10, fd);
	write(fd, &"0123456789"[n % 10], 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == 0)
	{
		write(fd, "0", 1);
		return ;
	}
	if (n < 0)
	{
		if (n == -2147483648)
		{
			write(fd, "-2147483648", 11);
			return ;
		}
		else
		{
			write(fd, "-", 1);
			n *= -1;
		}
	}
	re_putnbr(n, fd);
}
