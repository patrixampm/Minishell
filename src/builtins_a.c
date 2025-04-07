/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_a.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrl <aehrl@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:28:18 by aehrl             #+#    #+#             */
/*   Updated: 2025/04/07 17:17:57 by aehrl            ###   ########.fr       */
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


void	ft_buitlin_pwd(t_proc *p)
{
	char	*aux;
	
	// might wanna handle this with error code 2 (eg give this a int return)
	if (p->args[1])
	{
		if (p->args[1][0] == '-' && p->args[1][1] != '\0')
		{
			printf("pwd: -%c: invalid option\n", p->args[1][1]); //check if this is correct
			return ;
		}
	}
	aux = getcwd(NULL, 0);
	printf("%s\n", aux);
	free(aux);
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
		if ((i == 1 && j < ft_strlen(p->args[i])) || p->args[1][0] != '-')
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
// need to add exp and delete from export list as well
char	**ft_builtin_unset(t_proc *p ,char **env)
{	
	char	**temp;
	int		i;
	int		check;
	int		j;

	check = ft_builtin_unset_checker(env, p->args[1]);
	if (ft_check_arg_number(p->args, 2) == -1 || check == -1) //check this as we can do multiple unsets at once
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

void	ft_builtin_execute(t_proc *proc, char ***env, t_env **exp)
{	
	if (!ft_strncmp(proc->args[0], "pwd", ft_strlen(proc->args[0])))
		ft_buitlin_pwd(proc);
	else if (!ft_strncmp(proc->args[0], "echo", ft_strlen(proc->args[0])))
		ft_builtin_echo(proc);
	else if (!ft_strncmp(proc->args[0], "env", ft_strlen(proc->args[0])))
		ft_print_matrix(*env); 
	else if (!ft_strncmp(proc->args[0], "unset", ft_strlen(proc->args[0])))
		*env = ft_builtin_unset(proc, *env);
	else if (!ft_strncmp(proc->args[0], "export", ft_strlen(proc->args[0])))
		ft_builtin_export(proc, env, exp); //Need to add env 
	/*else if (!ft_strncmp(proc->args[0], "cd", ft_strlen(proc->args[0])))
	ft_builtin_cd(t_proc *proc);
	else if (!ft_strncmp(proc->args[0], "exit", ft_strlen(proc->args[0])))
		ft_builtin_export(t_proc *proc); */
}