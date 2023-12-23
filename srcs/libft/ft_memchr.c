/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayzapata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 10:41:24 by ayzapata          #+#    #+#             */
/*   Updated: 2019/11/14 12:41:11 by ayzapata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	tmp_c;
	size_t			i;
	unsigned char	*ptr_s;

	ptr_s = (unsigned char *)s;
	tmp_c = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (tmp_c == ptr_s[i])
			return (&ptr_s[i]);
		i++;
	}
	return (NULL);
}
