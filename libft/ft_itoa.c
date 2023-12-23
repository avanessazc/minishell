/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayzapata <ayzapata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 12:08:37 by ayzapata          #+#    #+#             */
/*   Updated: 2021/09/24 19:11:26 by ayzapata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_size_tab(int n)
{
	int		s;
	int		nbr;

	s = 0;
	nbr = n;
	if (nbr <= 0)
		s++;
	while (nbr != 0)
	{
		nbr = nbr / 10;
		s++;
	}
	return (s);
}

static void	ft_trans(char *tab, long nbr, int size)
{
	int	i;

	i = size - 1;
	while (i >= 0)
	{
		tab[i] = nbr % 10 + '0';
		nbr = nbr / 10;
		i--;
	}
}

char	*ft_itoa(int n)
{
	char	*tab;
	int		size;
	long	nbr;
	int		sig;

	nbr = n;
	sig = 1;
	size = ft_size_tab(n);
	tab = (char *)malloc(sizeof(char) * (size + 1));
	if (tab == NULL)
		return (NULL);
	if (nbr < 0)
	{
		sig = -1;
		nbr = nbr * -1;
	}
	ft_trans(tab, nbr, size);
	if (sig == -1)
		tab[0] = '-';
	tab[size] = '\0';
	return (tab);
}
