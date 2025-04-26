/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrl <aehrl@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 17:26:13 by aehrl             #+#    #+#             */
/*   Updated: 2025/04/26 18:58:36 by aehrl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_arg_number(char **args, int expect)
{
	int	i;
	
	i = 0;
	while (args[i])
		i++;
	if (expect != 0 && i > expect)
	{
		printf("TESTING ERROR\n Invalid argument: %s\n", args[i]);
		return (-1);
	}
	return (i);
}

int	ft_proc_lstsize(t_proc **lst)
{
	int		i;
	t_proc	*aux;

	aux = *lst;
	i = 0;
	while (aux)
	{
		i++;
		aux = aux->next;
	}
	return (i);
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

void	ft_print_matrix(char **matrix)
{
	int	i;

	i = 0;
	while(matrix[i])
	{
		printf("%s\n", matrix[i]);
		i++;
	}
}

void	ft_print_export_lst(t_env **exp_lst)
{
	t_env	*aux;

	aux = *exp_lst;
	while (aux)
	{
		if (aux && aux->content != NULL)
		{
			printf("declare -x %s=", aux->name);
			printf("\"%s\"\n", aux->content);
		}
		else if (aux)
			printf("declare -x %s\n", aux->name);
		aux = aux->next;
	}
}
