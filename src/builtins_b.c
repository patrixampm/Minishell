/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_b.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrl <aehrl@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 19:06:33 by aehrl             #+#    #+#             */
/*   Updated: 2025/04/07 18:39:53 by aehrl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// step 1 figure out a alphabetized copy algorythm for the export
//  --> For this it might be usefull to use the lists
// --> when initializing the list add declare -x (honestly could just add this to a print function)
// step 2 when I add to the export without a value it just adds to the export (without =) (in alphabetical order)
// step 3 when I add a value to a name it adds it to the env (last item) and either updates or adds to the export


//figure out a way to set USER and then set 


void	ft_add_env_front(t_env **lst, t_env *new)
{
	t_env	*aux;
	
	aux = new;
	if (!new || !lst)
		return ;
	aux->next = *lst;
	*lst = aux;
}

/* void	ft_add_node_env_back(t_env **lst, t_env *new)
{
	t_env	*aux;
	t_env	*last_node;
	
	aux = new;
	if (!new || !lst)
		return ;
	aux->next = NULL;
	last_node = ft_last_env(*lst);
	last_node->next = aux;
} */

void	ft_slipin_node_env(t_env *a, t_env *b)
{
	/* t_env	*c;

	c = a->next; */
	b->next = a->next;
	a->next = b;

}
