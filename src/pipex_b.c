/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_b.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrl <aehrl@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:11:38 by aehrl             #+#    #+#             */
/*   Updated: 2025/05/08 13:05:29 by aehrl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_dup2(int input_fd, int output_fd)
{
	if (input_fd != STDIN_FILENO)
	{
		if (dup2(input_fd, STDIN_FILENO) == -1)
			(close(output_fd), close(input_fd), exit(1));
		close(input_fd);
	}
	if (output_fd != STDOUT_FILENO)
	{
		if (dup2(output_fd, STDOUT_FILENO) == -1)
			(close(output_fd), exit(1));
		close(output_fd);
	}
}

int	ft_set_infd(int pipein, int pipeout)
{
	close(pipeout);
	return (pipein);
}

char	*ft_get_path(char **envp, char *cmnd)
{
	int		i;
	char	*path;

	i = 0;
	if (!cmnd)
		return (NULL);
	if (ft_strrchr(cmnd, '/'))
		return (cmnd);
	while (envp[i])
	{
		path = ft_strjoin(ft_strjoin(envp[i], "/"), cmnd);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

void	read_input_limiter(t_proc *p)
{
	char	*input;
	int		fd;

	fd = open("here_doc", O_RDWR, S_IRWXU);
	while (1)
	{
		write(1, "here_doc> ", 10);
		input = get_next_line(0);
		if (input && ft_strlen(input) - 1 != ft_strlen(p->args[0]))
			ft_putstr_fd(input, fd);
		else if (input
			&& ft_strncmp(input, p->args[0], ft_strlen(p->args[0])) != 0)
			ft_putstr_fd(input, fd);
		else
			break ;
		free(input);
	}
	if (!input)
	{
		unlink("here_doc");
		exit(2);
	}
	free(input);
	close(fd);
}
/* void	read_input_limiter(int i, char *argv[])
{
	char	*input;
	int		fd;

	fd = open(argv[i], O_RDWR, S_IRWXU);
	while (1)
	{
		write(1, "here_doc> ", 10);
		input = get_next_line(0);
		if (input && ft_strlen(input) - 1 != ft_strlen(argv[i + 1]))
			ft_putstr_fd(input, fd);
		else if (input
			&& ft_strncmp(input, argv[i + 1], ft_strlen(argv[i + 1])) != 0)
			ft_putstr_fd(input, fd);
		else
			break ;
		free(input);
	}
	if (!input)
	{
		unlink("here_doc");
		exit(2);
	}
	free(input);
	close(fd);
} */

void	del_heredoc(t_proc *p)
{
	bool	check;
	t_proc	*aux;

	aux = p;
	while(aux)
	{
		if (aux->hd == true)
			check = true;
	}
	if (p->hd == true || check == true)
		unlink("here_doc");
}
