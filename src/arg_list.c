/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeckham <ppeckham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 11:53:35 by ppeckham          #+#    #+#             */
/*   Updated: 2025/02/26 13:43:05 by ppeckham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_arg	*ft_new_arg(t_arg *arg_node)
{
	arg_node = malloc(sizeof(t_arg));
	if (!arg_node)
		return (NULL);
	arg_node->str = NULL;
	arg_node->temp = NULL;
	arg_node->temp2 = NULL;
	arg_node->pre = NULL;
	arg_node->post = NULL;
	arg_node->exp = NULL;
	arg_node->len = 0;
	arg_node->type = -1;
	arg_node->has_expand = false;
	arg_node->valid_expand = false;
	arg_node->next = NULL;
	arg_node->prev = NULL;
	return (arg_node);
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
	new->prev = last_node;
}

void	ft_lst_del_node(t_arg **lst, t_arg *node)
{
	t_arg	*aux1;
	t_arg	*aux2;

	if (!node)
		return ;
	aux2 = node->next;
	if (node->prev)
	{
		aux1 = node->prev;
		if (aux2)
			aux2->prev = aux1;
		aux1->next = aux2;
	}
	else
	{
		*lst = aux2;
		if (aux2)
			aux2->prev = NULL;
	}
	free(node->str);
	free(node);
}

void	ft_free_arg_list(t_arg **lst)
{
	t_arg	*aux;
	t_arg	*next;

	if (!lst)
		return ;
	aux = *lst;
	while (aux)
	{
		next = aux->next;
		if (aux->str)
			free(aux->str);
		free(aux);
		aux = next;
	}
	*lst = NULL;
}
