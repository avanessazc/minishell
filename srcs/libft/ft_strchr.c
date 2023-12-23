/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayzapata <ayzapata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 14:32:27 by ayzapata          #+#    #+#             */
/*   Updated: 2021/09/24 19:16:05 by ayzapata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strchr(const char *s, int c)
{
	char	tmp_c;
	char	*tmp_s;
	int		i;

	tmp_c = (char)c;
	tmp_s = (char *)s;
	i = 0;
	while (tmp_s[i] != '\0' && tmp_s[i] != tmp_c)
		i++;
	if (tmp_s[i] == tmp_c)
		return (1);
	return (0);
}
