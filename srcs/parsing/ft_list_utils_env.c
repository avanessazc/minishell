/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_utils_env.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayzapata <ayzapata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 17:07:15 by ayzapata          #+#    #+#             */
/*   Updated: 2021/09/30 17:07:18 by ayzapata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_new_elem_env(int id, char *var)
{
	t_env	*new_element;

	new_element = (t_env *)malloc(sizeof(t_env));
	if (!new_element)
		return (NULL);
	new_element->id = id;
	new_element->str = ft_strdup(var);
	if (!new_element->str)
		return (NULL);
	new_element->name = NULL;
	new_element->len_name = 0;
	new_element->equals_symbol = NO;
	new_element->value = NULL;
	new_element->len_value = 0;
	new_element->print = YES;
	new_element->next = NULL;
	return (new_element);
}

int	ft_add_new_elem_env(t_env **env, int id, char *str)
{
	t_env	*new;
	t_env	*tmp;

	new = ft_new_elem_env(id, str);
	if (new == NULL)
		return (ERR_MALLOC);
	if (!(*env))
		*env = new;
	else
	{
		tmp = (*env);
		while ((*env)->next)
			*env = (*env)->next;
		(*env)->next = new;
		*env = tmp;
	}
	return (0);
}

void	ft_clear_list_env(t_env **to_free)
{
	t_env	*next;

	while (*to_free)
	{
		next = (*to_free)->next;
		if ((*to_free)->str)
		{
			free((*to_free)->str);
			(*to_free)->str = NULL;
		}
		if ((*to_free)->name)
		{
			free((*to_free)->name);
			(*to_free)->name = NULL;
		}
		if ((*to_free)->value)
		{
			free((*to_free)->value);
			(*to_free)->value = NULL;
		}
		free(*to_free);
		*to_free = next;
	}
	to_free = NULL;
}

int	ft_list_size_env(t_env *lst)
{
	int		i;

	i = 0;
	while (lst != NULL)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}
