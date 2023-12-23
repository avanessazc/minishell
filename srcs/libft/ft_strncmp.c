/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayzapata <ayzapata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 16:31:19 by ayzapata          #+#    #+#             */
/*   Updated: 2021/09/24 19:19:05 by ayzapata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, int n)
{
	int				i;
	unsigned char	*t_s1;
	unsigned char	*t_s2;

	t_s1 = (unsigned char *)s1;
	t_s2 = (unsigned char *)s2;
	i = 0;
	while ((t_s1[i] != '\0' || t_s2[i] != '\0') && i < n)
	{
		if (t_s1[i] == t_s2[i])
			i++;
		else
			return ((t_s1[i] - t_s2[i]));
	}
	return (0);
}
