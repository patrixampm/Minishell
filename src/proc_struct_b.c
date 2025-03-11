/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_struct_b.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeckham <ppeckham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 11:12:33 by ppeckham          #+#    #+#             */
/*   Updated: 2025/03/11 15:05:27 by ppeckham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_print_err(int n, t_arg *a)
{
	if (n == 1 || n == 2 || (n == 4 && a->next->type == 7))
		printf("ms: syntax error near unexpected token '|'\n");
	else if (n == 3)
		printf("ms: syntax error near unexpected token 'newline'\n");
	else if (n == 4)
	{
		if (a->next->type < 3)
			printf("ms: syntax error near unexpected token '%s'\n", a->str);
		else
			printf("ms: syntax error near unexpected token '%s'\n",
				a->next->str);
	}
}

bool	ft_check_syntax_errors(t_arg *lst)
{
	t_arg	*a;
	t_arg	*prev;
	t_arg	*next;

	a = lst;
	while (a)
	{
		prev = a->prev;
		next = a->next;
		if (a->job == 'p' && (prev == NULL || next == NULL))
			return (ft_print_err(1, a), false);
		else if (a->job == 'p' && (prev->type > 2 || next->type == 7))
			return (ft_print_err(2, a), false);
		else if (next == NULL && (a->type > 2 && a->type < 7))
			return (ft_print_err(3, a), false);
		else if (prev && (a->type > 2 && a->type < 7)
			&& ((prev->type > 2 && prev->type < 7)
				|| (next->type > 2 && next->type <= 7)))
			return (ft_print_err(4, a), false);
		a = a->next;
	}
	return (true);
}
