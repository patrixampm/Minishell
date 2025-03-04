/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeckham <ppeckham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 14:21:29 by ppeckham          #+#    #+#             */
/*   Updated: 2025/03/04 10:35:36 by ppeckham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_give_job(t_arg *node)
{
	t_arg	*prev;
	t_arg	*next;

	prev = node->prev;
	next = node->next;
	if (prev != NULL)
	{
		if (prev->type == 3)
			node->job = 'I';
		else if (prev->type == 4)
			node->job = 'D';
		else if (prev->type == 5)
			node->job = 'O';
		else if (prev->type < 3 || prev->type == 7)
		{
			if ((next && next->type == 5))
				node->job = 'I';
			else
				node->job = 'C';
		}
		else
			node->job = 'X';
	}
	else
		node->job = 'C';
}

void	ft_arg_jobs(t_ms *ms)
{
	t_arg	*aux;

	aux = ms->arg_lst;
	while (aux)
	{
		if (aux->type == 3)
			aux->job = 'i';
		if (aux->type == 4)
			aux->job = 'h';
		if (aux->type == 5)
			aux->job = 'o';
		if (aux->type == 6)
			aux->job = 'a';
		if (aux->type == 7)
			aux->job = 'p';
		if (aux->type < 3)
			ft_give_job(aux);
		aux = aux->next;
	}
}

void	ft_chunks(t_ms *ms)
{
	ft_arg_jobs(ms);
	// AQUÍ DEBERÍA CHECKEAR YA SI HAY ALGO RARO COMO UNA PIPE AL PRINCIPIO DE LA LISTA
	// O SI HAY DOS PIPAS SEGUIDAS (BÁSICAMENTE CUALQUIER COSA QUE NO ACEPTE
	// BASH) Y DEVOLVER UN MENSAJE DE ERROR CORRECTO
	// ft_check_basic_order(ms)
	//ft_create_chunks(ms);
}