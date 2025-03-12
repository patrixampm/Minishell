/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrl <aehrl@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:15:27 by ppeckham          #+#    #+#             */
/*   Updated: 2025/03/12 13:54:48 by aehrl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_proc	*ft_new_proc(t_proc *proc_node)
{
	proc_node = malloc(sizeof(t_proc));
	if (!proc_node)
		return (NULL);
	proc_node->args = NULL;
	proc_node->infile = NULL;
	proc_node->infd = 0;
	proc_node->outfile = NULL;
	proc_node->outfd = 0;
	proc_node->append = false;
	proc_node->hd = false;
	proc_node->has_flags = false;
	proc_node->exit_status = 0;
	proc_node->is_builtin = false;
	proc_node->next = NULL;
	return (proc_node);
}

t_proc	*ft_last_proc(t_proc *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

void	ft_add_proc_back(t_proc **lst, t_proc *new)
{
	t_proc	*last_node;

	if (!new || !lst)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last_node = ft_last_proc(*lst);
	last_node->next = new;
}

void	ft_free_proc_node(t_proc *node)
{
	int		i;

	if (!node)
		return ;
	i = 0;
	if (node->args != NULL)
	{
		while (node->args[i] != NULL)
		{
			free(node->args[i]);
			i++;
		}
	}
	if (node->infile)
		free(node->infile);
	if (node->outfile)
		free(node->outfile);
	free(node);
}

void	ft_free_proc_lst(t_proc **lst)
{
	t_proc	*aux;
	t_proc	*next;
	int		i;

	if (!lst)
		return ;
	aux = *lst;
	while (aux)
	{
		i = 0;
		next = aux->next;
		while (aux->args[i])
		{
			free(aux->args[i]);
			i++;
		}
		free(aux->args);
		free(aux->infile);
		free(aux->outfile);
		free(aux);
		aux = next;
	}
	*lst = NULL;
}
