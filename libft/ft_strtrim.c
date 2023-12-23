/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayzapata <ayzapata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 15:39:48 by ayzapata          #+#    #+#             */
/*   Updated: 2021/09/24 19:36:32 by ayzapata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_char(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static unsigned int	ft_start(char const *s1, char const *set)
{
	unsigned int	i;

	i = 0;
	while (s1[i] != '\0' && ft_char(s1[i], set) == 1)
		i++;
	return (i);
}

static size_t	ft_end(char const *s1, char const *set, size_t i)
{
	size_t	index;

	index = i;
	while (index > 0 && ft_char(s1[index], set) == 1)
		index--;
	return (index);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned int	start;
	size_t			end;
	char			*dst;

	if (s1 == NULL || set == NULL)
		return (NULL);
	if (ft_strlen(s1) != 0)
	{
		start = ft_start(s1, set);
		end = ft_end(s1, set, ft_strlen(s1) - 1);
	}
	if (ft_strlen(s1) == 0 || end < start)
	{
		dst = (char *)malloc(sizeof(char));
		dst[0] = '\0';
		return (dst);
	}
	dst = ft_substr(s1, start, end - start + 1);
	if (dst)
		return (NULL);
	return (dst);
}
