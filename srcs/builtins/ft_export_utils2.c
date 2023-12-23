/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayzapata <ayzapata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/28 12:42:15 by abesombe          #+#    #+#             */
/*   Updated: 2021/09/30 17:08:34 by ayzapata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_upper_case_list(t_env **upper_case, char c, t_env *tmp)
{
	t_env	*tempo;

	if (c >= 'A' && c <= 'Z')
	{
		if (ft_add_new_elem_env(upper_case,
				ft_list_size_env(*upper_case) + 1, tmp->str) != 0)
			return (ERR_MALLOC);
		tempo = *upper_case;
		while (tempo)
		{
			if (tempo->next == NULL)
			{
				tempo->name = ft_strdup(tmp->name);
				if (!tempo->name)
					return (ERR_MALLOC);
				break ;
			}
			tempo = tempo->next;
		}
	}
	return (0);
}

static int	ft_lower_case_list(t_env **lower_case, char c, t_env *tmp)
{
	t_env	*tempo;

	if ((c >= 'a' && c <= 'z') || c == '_')
	{
		if (ft_add_new_elem_env(lower_case,
				ft_list_size_env(*lower_case) + 1, tmp->str) != 0)
			return (ERR_MALLOC);
		tempo = *lower_case;
		while (tempo)
		{
			if (tempo->next == NULL)
			{
				tempo->name = ft_strdup(tmp->name);
				if (!tempo->name)
					return (ERR_MALLOC);
				break ;
			}
			tempo = tempo->next;
		}
	}
	return (0);
}

static int	ft_free_lists(t_env **upper_case, t_env **lower_case, int ret)
{
	ft_clear_list_env(upper_case);
	ft_clear_list_env(lower_case);
	return (ret);
}

static void	ft_init(t_env **upper_case, t_env **lower_case)
{
	*upper_case = NULL;
	*lower_case = NULL;
}

int	ft_print_export_list(t_env *env)
{
	t_env	*tmp;
	t_env	*upper_case;
	t_env	*lower_case;
	char	c;

	ft_init(&upper_case, &lower_case);
	tmp = env;
	while (tmp)
	{
		if (tmp->str[0] != '\0')
		{
			c = tmp->str[0];
			if (ft_upper_case_list(&upper_case, c, tmp) != 0)
				return (ft_free_lists(&upper_case, &lower_case, ERR_MALLOC));
			if (ft_lower_case_list(&lower_case, c, tmp) != 0)
				return (ft_free_lists(&upper_case, &lower_case, ERR_MALLOC));
		}
		tmp = tmp->next;
	}
	if (ft_env_sorted(upper_case) != 0)
		return (ft_free_lists(&upper_case, &lower_case, ERR_MALLOC));
	if (ft_env_sorted(lower_case) != 0)
		return (ft_free_lists(&upper_case, &lower_case, ERR_MALLOC));
	ft_free_lists(&upper_case, &lower_case, 0);
	return (0);
}
