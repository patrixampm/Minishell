/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrl <aehrl@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:28:18 by aehrl             #+#    #+#             */
/*   Updated: 2025/03/14 21:23:39 by aehrl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
// change ms to specific argl_list
void	ft_builtin_check(t_arg *arg, t_proc *proc)
{
	if (arg->len == 2 && !ft_strncmp(arg->str, "cd", arg->len))
		proc->is_builtin = true;
	else if (arg->len == 3 && (!ft_strncmp(arg->str, "env", arg->len)
			|| !ft_strncmp(arg->str, "pwd", arg->len)))
		proc->is_builtin = true;
	else if (arg->len == 4 && (!ft_strncmp(arg->str, "echo", arg->len)
			|| !ft_strncmp(arg->str, "exit", arg->len)))
		proc->is_builtin = true;
	else if (arg->len == 5 && !ft_strncmp(arg->str, "unset", arg->len))
		proc->is_builtin = true;
	else if (arg->len == 6 && !ft_strncmp(arg->str, "export", arg->len))
		proc->is_builtin = true;
}



void	ft_buitlin_pwd(t_env *env_lst)
{
	t_env *temp;

	temp = env_lst;
	// ADD CHECK FOR PROC to see if flags are given (if so fail)
	while (temp)
	{
		if (!ft_strncmp(temp->name, "PWD", 3))
		{
			printf("%s\n", temp->content);
			return ;
		}
		temp = temp->next;
	}
}

void	ft_builtin_echo(t_proc *p)
{
	int	i;
	int	j;

	i = 1;
	while (p->has_flags == true)
	{
		j = 1;
		while (p->args[i][j] != '\0' && p->args[i][j] == 'n')
			j++;
		if ((i == 1 && j < ft_strlen(p->args[i])) || p->args[i][0] != '-')
			p->has_flags = false;
		if (j != ft_strlen(p->args[i]))
			break ;
		i++;
	}
	while (p->args[i])
	{
		ft_putstr_fd(p->args[i], 1);
		if (p->args[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (p->has_flags == false)
		ft_putstr_fd("\n", 1);
}

int	ft_builtin_unset_checker(char **env, char *unset)
{
	int		i;
	char	*temp;

	i = 0;
	temp = ft_strjoin(unset, "=");
	while (env[i])
	{
		if (!ft_strncmp(env[i], temp, ft_strlen(temp)))
		{
			free(temp);
			return (i);
		}
		i++;
	}
	free(temp);
	return (-1);
}

char	**ft_builtin_unset(t_proc *p ,char **env)
{	
	char	**temp;
	int		i;
	int		check;
	int		j;

	check = ft_builtin_unset_checker(env, p->args[1]);
	if (ft_check_arg_number(p->args, 2) == -1 || check == -1)
		return (env);
	j = 0;
	i = 0;
	temp = ft_calloc(sizeof(char *), ft_matrix_size(env));
	while (env[i])
	{
		if (i == check)
			i++;
		else if (env[i])
		{
			temp[j] = ft_strdup(env[i]);
			j++;
			i++;
		}
	}
	ft_free_matrix(env);
	return (temp);
}

void	ft_print_matrix(char **matrix)
{
	int	i;

	i = 0;
	while(matrix[i])
	{
		printf("%s\n", matrix[i]);
		i++;
	}
}


void	ft_builtin_execute(t_proc *proc, t_ms *ms, char ***env)
{	
	if (!ft_strncmp(proc->args[0], "pwd", ft_strlen(proc->args[0])))
		ft_buitlin_pwd(ms->env_lst);
	else if (!ft_strncmp(proc->args[0], "echo", ft_strlen(proc->args[0])))
		ft_builtin_echo(proc);
	else if (!ft_strncmp(proc->args[0], "env", ft_strlen(proc->args[0])))
		ft_print_matrix(*env); 
	else if (!ft_strncmp(proc->args[0], "unset", ft_strlen(proc->args[0])))
		*env = ft_builtin_unset(proc, *env);
	/*else if (!ft_strncmp(proc->args[0], "cd", ft_strlen(proc->args[0])))
	ft_builtin_cd(t_proc *proc);
	else if (!ft_strncmp(proc->args[0], "env", ft_strlen(proc->args[0])))
		ft_print_env_lst(&ms->env_lst); 
	else if (!ft_strncmp(proc->args[0], "export", ft_strlen(proc->args[0])))
		ft_builtin_export(t_proc *proc);
	else if (!ft_strncmp(proc->args[0], "exit", ft_strlen(proc->args[0])))
		ft_builtin_export(t_proc *proc); */
}