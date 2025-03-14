/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrl <aehrl@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 17:26:13 by aehrl             #+#    #+#             */
/*   Updated: 2025/03/14 21:24:27 by aehrl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_arg_number(char **args, int expect)
{
	int	i;
	
	i = 0;
	while (args[i] && i <= expect)
		i++;
	if (i > expect)
	{
		printf("TESTING ERROR\n Invalid argument: %s\n", args[i]);
		return (-1);
	}
	return (0);
}

int	ft_matrix_size(char **matrix)
{
	int	i;

	i = 0;
	while(matrix[i])
		i++;
	return (i);
}

void	ft_free_matrix(char **matrix)
{
	int	i;
	int	size;

	i = 0;
	size = ft_matrix_size(matrix);
	if (matrix)
	{
		while (i < size && matrix[i])
		{
			free(matrix[i]);
			i++;
		}
		free(matrix);
		matrix = NULL;
	}
}