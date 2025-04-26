/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_b.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrl <aehrl@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 19:06:33 by aehrl             #+#    #+#             */
/*   Updated: 2025/04/26 18:57:20 by aehrl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// step 1 figure out a alphabetized copy algorythm for the export
//  --> For this it might be usefull to use the lists
// --> when initializing the list add declare -x (honestly could just add this to a print function)
// step 2 when I add to the export without a value it just adds to the export (without =) (in alphabetical order)
// step 3 when I add a value to a name it adds it to the env (last item) and either updates or adds to the export


//figure out a way to set USER and then set 
void	ft_search_export(t_env **exp, char	*name, char	*value)
{
	int		i;
	t_env	*aux;
	t_env	*node;

	i = 0;
	aux = *exp;
	if (ft_search_export_front(exp, name, value) == 1)
		return ;
	while (aux)
	{
		if (ft_strncmp(aux->name, name, ft_strlen(name)) == 0 && value)
		{
			free(aux->content);
			aux->content = ft_strdup(value);
			return ;
		}
		if (ft_search_export_slipin(exp, name, value) == 1)
			return ;
		aux = aux->next; 
	}
	if (value)
		node = ft_new_env(ft_strdup(name), ft_strdup(value));
	else
		node = ft_new_env(ft_strdup(name), NULL);
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
		free(env[i]);
		env[i] = ft_strjoin(aux, value);
		free(aux);
		return (env);
	}
	i = 0;
	size = ft_matrix_size(env);
	temp = (char **)ft_calloc(size + 2, sizeof(char *));
	while (i < size)
	{
		temp[i] = ft_strdup(env[i]);
		i++;
	}
	temp[i] = ft_strjoin(aux, value);
	free(aux);
	ft_free_matrix(env);
	return (temp);
}

void	ft_export_add_or_set(t_env **exp, char *arg, char ***env)
{
	char	**command;
	int		env_loc;
	int		i;
	char	*new_arg;

	i = 1;
	new_arg = ft_strdup(arg);
	if (ft_strchr(new_arg, '='))
	{
		command = ft_split(new_arg, '=');
		while (command[i])
			i++;
		while (--i > 1)
			command[i - 1] = ft_strjoin(command[i - 1], command[i]);
		ft_search_export(exp, command[0], command[1]);
		env_loc = ft_builtin_unset_checker(*env, command[0]);
		*env = ft_env_add_or_set(*env, env_loc, command[0], command[1]);
		ft_free_matrix(command);
	}
	else
		ft_search_export(exp, new_arg, NULL);
	free(new_arg);
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
				printf("export: \'-%c\'\n: invalid option", p->args[i][1]);
			else
				printf("export: \'%s\'\n: not a valid identifier", p->args[i]);
			return ; //set errno and break process
		}
		ft_export_add_or_set(exp, p->args[i], env);
		i++;
	}
}
