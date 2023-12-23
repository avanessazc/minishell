/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayzapata <ayzapata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 10:20:16 by ayzapata          #+#    #+#             */
/*   Updated: 2021/04/26 13:33:41 by ayzapata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, int len)
{
	char			*ptr;
	int				l;
	unsigned char	tmp_c;

	tmp_c = (unsigned char)c;
	ptr = (char *)b;
	l = 0;
	while (l < len)
	{
		ptr[l] = tmp_c;
		l++;
	}
	return (b);
}
