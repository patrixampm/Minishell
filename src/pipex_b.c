/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_b.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeckham <ppeckham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:11:38 by aehrl             #+#    #+#             */
/*   Updated: 2025/05/29 13:26:45 by ppeckham         ###   ########.fr       */
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
	char	*aux;

	i = 0;
	if (!cmnd)
		return (NULL);
	if (ft_strrchr(cmnd, '/'))
		return (cmnd);
	while (envp[i])
	{
		aux = ft_strjoin(envp[i], "/");
		path = ft_strjoin(aux, cmnd);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		free(aux);
		i++;
	}
	return (NULL);
}

void	read_input_limiter(t_proc *p, t_env *exp)
{
	char	*input;

	p->infd = open("here_doc", O_RDWR | O_CREAT, S_IRWXU);
	ft_putstr_fd("\nenter.... fd.... open", 2);
	ft_putnbr_fd(p->infd, 2);
	ft_putstr_fd("\n", 2);
	while (1)
	{
		write(1, "here_doc> ", 10);
		input = get_next_line(0);
		input = ft_check_expand3(exp, input);
		if (input && ft_strlen(input) - 1 != ft_strlen(p->delimiter))
			ft_putstr_fd(input, p->infd);
		else if (input
			&& ft_strncmp(input, p->delimiter, ft_strlen(p->delimiter)) != 0)
			ft_putstr_fd(input, p->infd);
		else
			break ;
		free(input);
	}
	if (!input)
	{
		unlink("here_doc");
		p->exit_status = 2;
		return ;
	}
	free(input);
	close(p->infd);
}

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
