/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_a.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrl <aehrl@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:28:18 by aehrl             #+#    #+#             */
/*   Updated: 2025/05/13 20:36:56 by aehrl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_builtin_check(t_proc *proc)
{	
	int len;
	len = ft_strlen(proc->args[0]);
	if (len == 2 && !ft_strncmp(proc->args[0], "cd", len))
		proc->is_builtin = true;
	else if (len == 3 && (!ft_strncmp(proc->args[0], "env", len)
			|| !ft_strncmp(proc->args[0], "pwd", len)))
		proc->is_builtin = true;
	else if (len == 4 && (!ft_strncmp(proc->args[0], "echo", len)
			|| !ft_strncmp(proc->args[0], "exit", len)))
		proc->is_builtin = true;
	else if (len == 5 && !ft_strncmp(proc->args[0], "unset", len))
		proc->is_builtin = true;
	else if (len == 6 && !ft_strncmp(proc->args[0], "export", len))
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
		if (j != ft_strlen(p->args[i])|| p->args[1][0] != '-')
			break ;
		i++;
	}
	while (p->args[i])
	{
		printf("%s",p->args[i]);
		if (p->args[i + 1])
			printf(" ");
		i++;
	}
	if (p->has_flags == false)
		printf("\n");
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

char	**ft_builtin_unset_env(char **env, int loc)
{
	char	**temp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	temp = ft_calloc(sizeof(char *), ft_matrix_size(env));
	while (env[i])
	{
		if (i == loc)
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

void	ft_builtin_unset(t_proc *p ,char ***env, t_env **exp)
{	
	int		i;
	int		check;

	i = 1;
	while (p->args[i])
	{
		check = ft_builtin_unset_checker(*env, p->args[i]);
		printf("check = %d\n", check);
		if (check == -1)
			ft_search_export_unset(exp, p->args[i]);
		else
		{
			*env = ft_builtin_unset_env(*env, check);
			ft_search_export_unset(exp, p->args[i]);
		}
		i++;
	}
}

void	ft_builtin_execute(t_proc *p, char ***env, t_env **exp, t_pipex *pipex)
{	
	int	arg_len;

	arg_len = ft_strlen(p->args[0]);
	if (!ft_strncmp(p->args[0], "pwd", ft_strlen(p->args[0])))
		ft_buitlin_pwd(p);
	else if (!ft_strncmp(p->args[0], "echo", ft_strlen(p->args[0])))
		ft_builtin_echo(p);
	else if (!ft_strncmp(p->args[0], "env", ft_strlen(p->args[0])))
		ft_print_matrix(*env);
	else if (!ft_strncmp(p->args[0], "unset", ft_strlen(p->args[0])))
		ft_builtin_unset(p, env, exp);
	else if (!ft_strncmp(p->args[0], "export", ft_strlen(p->args[0])))
		ft_builtin_export(p, env, exp); 
	(void)pipex;
	/*else if (!ft_strncmp(p->args[0], "cd", ft_strlen(p->args[0])))
		ft_builtin_cd(t_proc *p);
	else if (!ft_strncmp(proc->args[0], "exit", ft_strlen(proc->args[0])))
		ft_builtin_exit(t_proc *proc); */
}
