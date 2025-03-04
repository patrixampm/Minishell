/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_struct_a.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeckham <ppeckham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 10:56:50 by ppeckham          #+#    #+#             */
/*   Updated: 2025/03/03 12:40:24 by ppeckham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_node_n_list(t_arg **lst, t_arg *node)
{
	if (node)
		free(node);
	if (lst)
		ft_free_arg_list(lst);
	else
		lst = NULL;
}

void	ft_print_arg_lst(t_arg **arg_lst)
{
	t_arg	*aux;
	int		i;

	aux = *arg_lst;
	i = 0;
	while (aux)
	{
		printf("node %d str: %s\n", i, aux->str);
		printf("node %d len: %d\n", i, aux->len);
		printf("node %d type: %d\n", i, aux->type);
		printf("node %d job: %c\n", i, aux->job);
		printf("node %d has expand: %d\n", i, aux->has_expand);
		printf("node %d has valid expand: %d\n", i, aux->valid_expand);
		printf("--------------------------\n");
		i++;
		aux = aux->next;
	}
}

void	ft_create_arg_lst(char *str, t_arg **arg_lst, t_env *env_lst)
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
			ft_free_node_n_list(arg_lst, arg_node);
			break ;
		}
		if (!ft_set_arg_str(arg_node, str, &i, env_lst))
		{
			ft_free_arg_list(arg_lst);
			break ;
		}
		ft_add_arg_back(arg_lst, arg_node);
		if (i >= ft_strlen(str))
			break ;
	}
}

t_arg	*ft_arg_lst(char *str, t_env *env_lst)
{
	t_arg	*arg_lst;
	t_arg	*aux;
	t_arg	*next;

	arg_lst = NULL;
	ft_create_arg_lst(str, &arg_lst, env_lst);
	if (arg_lst == NULL)
		return (NULL);
	aux = arg_lst;
	while (aux)
	{
		next = aux->next;
		if (aux->str == NULL && (aux->next || aux->prev))
			ft_lst_del_node(&arg_lst, aux);
		aux = next;
	}
	// ft_print_arg_lst(&arg_lst);
	return (arg_lst);
}
