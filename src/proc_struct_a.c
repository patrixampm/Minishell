/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_struct_a.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeckham <ppeckham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 14:21:29 by ppeckham          #+#    #+#             */
/*   Updated: 2025/03/11 15:06:40 by ppeckham         ###   ########.fr       */
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
		else if (prev->type == 5 || prev->type == 6)
			node->job = 'O';
		else if (prev->type < 3 || prev->type == 7)
			node->job = 'C';
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

void	ft_memset_cmds(t_arg *head, t_proc *process)
{
	t_arg	*aux;
	int		count;

	aux = head;
	count = 0;
	while (aux && aux->job != 'p')
	{
		if (aux->job == 'C')
			count++;
		aux = aux->next;
	}
	if (count > 0)
	{
		process->args = malloc(sizeof(char *) * (count + 1));
		process->args[count] = NULL;
	}
	else
		process->args = NULL;
}

void	ft_print_proc_lst(t_proc **proc_lst)
{
	t_proc	*aux;
	int		i;

	aux = *proc_lst;
	while (aux)
	{
		i = 0;
		if (aux->args)
		{
			while (aux->args[i])
			{
				printf("arg[%d]: %s\n", i, aux->args[i]);
				i++;
			}
		}
		printf("infile: %s infd: %d\n", aux->infile, aux->infd);
		printf("outfile: %s outfd: %d\n", aux->outfile, aux->outfd);
		printf("append?: %d\n", aux->append);
		printf("hd?: %d\n", aux->hd);
		printf("has_flags?: %d\n", aux->has_flags);
		printf("exit_status: %d\n", aux->exit_status);
		printf("--------------------------------------\n");
		aux = aux->next;
	}
}

t_proc	*ft_proc(t_ms *ms)
{
	t_proc	*proc_lst;

	proc_lst = NULL;
	ft_arg_jobs(ms);
	if (!ft_check_syntax_errors(ms->arg_lst))
		return (NULL);
	proc_lst = ft_create_proc(&proc_lst, ms);
	if (proc_lst == NULL)
	{
		ft_free_proc_lst(&proc_lst);
		return (NULL);
	}
	return (proc_lst);
}
