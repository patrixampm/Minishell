/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeckham <ppeckham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 17:19:09 by ppeckham          #+#    #+#             */
/*   Updated: 2025/02/25 17:27:05 by ppeckham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	ft_check_closure(char *str, int *i, t_arg *node)
{
	int	j;

	j = *i + 1;
	while (str[j] != '\0')
	{
		if (str[j] == str[*i])
		{
			if (node->end == 0)
				node->end = j;
			return (true);
		}
		j++;
	}
	if (ft_strlen(node->str) != 0)
		free(node->str);
	free(node);
	return (false);
}

bool	ft_check_qt_closure(char *str, int k)
{
	int	j;

	j = k + 1;
	while (str[j] != '\0')
	{
		if (str[j] == str[k])
			return (true);
		j++;
	}
	return (false);
}
