/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeckham <ppeckham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 09:40:22 by aehrl             #+#    #+#             */
/*   Updated: 2025/05/26 12:58:23 by ppeckham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_printerr(char *str, char *arg, int errnum, t_pipex *px)
{
	if (arg)
		printf("%s: %s\n", str, arg);
	else
		printf("%s\n", str);
	px->status = errnum;
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

void	ft_print_export_lst(t_env **exp_lst)
{
	t_env	*aux;

	aux = *exp_lst;
	while (aux)
	{
		if (aux && aux->content != NULL)
		{
			printf("declare -x %s=", aux->name);
			printf("\"%s\"\n", aux->content);
		}
		else if (aux)
			printf("declare -x %s\n", aux->name);
		aux = aux->next;
	}
}

void	ft_print_pipex(t_pipex *pipex)
{
	int	i;

	i = 0;
	ft_putstr_fd("\ncommand count:\n", 2);
	ft_putnbr_fd(pipex->cmd_count, 2);
	ft_putstr_fd("\nproccess count:\n", 2);
	ft_putnbr_fd(pipex->p_count, 2);
	ft_putstr_fd("\ncommands:\n", 2);
	while (pipex->cmd_args[i])
	{
		ft_putendl_fd(pipex->cmd_args[i], 2);
		i++;
	}
	ft_putstr_fd("pipex iterator:", 2);
	ft_putnbr_fd(pipex->iter, 2);
	/*ft_putstr_fd("\npipex pipefd[0]:", 2);
	 ft_putnbr_fd(pipex->pipes[0], 2);
	ft_putstr_fd("\npipex pipefd[1]:", 2);
	ft_putnbr_fd(pipex->pipes[1], 2);*/
	ft_putstr_fd("\npipex status:", 2); 
	ft_putnbr_fd(pipex->status, 2);
	ft_putstr_fd("\n", 2);
}

void	ft_error_message(int error, char **path)
{
	ft_putstr_fd(strerror(error), 2);
	if (path)
		ft_free_matrix(path);
}

void	ft_print_dup2err(t_pipex *px)
{
    if (errno == EBADF)
    {
        printf("dup2: Bad file descriptor\n");
        px->status = 1;
    }
    else if (errno == EINTR)
    {
        printf("dup2: Interrupted by signal\n");
        px->status = 4;
    }
    else if (errno == EMFILE)
    {
        printf("dup2: Too many open files\n");
        px->status = 24;
    }
    else
    {
        printf("dup2\n");
        px->status = 1;
    }
	exit(px->status);
}

void	ft_print_execve_err(t_pipex *px, char *arg)
{
    if (errno == EACCES)
    {
        printf("%s: Permission denied\n", arg);
        px->status = 126;
    }
    else if (errno == ENOEXEC)
    {
        printf("%s: Exec format error\n", arg);
        px->status = 126;
    }
    else if (errno == EISDIR)
    {
        printf("%s: is a directory\n", arg);
        px->status = 126;
    }
    else
	{
		printf("%s: command not found\n", arg);
        px->status = 127;
	}
	exit(px->status);
}
