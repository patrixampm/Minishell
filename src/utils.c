/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrl <aehrl@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 17:26:13 by aehrl             #+#    #+#             */
/*   Updated: 2025/06/03 17:20:39 by aehrl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_arg_number(char **args, int expect)
{
	int	i;
	
	i = 0;
	while (args[i])
		i++;
	if (expect != 0 && i > expect)
	{
		printf("TESTING ERROR\n Invalid argument: %s\n", args[i]);
		return (-1);
	}
	return (i);
}

int	ft_proc_lstsize(t_proc **lst)
{
	int		i;
	t_proc	*aux;

	aux = *lst;
	i = 0;
	while (aux)
	{
		i++;
		aux = aux->next;
	}
	return (i);
}

int	ft_matrix_size(char **matrix)
{
	int	i;

	i = 0;
	if (!matrix)
		return (-1);
	while(matrix && matrix[i])
		i++;
	return (i);
}

void	ft_free_matrix(char **matrix)
{
	int	i;
	int	size;

	i = 0;
	if (!matrix)
		return ;
	size = ft_matrix_size(matrix);
	if (matrix && matrix != NULL)
	{
		while (i < size && matrix[i])
		{
			free(matrix[i]);
			i++;
		}
		free(matrix);
		matrix = NULL;
	}
}

/* t_pipex	ft_init_pipex(t_proc *p, t_env	**exp)
{
	t_pipex	pipex;
	t_proc	*aux;
	int		i;

	aux = p;
	i = 0;
	pipex.iter = 0;
	pipex.p_count = ft_proc_lstsize(&p);
	while (i++ < pipex.p_count - 1)
	{
		pipex.pipes[pipex.p_count] = (int *)malloc(2 * sizeof(int));
		if (!pipex.pipes[pipex.p_count]
			|| pipe(pipex.pipes[pipex.p_count]) == -1)
			(perror("Pipe error: pipe[i]\n"),
				exit(EXIT_FAILURE));
				//ft_free_pipex(pipex), exit(EXIT_FAILURE));
	}
	pipex.pids = (pid_t *)malloc((pipex.cmd_count) * sizeof(pid_t));
	if (!pipex.pids)
		(perror("Malloc failed\n"), exit(EXIT_FAILURE));
		//(perror("Malloc failed\n"), ft_free_pipex(pipex), exit(EXIT_FAILURE));
	pipex.all_paths = NULL;
	pipex.exp = exp;
	pipex.cmd_args = p->args;
	pipex.clean_path = NULL;
	pipex.status = 0;
	return (pipex);
} */
t_pipex	ft_init_pipex(t_proc *p, t_info *info)
{
	t_pipex	pipex;
	t_proc	*aux;
	int		i;

	aux = p;
	i = 0;
	pipex.iter = 0;
	pipex.p_count = ft_proc_lstsize(&p);
	pipex.out = 1;
	if (pipex.p_count >= 1)
	{
		pipex.pids = (pid_t *)malloc((pipex.p_count) * sizeof(pid_t));
		if (!pipex.pids)
			(perror("Malloc failed\n"), exit(EXIT_FAILURE));
	}
	pipex.all_paths = NULL;
	pipex.exp = &info->exp;
	pipex.cmd_args = p->args;
	pipex.clean_path = NULL;
	pipex.status = info->prev_exit;
	return (pipex);
}
