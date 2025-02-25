/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeckham <ppeckham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 13:48:15 by ppeckham          #+#    #+#             */
/*   Updated: 2025/02/25 12:07:57 by ppeckham         ###   ########.fr       */
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
	if (arg_node->exp_str)
		free(arg_node->exp_str);
	if (arg_node->pre)
		free(arg_node->pre);
	if (arg_node->post)
		free(arg_node->post);
}

void	ft_reset_expand_s2(t_arg *arg_node)
{
	if (ft_strlen(arg_node->pre) == 0)
		arg_node->pre = NULL;
	if (ft_strlen(arg_node->exp_str) == 0)
		arg_node->exp_str = NULL;
	if (ft_strlen(arg_node->post) == 0)
		arg_node->post = NULL;
}

void	ft_reset_str_temp(t_arg *arg_node)
{
	if (ft_strlen(arg_node->str) == 0)
		arg_node->str = NULL;
	if (ft_strlen(arg_node->temp) == 0)
		arg_node->temp = NULL;
}

// void	ft_set_post(char *str, int j, int k, t_arg *node)
// {
// 	int	qt_count;
// 	int	i;

// 	qt_count = 0;
// 	i = j;
// 	while (i < ft_strlen(str))
// 	{
// 		if (str[i] == '\'' || str[i] == '"')
// 			qt_count++;
// 		i++;
// 	}
// 	if (qt_count % 2 == 0)
// 	{
// 		if (str[k + 1] == '\'' || str[k + 1] == '"')
// 			node->post = ft_substr(str, j, k - (j - 1));
// 		else
// 			node->post = ft_substr(str, j, (k - j));
// 	}
// 	else
// 		node->post = ft_substr(str, j, k - (j - 1));
// }

void	ft_check_expand(t_arg *nd, t_env *env_lst)
{
	t_env	*aux;

	aux = env_lst;
	nd->has_expand = true;
	while (aux)
	{
		if (ft_strncmp(nd->exp_str, aux->name, ft_strlen(aux->name)) == 0
			&& ft_strlen(nd->exp_str) != 0 && ft_strlen(aux->name) == ft_strlen(nd->exp_str))
		{
			nd->valid_expand = true;
			free(nd->exp_str);
			nd->exp_str = ft_strdup(aux->content);
		}
		aux = aux->next;
	}
	if (!nd->valid_expand)
	{
		if (ft_strncmp("$", nd->exp_str, ft_strlen(nd->exp_str)) == 0)
			return ;
		else
		{
			free(nd->exp_str);
			nd->exp_str = NULL;
		}
	}
}
