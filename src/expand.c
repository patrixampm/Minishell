/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeckham <ppeckham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 13:48:15 by ppeckham          #+#    #+#             */
/*   Updated: 2025/02/25 17:39:16 by ppeckham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_reset_expand_b(t_arg *arg_node)
{
	arg_node->has_expand = false;
	arg_node->valid_expand = false;
}

void	ft_reset_expand_s(t_arg *arg_node)
{
	if (arg_node->exp)
		free(arg_node->exp);
	if (arg_node->pre)
		free(arg_node->pre);
	if (arg_node->post)
		free(arg_node->post);
}

void	ft_reset_expand_s2(t_arg *arg_node)
{
	if (ft_strlen(arg_node->pre) == 0)
		arg_node->pre = NULL;
	if (ft_strlen(arg_node->exp) == 0)
		arg_node->exp = NULL;
	if (ft_strlen(arg_node->post) == 0)
		arg_node->post = NULL;
}

void	ft_check_expand(t_arg *nd, t_env *env_lst)
{
	t_env	*a;

	a = env_lst;
	while (a)
	{
		if (ft_strncmp(nd->exp, a->name, ft_strlen(a->name)) == 0
			&& ft_strlen(nd->exp) != 0
			&& ft_strlen(a->name) == ft_strlen(nd->exp))
		{
			nd->valid_expand = true;
			free(nd->exp);
			nd->exp = ft_strdup(a->content);
		}
		a = a->next;
	}
	if (!nd->valid_expand)
	{
		if (ft_strncmp("$", nd->exp, ft_strlen(nd->exp)) == 0)
			return ;
		else
		{
			free(nd->exp);
			nd->exp = NULL;
		}
	}
}
