/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_struct_c.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrl <aehrl@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:13:28 by ppeckham          #+#    #+#             */
/*   Updated: 2025/03/12 13:44:23 by aehrl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_prev_type_3to5(t_arg *aux, t_proc *process)
{
	if (aux->prev->type == 3)
	{
		if (process->infile)
			free(process->infile);
		process->infile = ft_strdup(aux->str);
		process->infd = open(process->infile, O_RDONLY);
	}
	else if (aux->prev->type == 4)
	{
		if (process->infile)
			free(process->infile);
		process->infile = ft_strdup(aux->str);
		process->hd = true;
	}
	else if (aux->prev->type == 5)
	{
		if (process->outfile)
			free(process->outfile);
		process->outfile = ft_strdup(aux->str);
		process->outfd = open(process->outfile, O_WRONLY | O_CREAT, 0744);
		process->append = false;
	}
}

void	ft_prev_type_6or7(t_arg *aux, t_proc *process, int *i)
{
	if (aux->prev->type == 6)
	{
		if (process->outfile)
			free(process->outfile);
		process->outfile = ft_strdup(aux->str);
		process->outfd = open(process->outfile, O_WRONLY | O_CREAT | O_APPEND,
				0744);
		process->append = true;
	}
	else if (aux->prev->type == 7 && aux->type < 3)
	{
		process->args[*i] = ft_strdup(aux->str);
		*i += 1;
	}
}

void	ft_word_type(t_arg *aux, t_arg *prev, t_proc *process, int *i)
{
	if (aux->type > 2)
		aux = aux->next;
	else if (aux->type < 3)
	{
		if (prev == NULL)
		{
			process->args[*i] = ft_strdup(aux->str);
			*i += 1;
		}
		else if (prev->type == 3 || prev->type == 4
			|| prev->type == 5)
			ft_prev_type_3to5(aux, process);
		else if (prev->type == 6 || prev->type == 7)
			ft_prev_type_6or7(aux, process, i);
		else
		{
			process->args[*i] = ft_strdup(aux->str);
			*i += 1;
			if (*i != 0)
				process->has_flags = true;
		}
		aux = aux->next;
	}
}

t_proc	*ft_create_proc(t_proc **proc_lst, t_ms *ms)
{
	t_arg	*aux;
	t_proc	*process;
	int		i;

	aux = ms->arg_lst;
	while (aux)
	{
		process = ft_new_proc(process);
		i = 0;
		if (aux->type == 7)
			aux = aux->next;
		ft_memset_cmds(aux, process);
		if (aux->job == 'C')
			ft_builtin_check(aux, process);
		while (aux && aux->job != 'p')
		{
			ft_word_type(aux, aux->prev, process, &i);
			aux = aux->next;
		}
		ft_add_proc_back(proc_lst, process);
		if (aux == NULL)
			break ;
		else
			aux = aux->next;
	}
	return (*proc_lst);
}
