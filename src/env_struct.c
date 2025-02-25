/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_struct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeckham <ppeckham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:25:42 by ppeckham          #+#    #+#             */
/*   Updated: 2025/02/12 13:15:12 by ppeckham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_print_env_lst(t_env **env_lst)
{
	t_env	*aux;

	aux = *env_lst;
	while (aux->next)
	{
		printf("node name: %s\n", aux->name);
		printf("node content: %s\n", aux->content);
		aux = aux->next;
	}
	printf("node name: %s\n", aux->name);
	printf("node content: %s\n", aux->content);
}

t_env	*ft_create_env_lst(t_env **lst, char **env)
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
		while (env[i][j] != '=')
			j++;
		name = ft_substr(env[i], 0, j);
		j++;
		content = ft_substr(env[i], j, ft_strlen(env[i]));
		node = ft_new_env(name, content);
		ft_add_env_back(lst, node);
		i++;
	}
	return (*lst);
}

t_env	*ft_get_env_lst(char **env)
{
	t_env	*env_lst;

	env_lst = NULL;
	env_lst = ft_create_env_lst(&env_lst, env);
	// if (env_lst != NULL)
	// 	ft_print_env_lst(&env_lst);
	if (!env_lst)
	{
		ft_free_env_list(&env_lst);
		return (NULL);
	}
	else
		return (env_lst);
}
