/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrl <aehrl@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:29:31 by aehrl             #+#    #+#             */
/*   Updated: 2025/04/07 18:45:47 by aehrl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*ft_set_export_lst(t_env **lst, char **env)
{
	t_env	*node;
	char	*name;
	char	*content;
	int		i;
	int		j;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] != '=' && env[i][j] != '\0')
			j++;
		if (env[i][j] != '\0')
		{
			name = ft_substr(env[i], 0, j);
			j++;
			content = ft_substr(env[i], j, ft_strlen(env[i]));
			node = ft_new_env(name, content);
		}
		else
			node = ft_new_env(env[i], NULL);
		ft_add_env_back(lst, node);
		i++;
	}
	return (*lst);
}

t_env	*ft_get_export_lst(char **env)
{
	t_env	*export_lst;

	export_lst = NULL;
	export_lst = ft_set_export_lst(&export_lst, env);
	if (!export_lst)
	{
		ft_free_env_list(&export_lst);
		return (NULL);
	}
	else
		return (export_lst);
}

t_env	*ft_create_export_lst(char **env)
{
	t_env	*env_lst;
	t_env	*export_lst;
	t_env	*new_node;
	t_env	*env_aux;
	t_env	*exp_aux;
	int		check;

	env_lst = ft_get_export_lst(env);
	env_aux = env_lst;
	new_node = ft_new_env(env_aux->name, env_aux->content);
	ft_add_env_back(&export_lst, new_node);
	env_aux = env_aux->next;
	while (env_aux)
	{
		exp_aux = export_lst;
		new_node = ft_new_env(env_aux->name, env_aux->content);
		check = ft_strncmp(new_node->name, exp_aux->name, ft_strlen(new_node->name)); // not sure if we should be looking at aux->name, or new_node_name
		if (check < 0)
			ft_add_env_front(&export_lst, new_node);
		else
		{
			while (check > 0 && exp_aux->next != NULL)
			{
				check = ft_strncmp(new_node->name, exp_aux->next->name, ft_strlen(new_node->name));
				if (check > 0) 
					exp_aux = exp_aux->next;
			}
			ft_slipin_node_env(exp_aux, new_node);
		}
		env_aux = env_aux->next;
	}
	return (export_lst);
}