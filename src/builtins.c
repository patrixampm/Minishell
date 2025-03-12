/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrl <aehrl@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:28:18 by aehrl             #+#    #+#             */
/*   Updated: 2025/03/12 19:53:16 by aehrl            ###   ########.fr       */
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
	// Problem with mnultiple spaces before the first input (GENERAL PROBLEM)
	// Problem with \t & \n not executing at all
	//->SUGESTION add a char *input for whole command that I acces to check 
	// ENTERS ARE SEEN AS OPERATIONS IN LOG OF TERMINAL (NOT THE CASE IN ORIGINAL)
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

void	ft_builtin_unset(t_proc *p , t_env *env_lst)
{
	t_env	*temp;
	int		i;

	temp = env_lst;
	i = 0;
	while (p->args[i] && i <= 2)
		i++;
	if (i > 2)
	{
		printf("TESTING ERROR\n Invalid argument: %s\n", p->args[i]);
		return ;
	}
	i--;
	while (temp)
	{
		if (!ft_strncmp(temp->name, p->args[i], ft_strlen(p->args[i])))
		{
			printf("unset: %s\n",temp->content);
			ft_env_del_node(&temp, temp->name);
			return ;
		}
		temp = temp->next;
	}
}

void	ft_builtin_execute(t_proc *proc, t_ms *ms)
{
	if (!ft_strncmp(proc->args[0], "pwd", ft_strlen(proc->args[0])))
		ft_buitlin_pwd(ms->env_lst);
	else if (!ft_strncmp(proc->args[0], "echo", ft_strlen(proc->args[0])))
		ft_builtin_echo(proc);
	else if (!ft_strncmp(proc->args[0], "env", ft_strlen(proc->args[0])))
		ft_print_env_lst(&ms->env_lst); // // ADD CHECK FOR PROC to see if flags are given (if so fail)
	else if (!ft_strncmp(proc->args[0], "unset", ft_strlen(proc->args[0])))
		ft_builtin_unset(proc ,ms->env_lst);
	/*else if (!ft_strncmp(proc->args[0], "cd", ft_strlen(proc->args[0])))
		ft_builtin_cd(t_proc *proc);
	else if (!ft_strncmp(proc->args[0], "export", ft_strlen(proc->args[0])))
		ft_builtin_export(t_proc *proc);
	else if (!ft_strncmp(proc->args[0], "exit", ft_strlen(proc->args[0])))
		ft_builtin_export(t_proc *proc); */
}