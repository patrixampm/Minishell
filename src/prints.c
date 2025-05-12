/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrl <aehrl@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 09:40:22 by aehrl             #+#    #+#             */
/*   Updated: 2025/05/08 13:39:50 by aehrl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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