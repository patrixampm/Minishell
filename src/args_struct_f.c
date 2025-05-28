/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_struct_f.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeckham <ppeckham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:00:16 by ppeckham          #+#    #+#             */
/*   Updated: 2025/05/28 18:27:56 by ppeckham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_handle_exp(char *exp, char *s, int i, int k)
{
	if (s[k - 2] == '$' && s[k - 1] == '?')
		exp = ft_strdup("$?");
	else if (s[k - 1] == '$' && !s[k])
		exp = ft_strdup("$");
	else
		exp = ft_substr(s, i + 1, k - (i + 1));
	return (exp);
}

char	*ft_pre_n_exp3(char *s, int i, t_info *info)
{
	char	*pre;
	char	*exp;
	int		k;
	bool	valid;

	valid = false;
	exp = NULL;
	if (s[i - 1] == '\'' || s[i - 1] == '"')
		pre = ft_substr(s, 0, i - 1);
	else
		pre = ft_substr(s, 0, i);
	k = i + 1;
	while (s[k] != '\0' && s[k] != '$' && s[k] != '\''
		&& s[k] != '"' && s[k] != ' ')
		k++;
	exp = ft_handle_exp(exp, s, i, k);
	exp = ft_check_expand2(exp, info, valid);
	if (ft_strlen(pre) != 0 && ft_strlen(exp) != 0)
		return (free(s), s = ft_join_free(pre, exp));
	else if (ft_strlen(exp) == 0)
		return (free (s), pre);
	else
		return (free(s), exp);
}

int	ft_check_post(t_arg *node, t_info *info, int j)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	while (node->post[x] != '\0')
		x++;
	while (node->post[i] != '$' && i < x)
		i++;
	if (i == x)
		return (x + j);
	else
	{
		node->post = ft_pre_n_exp3(node->post, i, info);
		return (j + x);
	}
}
