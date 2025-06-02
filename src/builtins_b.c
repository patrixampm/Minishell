/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_b.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeckham <ppeckham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 19:06:33 by aehrl             #+#    #+#             */
/*   Updated: 2025/06/02 17:36:43 by ppeckham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_search_export_unset(t_env **exp, char *name)
{
	t_env	*aux;
	t_env	*prev;

	aux = *exp;
	prev = NULL;
	while (aux)
	{
		if (ft_strncmp(aux->name, name, ft_strlen(name) + 1) == 0)
		{
			if (prev)
				prev->next = aux->next;
			else
				*exp = aux->next;
			free(aux->name);
			if (aux->content)
				free(aux->content);
			free(aux);
			return ;
		}
		prev = aux;
		aux = aux->next;
	}
}

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
		if (ft_strncmp(aux->name, name, ft_strlen(name)) == 0)
		{
			if (value)
			{
				free(aux->content);
				aux->content = ft_strdup(value);
			}
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
	char	*name;
	char	*content;
	int		env_loc;
	int		i;

	i = 0;
	while (arg[i]!= '=' && arg[i] != '\0')
		i++;
	name = ft_substr(arg, 0, i);
	if (ft_strchr(arg, '='))
	{
		content = ft_strchr(arg, '=');
		ft_search_export(exp, name, (content + 1));
		env_loc = ft_builtin_unset_checker(*env, name);
		*env = ft_env_add_or_set(*env, env_loc, name, (content + 1));
	}
	else
		ft_search_export(exp, arg, NULL);
	free(name);
}

void	ft_builtin_export(t_proc *p, char ***env, t_env **exp, t_pipex *px)
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
		if (p->args[i][0] > 20 && p->args[i][0] < 58)
		{
			if (p->args[i][0] == '-')
			{
				px->status = 2;
				printf("export: \'-%c\': invalid option\n", p->args[i][1]);
			}
			else
			{
				px->status = 1;
				printf("export: \'%s\': not a valid identifier\n", p->args[i]);
			}
			return ;
		}
		ft_export_add_or_set(exp, p->args[i], env);
		i++;
	}
}
