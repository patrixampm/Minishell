/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_struct_c.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeckham <ppeckham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 16:30:16 by ppeckham          #+#    #+#             */
/*   Updated: 2025/03/10 11:55:26 by ppeckham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	ft_qt(char *str, int *i, t_arg *node, t_env *env)
{
	if (str[*i] == '\'')
		ft_simple_qt(str, i, node);
	else
		ft_double_qt(str, i, node, env);
	return (true);
}

void	ft_expand_str(t_arg *arg_node)
{
	ft_reset_expand_s2(arg_node);
	if (!arg_node->pre && !arg_node->exp && !arg_node->post)
		arg_node->temp = NULL;
	if (arg_node->pre && arg_node->exp && arg_node->post)
	{
		arg_node->temp2 = ft_join_free(arg_node->pre, arg_node->exp);
		arg_node->temp = ft_join_free(arg_node->temp2, arg_node->post);
	}
	else if (arg_node->pre && arg_node->exp && !arg_node->post)
		arg_node->temp = ft_join_free(arg_node->pre, arg_node->exp);
	else if (arg_node->pre && !arg_node->exp && arg_node->post)
		arg_node->temp = ft_join_free(arg_node->pre, arg_node->post);
	else if (!arg_node->pre && arg_node->exp && arg_node->post)
		arg_node->temp = ft_join_free(arg_node->exp, arg_node->post);
	else
	{
		if (!arg_node->pre && arg_node->exp && !arg_node->post)
			arg_node->temp = ft_strdup(arg_node->exp);
		else if (!arg_node->pre && !arg_node->exp && arg_node->post)
			arg_node->temp = ft_strdup(arg_node->post);
		else if (arg_node->pre && !arg_node->exp && !arg_node->post)
			arg_node->temp = ft_strdup(arg_node->pre);
		ft_reset_expand_s(arg_node);
	}
}

void	ft_reset_str_temp(t_arg *arg_node)
{
	if (ft_strlen(arg_node->str) == 0)
		arg_node->str = NULL;
	if (ft_strlen(arg_node->temp) == 0)
		arg_node->temp = NULL;
}

void	ft_form_str(t_arg *arg_node)
{
	char	*temp2;

	temp2 = NULL;
	if (ft_strlen(arg_node->str) == 0 && ft_strlen(arg_node->temp) == 0)
		return ;
	ft_reset_str_temp(arg_node);
	if (arg_node->str)
	{
		if (ft_strlen(arg_node->temp) == 0)
		{
			temp2 = ft_strdup(arg_node->str);
			free(arg_node->str);
		}
		else
			temp2 = ft_join_free(arg_node->str, arg_node->temp);
		arg_node->str = ft_strdup(temp2);
		free(temp2);
	}
	else if (!arg_node->str)
	{
		arg_node->str = ft_strdup(arg_node->temp);
		free(arg_node->temp);
	}
	ft_reset_str_temp(arg_node);
	arg_node->len = ft_strlen(arg_node->str);
}
