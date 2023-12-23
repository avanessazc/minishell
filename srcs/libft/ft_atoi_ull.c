/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_ull.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayzapata <ayzapata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 14:02:18 by ayzapata          #+#    #+#             */
/*   Updated: 2021/09/24 19:09:23 by ayzapata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned long long	ft_atoi_ull(const char *str)
{
	int					i;
	int					sig;
	unsigned long long	num;

	sig = 1;
	i = 0;
	while ((str[i] <= 13 && str[i] >= 9) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sig = sig * -1;
		i++;
	}
	num = 0;
	while ((str[i] >= '0' && str[i] <= '9') && str[i])
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	return (num * sig);
}
