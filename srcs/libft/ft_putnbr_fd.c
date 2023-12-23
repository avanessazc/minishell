/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayzapata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 10:51:31 by ayzapata          #+#    #+#             */
/*   Updated: 2019/11/12 11:41:16 by ayzapata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int		nbr;

	nbr = n;
	if (n == -2147483648)
		write(fd, "-2147483648", 11);
	else
	{
		if (n < 0)
		{
			nbr = n * -1;
			write(fd, "-", 1);
		}
		if (nbr >= 10)
		{
			ft_putnbr_fd(nbr / 10, fd);
			ft_putchar_fd((nbr % 10) + '0', fd);
		}
		else
			ft_putchar_fd((nbr % 10) + '0', fd);
	}
}
