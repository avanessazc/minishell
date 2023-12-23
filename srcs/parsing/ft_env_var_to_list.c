/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_var_to_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayzapata <ayzapata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 09:42:19 by ayzapata          #+#    #+#             */
/*   Updated: 2021/09/26 15:54:40 by ayzapata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_set_env_list_node(t_env **tmp, int i)
{
	(*tmp)->equals_symbol = YES;
	ft_free_array(&(*tmp)->name);
	 (*tmp)->name = ft_strndup((*tmp)->str, i);
	if (!(*tmp)->name)
		return (ERR_MALLOC);
	(*tmp)->len_name = ft_strlen((*tmp)->name);
	ft_free_array(&(*tmp)->value);
	(*tmp)->value = ft_strdup(&(*tmp)->str[i + 1]);
	if (!(*tmp)->value)
		return (ERR_MALLOC);
	(*tmp)->len_value = ft_strlen((*tmp)->value);
	(*tmp)->print = YES;
	return (0);
}

static int	ft_env_var_to_list_util(t_env **env_var, char **env, int id)
{
	int	ret;
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		if ((env[i][0] != '\0' && env[i][0] == '_')
			&& (env[i][1] != '\0' && env[i][1] == '='))
			i++;
		else
		{
			ret = ft_add_new_elem_env(env_var, id++, env[i]);
			if (ret != 0)
				return (ret);
			i++;
		}
	}
	return (0);
}

void	ft_init_evtl(t_env_var_to_list *evtl)
{
	evtl->i = 0;
	evtl->id = 1;
	evtl->ret = 0;
}

int	ft_env_var_to_list(t_env **env_var, char **env)
{
	t_env_var_to_list	evtl;
	t_env				*tmp;

	ft_init_evtl(&evtl);
	evtl.ret = ft_env_var_to_list_util(env_var, env, evtl.id);
	if (evtl.ret != 0)
		return (evtl.ret);
	tmp = *env_var;
	while (tmp)
	{
		evtl.i = 0;
		while (tmp->str[evtl.i] != '\0')
		{
			if (tmp->str[evtl.i] == '=')
			{
				evtl.ret = ft_set_env_list_node(&tmp, evtl.i);
				if (evtl.ret != 0)
					return (evtl.ret);
				break ;
			}
			evtl.i++;
		}
		tmp = tmp->next;
	}
	return (SUCCESS);
}
