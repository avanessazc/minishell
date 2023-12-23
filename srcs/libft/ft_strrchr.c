/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayzapata <ayzapata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 15:51:12 by ayzapata          #+#    #+#             */
/*   Updated: 2021/09/24 19:19:30 by ayzapata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	tmp_c;
	char	*tmp_s;
	int		i;
	char	*p;

	tmp_c = (char)c;
	tmp_s = (char *)s;
	i = 0;
	p = 0;
	while (tmp_s[i] != '\0')
	{
		if (tmp_s[i] == tmp_c)
		{
			p = &tmp_s[i];
		}
		i++;
	}
	if (tmp_s[i] == tmp_c)
	{
		p = &tmp_s[i];
	}
	return (p);
}
