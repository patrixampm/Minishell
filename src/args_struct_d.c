/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_struct_d.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeckham <ppeckham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 17:30:02 by ppeckham          #+#    #+#             */
/*   Updated: 2025/02/25 17:43:58 by ppeckham         ###   ########.fr       */
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


void	ft_double_qt(char *s, int *i, t_arg *node, t_env *env_lst)
{
	int		j;
	int		k;

	j = *i + 1;
	while (s[j] != s[*i] && j < ft_strlen(s))
	{
		if (s[j] == '$')
		{
			node->has_expand = true;
			k = j + 1;
			node->pre = ft_substr(s, *i + 1, j - (*i + 1));
			while (s[k] && s[k] != '$' && s[k] != '\'' && s[k] != '"' && s[k] != ' ')
				k++;
			if (s[j] == '$' && (s[j + 1] == '\'' || s[j + 1] == '"' || s[j + 1] == '\0'))
				node->exp = ft_strdup("$");
			else
				node->exp = ft_substr(s, j + 1, k - (j + 1));
			ft_check_expand(node, env_lst);
			if (s[k] == '$' || (s[k] == '\'' && ft_check_qt_closure(s, k)))
			{
				ft_expand_str(node);
				*i = k - 1;
				return ;
			}
			j = k;
			if (s[j] != s[*i] && s[k] != '\0')
				k++;
			if (s[k] == '$')
			{
				ft_expand_str(node);
				*i = k - 1;
				return ;
			}
			while (s[k] && s[k] != s[*i])
				k++;
			node->post = ft_substr(s, j, k - j);
			if (s[j] == s[*i])
				break ;
			
		}
		j++;
	}
	if (!node->has_expand)
		ft_simple_qt(s, i, node);
	else
	{
		ft_expand_str(node);
		*i = j;
	}
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
			node->has_expand = true;
			k = j + 1;
			node->pre = ft_substr(s, *i, j - *i);
			while (s[k] && s[k] != '$' && s[k] != '\'' && s[k] != '"' && s[k] != ' ')
				k++;
			if (s[j] == '$' && (s[j + 1] == '\'' || s[j + 1] == '"' || s[j + 1] == '\0'))
				node->exp = ft_strdup("$");
			else
				node->exp = ft_substr(s, j + 1, k - (j + 1));
			ft_check_expand(node, env_lst);
			if (s[k] == '$' || s[k] == ' ')
			{
				ft_expand_str(node);
				*i = k - 1;
				return ;
			}
			else if (s[k] && (s[k] == '\'' || s[k] == '"'))
				k++;
			if (s[k] == '$')
			{
				ft_expand_str(node);
				*i = k - 1;
				return ;
			}
			j = k;
			while (s[k] && s[k] != '\'' && s[k] != '"' && s[k] != ' ')
				k++;
			node->post = ft_substr(s, j, k - j);
		}
		j++;
	}
	if (!node->has_expand)
	{
		node->temp = ft_substr(s, *i, (j - *i));
		*i = j - 1;
	}
	else
	{
		ft_expand_str(node);
		*i = j;
	}
}
