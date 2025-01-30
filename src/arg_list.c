/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeckham <ppeckham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 11:53:35 by ppeckham          #+#    #+#             */
/*   Updated: 2025/01/30 12:24:02 by ppeckham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_arg	*ft_new_arg(t_arg *arg_node)
{
	t_arg	*new_node;

	new_node = malloc(sizeof(t_arg));
	if (!new_node)
		return (NULL);
	new_node->str = NULL;
	new_node->len = 0;
	new_node->type = -1;
	new_node->job = NULL;
	new_node->next = NULL;
	return (new_node);
}

t_arg	*ft_last_arg(t_arg *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

void	ft_add_arg_back(t_arg **lst, t_arg *new)
{
	t_arg	*last_node;

	if (!new || !lst)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last_node = ft_last_arg(*lst);
	last_node->next = new;
}

int	ft_arg_lstsize(t_arg **lst)
{
	int		i;
	t_arg	*aux;

	aux = *lst;
	i = 0;
	while (aux)
	{
		i++;
		aux = aux->next;
	}
	return (i);
}

void	ft_free_arg_list(t_arg **lst)
{
	t_arg	*aux;
	t_arg	*next;

    if (!lst)
        return;

    aux = *lst;
    while (aux)
    {
		next = aux->next;
        free(aux->str);
        free(aux->len);
		free(aux->type);
		free(aux->job);
        free(aux);
        aux = next;
    }
    *lst = NULL;
}
