/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_struct_a.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeckham <ppeckham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 10:56:50 by ppeckham          #+#    #+#             */
/*   Updated: 2025/02/12 11:22:50 by ppeckham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_create_arg_lst(char *str, t_arg **arg_lst)
{
	t_arg	*arg_node;
	int		i;

	arg_node = NULL;
	i = 0;
	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		arg_node = ft_new_arg(arg_node);
		arg_node->type = ft_get_type(str, str[i], &i);
		if (arg_node->type == -1)
		{
			free(arg_node);
			return (ft_free_arg_list(arg_lst));
		}
		if (!ft_set_argstr(arg_node, str, &i))
		{
			free(arg_node);
			break ;
		}
		ft_add_arg_back(arg_lst, arg_node);
		if (!str[i - 1])
			break ;
	}
}

void	ft_print_lst(t_arg **arg_lst)
{
	t_arg	*aux;
	int		i;

	aux = *arg_lst;
	i = 0;
	while (aux->next)
	{
		printf("node %d str: %s\n", i, aux->str);
		printf("node %d len: %d\n", i, aux->len);
		printf("node %d type: %d\n", i, aux->type);
		i++;
		aux = aux->next;
	}
	printf("node %d str: %s\n", i, aux->str);
	printf("node %d len: %d\n", i, aux->len);
	printf("node %d type: %d\n", i, aux->type);
}

bool	ft_arg_lst(char *str)
{
	t_arg	*arg_lst;

	arg_lst = NULL;
	ft_create_arg_lst(str, &arg_lst);
	if (arg_lst != NULL)
		ft_print_lst(&arg_lst);
	if (!arg_lst)
	{
		ft_free_arg_list(&arg_lst);
		return (false);
	}
	else
		return (true);
}
