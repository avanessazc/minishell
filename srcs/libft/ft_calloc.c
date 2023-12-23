/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayzapata <ayzapata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 14:22:28 by ayzapata          #+#    #+#             */
/*   Updated: 2021/09/24 19:12:10 by ayzapata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*ptr_m;
	size_t			i;

	i = 0;
	if (count == 0 || size == 0)
	{
		count = 1;
		size = 1;
	}
	ptr_m = malloc(size * count);
	if (ptr_m == NULL)
	{
		return (NULL);
	}
	while (i < count * size)
	{
		ptr_m[i] = '\0';
		i++;
	}
	return (ptr_m);
}
