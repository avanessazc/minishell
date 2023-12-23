/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayzapata <ayzapata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 17:52:53 by abesombe          #+#    #+#             */
/*   Updated: 2021/09/24 19:06:07 by ayzapata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export_tab(t_program *program, char **tab[])
{
	int		ret;

	ret = ft_export(program, *tab, 0, 0);
	if (ret != 0)
	{
		(*tab)[0] = NULL;
		ft_free_array(&((*tab)[1]));
		ft_free_array2(*tab);
		return (ERR_MALLOC);
	}
	if (*tab)
	{
		(*tab)[0] = NULL;
		ft_free_array(&((*tab)[1]));
		ft_free_array2(*tab);
	}
	return (0);
}

int	ft_set(t_program *program, char *var_name, char *value)
{
	char	**tab;
	char	*varname_eq;

	tab = (char **)malloc(sizeof(char *) * 3);
	if (tab == NULL)
		return (ERR_MALLOC);
	tab[0] = "export";
	varname_eq = ft_strjoin(var_name, "=");
	if (varname_eq == NULL)
	{
		ft_free_array2(tab);
		return (ERR_MALLOC);
	}
	tab[1] = ft_strjoin(varname_eq, value);
	free(varname_eq);
	if (tab[1] == NULL)
	{
		ft_free_array2(tab);
		return (ERR_MALLOC);
	}
	tab[2] = NULL;
	if (ft_export_tab(program, &tab) != 0)
		return (ERR_MALLOC);
	return (0);
}
