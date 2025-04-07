/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrl <aehrl@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 13:32:55 by ppeckham          #+#    #+#             */
/*   Updated: 2025/04/07 18:42:43 by aehrl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_free_ms(t_ms *ms)
{
	ft_free_arg_list(&ms->arg_lst);
	ft_free_env_list(&ms->env_lst);
	if (ms->proc_lst != NULL)
		ft_free_proc_lst(&ms->proc_lst);
	free(ms->str);
	free(ms);
}

bool	ft_minishell(char *str, char ***env, t_env **exp)
{
	t_ms	*ms;

	ms = malloc(sizeof(t_ms));
	ms->proc_lst = NULL;
	if (ms == NULL)
		return (false);
	ms->env_lst = ft_get_env_lst(*env);
	if (ms->env_lst == NULL)
		return (false);
	ms->str = ft_strdup(str);
	ms->arg_lst = ft_arg_lst(str, ms->env_lst);
	if (ms->arg_lst == NULL)
		return (ft_free_ms(ms), false);
	ms->proc_lst = ft_proc(ms);
	if (ms->proc_lst == NULL)
		return (ft_free_ms(ms), false);
	ft_print_arg_lst(&ms->arg_lst);
	ft_print_proc_lst(&ms->proc_lst);
	ft_builtin_execute(ms->proc_lst, env, exp);
	//ft_excecute(ms->proc_lst, env);
	return (ft_free_ms(ms), true);
}

	
	
int	main(int ac, char **av, char **env)
{
	char	*str;
	char 	**new_env;
	t_env	*exp;
	
	new_env = ft_create_env(env, &exp);
	if (!exp)
		exp = ft_create_export_lst(new_env);
	(void)av;
	//ft_print_export_lst(&exp);
	if (ac == 1)
	{
		while (1)
		{
			str = readline("Minishell:>");
			add_history(str);
			if (!ft_strncmp(str, "EXIT", 5))
				break ;
			ft_minishell(str, &new_env, &exp);
			free(str);
		}
	}
	else
		return (1);
	ft_free_matrix(new_env);
	//ft_free_env_list(&exp);
	return (free(str), 0);
}
