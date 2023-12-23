/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayzapata <ayzapata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 09:22:55 by ayzapata          #+#    #+#             */
/*   Updated: 2021/09/24 19:15:42 by ayzapata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(char const *s, char c)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] != '\0' && s[i] != c)
		{
			count++;
			while (s[i] != '\0' && s[i] != c)
				i++;
		}
		while (s[i] != '\0' && s[i] == c)
			i++;
	}
	return (count);
}

static	char	*ft_malloc(char const *s, char c)
{
	char	*sub_dst;
	int		n;

	n = 0;
	while (s[n] != '\0' && s[n] != c)
		n++;
	sub_dst = (char *)malloc(sizeof(char) * (n + 1));
	if (sub_dst == NULL)
		return (NULL);
	n = 0;
	while (s[n] != c && s[n] != '\0')
	{
		sub_dst[n] = s[n];
		n++;
	}
	sub_dst[n] = '\0';
	return (sub_dst);
}

char	**create_tab(char const *s, char c, int *i, int *j)
{
	int		size;
	char	**dst;
	int		k;

	size = ft_count(s, c);
	dst = (char **)malloc(sizeof(char *) * (size + 1));
	if (dst == NULL)
		return (NULL);
	k = 0;
	while (k < size + 1)
	{
		dst[k] = NULL;
		k++;
	}
	*i = 0;
	*j = 0;
	return (dst);
}

char	**ft_free_tab_split(char **to_free)
{
	int		i;
	char	**ret;

	i = 0;
	if (to_free)
	{
		while (to_free[i])
		{
			free(to_free[i]);
			to_free[i] = NULL;
			i++;
		}
		free(to_free);
		to_free = NULL;
	}
	ret = NULL;
	return (ret);
}

char	**ft_split(char const *s, char c)
{
	char	**dst;
	int		i;
	int		j;

	dst = create_tab(s, c, &i, &j);
	if (dst == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		while (s[i] != '\0' && s[i] == c)
			i++;
		if (s[i] != '\0' && s[i] != c)
		{
			dst[j] = ft_malloc(&s[i], c);
			if (dst[j] == NULL)
				return (ft_free_tab_split(dst));
			j++;
			while (s[i] != '\0' && s[i] != c)
				i++;
		}
	}
	dst[j] = NULL;
	return (dst);
}
