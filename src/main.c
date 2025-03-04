/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeckham <ppeckham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 13:32:55 by ppeckham          #+#    #+#             */
/*   Updated: 2025/03/04 10:49:28 by ppeckham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	ft_minishell(char *str, char **env)
{
	t_ms	*ms;

	ms = malloc(sizeof(t_ms));
	if (ms == NULL)
		return (false);
	ms->env_lst = ft_get_env_lst(env);
	if (ms->env_lst == NULL)
		return (false);
	ms->arg_lst = ft_arg_lst(str, ms->env_lst);
	if (ms->arg_lst == NULL)
	{
		ft_free_arg_list(&ms->arg_lst);
		ft_free_env_list(&ms->env_lst);
		free(ms);
		return (false);
	}
	ft_chunks(ms);
	ft_print_arg_lst(&ms->arg_lst);
	ft_free_arg_list(&ms->arg_lst);
	ft_free_env_list(&ms->env_lst);
	free(ms);
	return (true);
}

int	main(int ac, char **av, char **env)
{
	char	*str;

	(void)av;
	if (ac == 1)
	{
		while (1)
		{
			str = readline("Minishell:>");
			add_history(str);
			if (!ft_strncmp(str, "EXIT", 5))
				break ;
			if (!ft_minishell(str, env))
			{
				free(str);
				return (1);
			}
			free(str);
		}
	}
	else
		return (1);
	free(str);
	return (0);
}
