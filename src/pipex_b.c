/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_b.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrl <aehrl@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:11:38 by aehrl             #+#    #+#             */
/*   Updated: 2025/06/04 17:44:23 by aehrl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void ft_close_hd_ctrlc(int sig)
{
	(void)sig;
	exit(130);
}

void	read_input_limiter(t_proc *p, t_env *exp)
{
	char	*input;

	p->infd = open("here_doc", O_RDWR | O_CREAT, S_IRWXU);
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
		signal(SIGINT, ft_close_hd_ctrlc);
		free(input);
	}
	if (!input)
	{
		ft_putstr_fd("warning: here-document at line 1 delimited by end-of-file (wanted `", 2);
		ft_putstr_fd(p->delimiter, 2);
		ft_putstr_fd("')\n", 2);
		close(p->infd);
		//px->pids[px->iter] = -1;
	//	unlink("here_doc");
		//p->exit_status = 2;
		return ;
	}
	free(input);
	close(p->infd);
}

void	del_heredoc(t_proc *p) // dont think we ever use this
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
