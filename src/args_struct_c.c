/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_struct_c.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeckham <ppeckham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 16:30:16 by ppeckham          #+#    #+#             */
/*   Updated: 2025/02/11 15:53:22 by ppeckham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_check_if_first_i(t_arg *arg_node)
{
	if (arg_node->end == 0)
		arg_node->str = arg_node->temp;
	else
		arg_node->str = ft_strjoin(arg_node->str, arg_node->temp);
}

void	ft_free_aux_str(t_strqt *qt, t_strqt *s)
{
	if (qt || s)
	{
		free(qt);
		free(s);
	}
}

bool	ft_check_quote(char *str, int start, t_strqt *qt)
{
	int	j;

	j = start;
	qt->start = 0;
	while (str[j] && str[j] != ' ' && str[j] != '\0')
	{
		if (str[j] == '\'' || str[j] == '"')
		{
			qt->start = j;
			return (true);
		}
		j++;
	}
	return (false);
}

bool	ft_check_q_end(char *str, int *i, char c, t_strqt *qt)
{
	int	j;

	j = *i;
	j++;
	while (str[j])
	{
		if (str[j] == c)
		{
			if (qt)
			{
				qt->end = j;
				qt->len = j - (qt->start + 1);
			}
			return (true);
		}
		j++;
	}
	return (false);
}

int	ft_get_s_end(char *str, int s_start)
{
	int	i;

	i = s_start;
	i++;
	while (str[i] && str[i] != ' ' && str[i] != '\'' && str[i] != '"')
		i++;
	return (i);
}
