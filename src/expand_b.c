/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_b.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeckham <ppeckham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:55:34 by ppeckham          #+#    #+#             */
/*   Updated: 2025/05/27 17:01:29 by ppeckham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_check_expand3(t_env *exp, char *input)
{
	t_env	*a;
	int		i;

	i = 0;
	if (input && input[0] == '$')
	{
		a = exp;
		while (a)
		{
			if (ft_strncmp(ft_strtrim(input, "$"), a->name, ft_strlen(a->name)) == 0
				&& ft_strlen(input) != 0)
				return ((free(input), input = ft_strjoin(a->content, "\n")));
			a = a->next;
		}
	}
	return (input);
}
