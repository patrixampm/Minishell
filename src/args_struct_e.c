/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_struct_e.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeckham <ppeckham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 13:40:58 by ppeckham          #+#    #+#             */
/*   Updated: 2025/02/26 13:59:34 by ppeckham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_iter_n_check(char *s, int j, int *k, t_arg *node)
{
	while (s[*k] && s[*k] != '$' && s[*k] != '\''
		&& s[*k] != '"' && s[*k] != ' ')
		*k = *k + 1;
	if (s[j] == '$' && (s[j + 1] == '\''
			|| s[j + 1] == '"' || s[j + 1] == '\0'))
		node->exp = ft_strdup("$");
	else
		node->exp = ft_substr(s, j + 1, *k - (j + 1));
}

int	ft_pre_n_exp1(char *s, t_arg *node, int *i, int j)
{
	int	k;

	node->has_expand = true;
	k = j + 1;
	node->pre = ft_substr(s, *i + 1, j - (*i + 1));
	ft_iter_n_check(s, j, &k, node);
	return (k);
}

int	ft_pre_n_exp2(char *s, t_arg *node, int *i, int j)
{
	int	k;

	node->has_expand = true;
	k = j + 1;
	node->pre = ft_substr(s, *i, j - *i);
	ft_iter_n_check(s, j, &k, node);
	return (k);
}

void	ft_iter_k(char *s, int *i, int *k)
{
	while (s[*k] && s[*k] != s[*i])
		*k = *k + 1;
}

void	ft_check_n_iter(char *s, int *i, int j, int *k)
{
	if (s[j] != s[*i] && s[*k] != '\0')
		*k = *k + 1;
}
