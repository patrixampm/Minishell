/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeckham <ppeckham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:29:31 by aehrl             #+#    #+#             */
/*   Updated: 2025/05/20 19:02:10 by ppeckham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_add_env_front(t_env **lst, t_env *new)
{
	t_env	*aux;
	
	aux = new;
	if (!new || !lst)
		return ;
	aux->next = *lst;
	*lst = aux;
}

void	ft_slipin_node_env(t_env *a, t_env *b)
{
	/* t_env	*c;

	c = a->next; */
	b->next = a->next;
	a->next = b;
}

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

t_env	*ft_create_export_lst(char **env, t_env *export_lst)
{
	t_env	*env_lst;
	t_env	*node;
	t_env	*aux;
	t_env	*exp_aux;
	int		check;

	env_lst = ft_get_export_lst(env);
	aux = env_lst;
	node = ft_new_env(ft_strdup(aux->name), ft_strdup(aux->content));
	ft_add_env_back(&export_lst, node);
	aux = aux->next;
	while (aux)
	{
		exp_aux = export_lst;
		node = ft_new_env(ft_strdup(aux->name), ft_strdup(aux->content));
		check = ft_strncmp(node->name, exp_aux->name, ft_strlen(node->name)); // not sure if we should be looking at aux->name, or node_name
		if (check < 0)
			ft_add_env_front(&export_lst, node);
		else
		{
			while (check > 0 && exp_aux->next != NULL)
			{
				check = ft_strncmp(node->name, exp_aux->next->name, ft_strlen(node->name));
				if (check > 0) 
					exp_aux = exp_aux->next;
			}
			ft_slipin_node_env(exp_aux, node);
		}
		aux = aux->next;
	}
	return (ft_free_env_list(&env_lst), export_lst); // change export setup to use strdup and them free env_lst
}
