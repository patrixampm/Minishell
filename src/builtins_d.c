/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrl <aehrl@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:07:25 by ppeckham          #+#    #+#             */
/*   Updated: 2025/06/04 17:52:25 by aehrl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_update_pwd_oldpwd(t_env **exp, char ***env, char *cwd)
{
	char	*new;
	char	*temp;

	new = getcwd(NULL, 0);
	temp = ft_strjoin("PWD=", new);
	ft_export_add_or_set(exp, temp, env);
	free(temp);
	temp = ft_strjoin("OLDPWD=", cwd);
	ft_export_add_or_set(exp, temp, env);
	free(temp);
	free(new);
}

void	ft_only_cd(t_env *exp, char ***env, t_pipex *px, char *pwd)
{
	char	*home;

	home = ft_get_exp_content(exp, "HOME");
	if (home == NULL)
		ft_printerr("cd: HOME not set", NULL, 1, px);
	else
	{
		chdir(home);
		ft_update_pwd_oldpwd(&exp, env, pwd);
	}
}

void	ft_builtin_cd(t_proc *p, char ***env, t_env **exp, t_pipex *px)
{
	char			*current_d;

	current_d = getcwd(NULL, 0);
	if (!p->args[1])
		ft_only_cd(*exp, env, px, current_d);
	else
	{
		if (p->args[2])
			ft_printerr("cd: too many arguments", NULL, 1, px);
		else if (chdir(p->args[1]) == -1)
		{
			printf("cd: %s: %s\n", p->args[1], strerror(errno));
			px->status = 1;
		}
		else
			ft_update_pwd_oldpwd(exp, env, current_d);
	}
	free(current_d);
}

bool	ft_check_numeric(char *num)
{
	int	i;

	i = 0;
	if (num[i] == '+' || num[i] == '-')
		i++;
	if (!num[i])
		return (false);
	while (num[i])
	{
		if (!ft_isdigit(num[i]))
			return (false);
		i++;
	}
	if (i == 0)
		return (false);
	return (true);
}

void	ft_exit_with_num(t_pipex *px, t_proc*p)
{
	long long	num;

	num = ft_atoi(p->args[1]);
	if (num > 255)
		px->status = num % 256;
	else if (num < 0)
		px->status = 256 + (num % 256);
	else
	{
		px->status = num;
		exit(num);
	}
}

void	ft_builtin_exit(t_proc *p, t_pipex *px)
{
	if (!p->args[1])
	{
		px->status = 0;
		exit(0);
	}
	else if (!ft_check_numeric(p->args[1]))
	{
		ft_printerr("exit: numeric argument required", NULL, 2, px);
		px->status = 2;
		exit(2);
	}
	else if (p->args[2])
		ft_printerr("exit: too many arguments", NULL, 1, px);
	else
		ft_exit_with_num(px, p);
}
