/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeckham <ppeckham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:01:16 by ppeckham          #+#    #+#             */
/*   Updated: 2025/01/30 11:45:22 by ppeckham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*ft_new_env(char *name, char *content)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->name = name;
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}

t_env	*ft_last_env(t_env *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

void	ft_add_env_back(t_env **lst, t_env *new)
{
	t_env	*last_node;

	if (!new || !lst)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last_node = ft_last_env(*lst);
	last_node->next = new;
}

int	ft_env_lstsize(t_env **lst)
{
	int		i;
	t_env	*aux;

	aux = *lst;
	i = 0;
	while (aux)
	{
		i++;
		aux = aux->next;
	}
	return (i);
}

void	ft_free_env_list(t_env **lst)
{
	t_env	*aux;
	t_env	*next;

    if (!lst)
        return;

    aux = *lst;
    while (aux)
    {
		next = aux->next;
        free(aux->name);
        free(aux->content);
        free(aux);
        aux = next;
    }
    *lst = NULL;
}
