/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_c.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrl <aehrl@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 18:37:51 by aehrl             #+#    #+#             */
/*   Updated: 2025/04/10 16:12:19 by aehrl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_search_export_front(t_env **exp, char *name, char *value)
{
	t_env	*aux;
	t_env	*node;

	aux = *exp;
	if (ft_strncmp(aux->name, name, ft_strlen(name)) > 0 && value)
	{
		node = ft_new_env(ft_strdup(name), ft_strdup(value));
		ft_add_env_front(exp, node);
		return (1);
	}
	else if (ft_strncmp(aux->name, name, ft_strlen(name)) > 0)
	{
		node = ft_new_env(ft_strdup(name), NULL);
		ft_add_env_front(exp, node);
		return (1);
	}
	return (0);
}

int ft_search_export_slipin(t_env **exp, char *name, char *value)
{
	int	check;
	t_env	*aux;
	t_env	*node;

	aux = *exp;
	check = ft_strncmp(aux->next->name, name, ft_strlen(name));
	if (aux->next != NULL && check > 0 && value)
	{
		node = ft_new_env(ft_strdup(name), ft_strdup(value));
		ft_slipin_node_env(aux, node);
		return (1);
	}
	else if (aux->next != NULL && check > 0)
	{
		node = ft_new_env(ft_strdup(name), NULL);
		ft_slipin_node_env(aux, node);
		return (1);
	}
	return (0);
}
