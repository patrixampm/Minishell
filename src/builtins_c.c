/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_c.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrl <aehrl@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 18:37:51 by aehrl             #+#    #+#             */
/*   Updated: 2025/04/07 18:50:41 by aehrl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_search_export(t_env **exp, char	*name, char	*value)
{
	int		i;
	t_env	*aux;
	t_env	*node;

	i = 0;
	aux = *exp;
	while (aux->next != NULL)
	{
		if (ft_strncmp(aux->name, name, ft_strlen(name)) == 0 && value)
		{
			//free(aux->content);
			aux->content = ft_strdup(value);
			return ;
		}
		if (ft_strncmp(aux->name, name, ft_strlen(name)) > 0)
		{
			node = ft_new_env(name, value);
			ft_slipin_node_env(aux, node);
			return ;
		}
		aux = aux->next; 
	}
	node = ft_new_env(name, value);
	printf("node name: %s content:%s\n",node->name, node->content);
	ft_add_env_back(exp, node);
}

char	**ft_env_add_or_set(char **env, int	i, char	*name, char	*value)
{
	char	**temp;
	char	*aux;
	int		size;

	aux = ft_strjoin(name, "=");
	if (i >= 0)
	{
		//free(env[i]);
		env[i] = ft_strjoin(aux, value);
	//	free(aux);
		return (env);
	}
	i = 0;
	size = ft_matrix_size(env);
	temp = (char **)ft_calloc(size + 1, sizeof(char *));
	while (i < size)
	{
		temp[i] = ft_strdup(env[i]);
		i++;
	}
	temp[i] = ft_strjoin(aux, value);
	//free(aux);
	ft_free_matrix(env);
	return (temp);
}

void	ft_export_add_or_set(t_env **exp, char *arg, char ***env)
{
	char	**command;
	int		env_loc;
	int		i;
	
	i = 1;
	if (ft_strchr(arg, '='))
	{
		command = ft_split(arg, '=');
		while (command[i])
			i++;
		while (--i > 1)
			command[i - 1] = ft_strjoin(command[i - 1], command[i]);
		ft_search_export(exp, command[0], command[1]);
		env_loc = ft_builtin_unset_checker(*env, command[0]);
		*env = ft_env_add_or_set(*env, env_loc, command[0], command[1]);
		// if more than one = is present it should join the strings into one
		//do add to exp and env
	}
	else
		ft_search_export(exp, arg, NULL);
}

void	ft_builtin_export(t_proc *p, char ***env, t_env **exp)
{
	int		i;
	int		size;
	t_env	*aux;

	i = 1;
	size = ft_check_arg_number(p->args, 0); //change how check_arg_num works (without expected int)
	aux = *exp;
	if (size == 1)
	{
		ft_print_export_lst(&aux);
		return ;
	}
	while (p->args[i])
	{
		if (p->args[i][0] == '-')
		{
			if (i == 1)
				printf("export: \'-%c\': invalid option", p->args[i][1]);
			else
				printf("export: \'-%s\': not a valid identifier", p->args[i]);
			return ; //set errno and break process
		}
		ft_export_add_or_set(exp, p->args[i], env);
		i++;
	}
}
