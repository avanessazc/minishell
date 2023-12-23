/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayzapata <ayzapata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/28 12:41:45 by abesombe          #+#    #+#             */
/*   Updated: 2021/09/30 17:08:31 by ayzapata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_print_var(int len, char **tab, int flag)
{
	int	i;
	int	j;

	i = 0;
	while (i < len)
	{
		flag = 0;
		ft_putstr_fd("declare -x ", STDOUT);
		j = 0;
		while (tab[i][j] != '\0')
		{
			ft_putchar_fd(tab[i][j], STDOUT);
			if (tab[i][j] == '=' && flag == 0)
			{
				ft_putchar_fd('\"', STDOUT);
				flag = 1;
			}
			j++;
		}
		if (flag == 1)
			ft_putchar_fd('\"', STDOUT);
		ft_putstr_fd("\n", STDOUT);
		i++;
	}
	return (0);
}

static int	ft_swap_sort(int len, char **tab[], char **name[])
{
	int		i;
	char	*t;

	i = 0;
	while (i < len - 1)
	{
		if (ft_strcmp((*name)[i], (*name)[i + 1]) > 0)
		{
			t = (*tab)[i];
			(*tab)[i] = (*tab)[i + 1];
			(*tab)[i + 1] = t;
			t = (*name)[i];
			(*name)[i] = (*name)[i + 1];
			(*name)[i + 1] = t;
			i = -1;
		}
		i++;
	}
	return (0);
}

static int	ft_free_tabs(char **tab, char **name, int ret)
{
	ft_free_array2(tab);
	ft_free_array2(name);
	return (ret);
}

static int	ft_create_arrays(t_env *env, int len, char **tab[], char **name[])
{
	int		i;
	t_env	*tmp;

	i = 0;
	tmp = env;
	while (tmp && i < len)
	{
		(*tab)[i] = ft_strdup(tmp->str);
		if (!((*tab)[i]))
			return (ft_free_tabs(*tab, *name, ERR_MALLOC));
		(*name)[i] = ft_strdup(tmp->name);
		if (!((*name)[i]))
			return (ft_free_tabs(*tab, *name, ERR_MALLOC));
		tmp = tmp->next;
		i++;
	}
	(*tab)[i] = NULL;
	(*name)[i] = NULL;
	return (0);
}

int	ft_env_sorted(t_env *env)
{
	char	**tab;
	char	**name;
	int		len;

	len = ft_list_size_env(env);
	tab = (char **)malloc(sizeof(char *) * (len + 1));
	if (!tab)
		return (ERR_MALLOC);
	name = (char **)malloc(sizeof(char *) * (len + 1));
	if (!name)
	{
		ft_free_array2(tab);
		return (ERR_MALLOC);
	}
	if (ft_create_arrays(env, len, &tab, &name) != 0)
		return (ERR_MALLOC);
	ft_swap_sort(len, &tab, &name);
	ft_print_var(len, tab, 0);
	ft_free_array2(tab);
	ft_free_array2(name);
	return (SUCCESS);
}
