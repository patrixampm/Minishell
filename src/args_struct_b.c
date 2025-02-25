/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_struct_b.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeckham <ppeckham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 16:32:31 by ppeckham          #+#    #+#             */
/*   Updated: 2025/02/25 17:40:59 by ppeckham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_get_type(char *str, char c, int *i)
{
	int		type;

	type = -1;
	if (ft_isalpha(c) == 1 || c == '$')
		return (type = 0);
	if (c == '\'')
		return (type = 1);
	if (c == '"')
		return (type = 2);
	if (str[*i + 1] && c == '<' && str[*i + 1] == '<')
		return (type = 4);
	if (c == '<')
		return (type = 3);
	if (str[*i + 1] && c == '>' && str[*i + 1] == '>')
		return (type = 6);
	if (c == '>')
		return (type = 5);
	if (c == '|')
		return (type = 7);
	return (type);
}

bool	ft_set_simple_str(t_arg *arg_node, char *str, int *i, int len)
{
	int	k;

	k = *i;
	arg_node->str = ft_substr(str, k, len);
	arg_node->len = len;
	return (true);
}

bool	ft_set_alt_str(char *str, int *i, t_arg *arg_node, t_env *env_lst)
{
	bool is_end;

	is_end = false;
	while (!is_end)
	{
		ft_reset_expand_b(arg_node);
		if (str[*i] == '\'' || str[*i] == '"')
		{
			if (!ft_check_closure(str, i, arg_node))
				return (false);
			ft_qt(str, i, arg_node, env_lst);
		}
		else
			ft_no_qt(str, i, arg_node, env_lst);
		ft_form_str(arg_node);
		if (*i >= (ft_strlen(str)))
			return (true);
		if (*i >= arg_node->end && (str[*i + 1] == '\0' || str[*i + 1] == ' '))
			is_end = true;
		else if (*i >= arg_node->end && str[*i + 1] && str[*i + 1] != ' ')
			arg_node->end = 0;
		*i = *i + 1;
	}
	return (true);
}

bool	ft_set_arg_str(t_arg *arg_node, char *str, int *i, t_env *env_lst)
{
	if (arg_node->type < 3)
	{
		if (!ft_set_alt_str(str, i, arg_node, env_lst))
			return (false);
	}
	else if (arg_node->type == 3 || arg_node->type == 5 || arg_node->type == 7)
	{
		if (!ft_set_simple_str(arg_node, str, i, 1))
			return (false);
		(*i)++;
	}
	else if (arg_node->type == 4 || arg_node->type == 6)
	{
		if (!ft_set_simple_str(arg_node, str, i, 2))
			return (false);
		*i += 2;
	}
	else
		return (false);
	return (true);
}
