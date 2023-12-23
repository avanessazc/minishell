/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_utils_tokens.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayzapata <ayzapata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 17:07:22 by ayzapata          #+#    #+#             */
/*   Updated: 2021/09/30 17:07:23 by ayzapata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*ft_new_elem(int id)
{
	t_list	*new_element;

	new_element = (t_list *)malloc(sizeof(t_list));
	if (!new_element)
		return (NULL);
	new_element->id = id;
	new_element->line = NULL;
	new_element->type = 0;
	new_element->qtdae = NULL;
	new_element->nq = NULL;
	new_element->check_equal = NO;
	new_element->check_export = NO;
	new_element->check_cd = NO;
	new_element->next = NULL;
	return (new_element);
}

int	ft_add_new_elem(t_list **cmd, int id)
{
	t_list	*new;
	t_list	*tmp;

	new = ft_new_elem(id);
	if (new == NULL)
		return (ERR_MALLOC);
	if (!(*cmd))
		*cmd = new;
	else
	{
		tmp = (*cmd);
		while ((*cmd)->next)
			*cmd = (*cmd)->next;
		(*cmd)->next = new;
		*cmd = tmp;
	}
	return (0);
}

void	ft_clear_list(t_list **to_free)
{
	t_list	*next;

	while (*to_free)
	{
		next = (*to_free)->next;
		if ((*to_free)->line)
		{
			free((*to_free)->line);
			(*to_free)->line = NULL;
		}
		if ((*to_free)->qtdae)
		{
			free((*to_free)->qtdae);
			(*to_free)->qtdae = NULL;
		}
		if ((*to_free)->nq)
		{
			free((*to_free)->nq);
			(*to_free)->nq = NULL;
		}
		free(*to_free);
		*to_free = next;
	}
	to_free = NULL;
}

int	ft_list_size(t_list *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}
