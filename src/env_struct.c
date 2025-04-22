/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_struct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrl <aehrl@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:25:42 by ppeckham          #+#    #+#             */
/*   Updated: 2025/04/15 11:26:09 by aehrl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_print_env_lst(t_env **env_lst)
{
	t_env	*aux;

	aux = *env_lst;
	while (aux)
	{
		printf("%s=", aux->name);
		printf("%s\n", aux->content);
		aux = aux->next;
	}
}
// need to create and ft_create_export_list becuse content might be null;
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
	if (!env_lst)
	{
		ft_free_env_list(&env_lst);
		return (NULL);
	}
	else
		return (env_lst);
}

char	**ft_set_global_env_exp(t_env **export)
{
	char	**path;
	char	*aux;
	char	*temp;
	t_env	*node;
	
	temp = "PATH=/usr/local/sbin:/usr/local/bin:";
	path = (char **)ft_calloc(sizeof(char *), 5);
	if (!path)
		return (NULL); // add error handiling 
	aux = getcwd(NULL, 0);
	path[0] = ft_strjoin("PWD=", aux);
	path[1] = ft_strjoin(temp, "/usr/sbin:/usr/bin:/sbin:/bin");
	path[2] = ft_strdup("SHLVL=1");
	path[3] = ft_strdup("_=/usr/bin/env");
	*export = ft_new_env(ft_strdup("OLDPWD"), NULL);
	node = ft_new_env(ft_strdup("PWD"), ft_strdup(aux)); 
	ft_add_env_back(export, node);
	node = ft_new_env(ft_strdup("SHLVL"), ft_strdup("1"));
	ft_add_env_back(export, node);
	free(aux);
	return (path);
}

char	**ft_create_env(char **env, t_env **export)
{
	int		i;
	char	**temp;

	i = 0;
	if (*env == NULL)
	{
		temp = ft_set_global_env_exp(export);
		return (temp);
	}
	temp = ft_calloc(ft_matrix_size(env) + 1, sizeof(char *));
	if (!temp)
		return (NULL);
	while(env[i])
	{
		if (!ft_strncmp(env[i], "_=", 2))
			temp[i] = ft_strdup("_=/usr/bin/env"); //might not need this
		else
			temp[i] = ft_strdup(env[i]);
		i++;
	}
	return (temp);
}
