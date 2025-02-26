/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_struct_d.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeckham <ppeckham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 17:30:02 by ppeckham          #+#    #+#             */
/*   Updated: 2025/02/26 14:00:08 by ppeckham         ###   ########.fr       */
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

void	ft_simple_qt(char *str, int *i, t_arg *node)
{
	int			j;

	j = *i + 1;
	while (str[j] != str[*i] && j < ft_strlen(str))
		j++;
	node->temp = ft_substr(str, *i + 1, j - (*i + 1));
	*i = j;
}

void	ft_end_here(t_arg *node, int *i, int k)
{
	ft_expand_str(node);
	*i = k - 1;
	return ;
}

void	ft_double_qt(char *s, int *i, t_arg *node, t_env *env_lst)
{
	int		j;
	int		k;

	j = *i + 1;
	while (s[j] != s[*i] && j < ft_strlen(s))
	{
		if (s[j] == '$')
		{
			k = ft_pre_n_exp1(s, node, i, j);
			ft_check_expand(node, env_lst);
			if (s[k] == '$' || (s[k] == '\'' && ft_check_qt_closure(s, k)))
				return (ft_end_here(node, i, k));
			j = k;
			ft_check_n_iter(s, i, j, &k);
			if (s[k] == '$')
				return (ft_end_here(node, i, k));
			ft_iter_k(s, i, &k);
			node->post = ft_substr(s, j, k - j);
			if (s[j] == s[*i])
				break ;
		}
		j++;
	}
	ft_compose_temp1(node, s, i, j);
}

void	ft_no_qt(char *s, int *i, t_arg *node, t_env *env_lst)
{
	int			j;
	int			k;

	j = *i;
	while (j <= ft_strlen(s) && s[j] != '\'' && s[j] != '"' && s[j] != ' ')
	{
		if (s[j] == '$')
		{
			k = ft_pre_n_exp2(s, node, i, j);
			ft_check_expand(node, env_lst);
			if (s[k] == '$' || s[k] == ' ')
				return (ft_end_here(node, i, k));
			else if (s[k] && (s[k] == '\'' || s[k] == '"'))
				k++;
			if (s[k] == '$')
				return (ft_end_here(node, i, k));
			j = k;
			while (s[k] && s[k] != '\'' && s[k] != '"' && s[k] != ' ')
				k++;
			node->post = ft_substr(s, j, k - j);
		}
		j++;
	}
	ft_compose_temp2(node, s, i, j);
}
