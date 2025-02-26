/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeckham <ppeckham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 13:32:55 by ppeckham          #+#    #+#             */
/*   Updated: 2025/02/24 16:19:06 by ppeckham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	ft_minishell(char *str, char **env)
{
	t_env	*env_lst;
	t_arg	*arg_lst;

	env_lst = ft_get_env_lst(env);
	if (env_lst == NULL)
		return (false);
	arg_lst = ft_arg_lst(str, env_lst);
	if (arg_lst == NULL)
	{
		ft_free_arg_list(&arg_lst);
		ft_free_env_list(&env_lst);
		return (false);
	}
	ft_free_arg_list(&arg_lst);
	ft_free_env_list(&env_lst);
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
