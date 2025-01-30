/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeckham <ppeckham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 10:56:50 by ppeckham          #+#    #+#             */
/*   Updated: 2025/01/30 13:50:17 by ppeckham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_get_type(char *str, char c, int i)
{
	int		type;

	type = -1;
	if (ft_isalpha(c) == 1)
		return (type = 0);
	if (c == '\'')
		return (type = 1);
	if (c == '"')
		return (type = 2);
	if (c == '<' && str[i + 1] == '<')
		return (type = 4);
	if (c == '<')
		return (type = 3);
	if (c == '>' && str[i + 1] == '>>')
		return (type = 6);
	if (c == '<')
		return (type = 5);
	if (c == '|')
		return (type = 7);
	return (-1);
}

t_arg	*ft_create_arg_lst(char *str)
{
	t_arg	*arg_node;
	int		i;
	int		j;
	int		type;

	ft_new_arg(arg_node);
	type = ft_get_type(str, str[0], 0);
	i = 0;
	while (str[i])
	{
		
	}
}

void	ft_arg_lst(char *str)
{
	t_arg	*arg_lst;

	arg_lst = ft_create_arg_lst(str);
	if (!arg_lst)
		return ;
}
