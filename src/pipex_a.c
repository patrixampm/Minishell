/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_a.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrl <aehrl@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:08:47 by aehrl             #+#    #+#             */
/*   Updated: 2025/04/26 19:35:27 by aehrl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

/* void	ft_solo_process(t_pipex *px, t_proc *p, int pipefd[], char *path[])
{
	if (p->infd != STDIN_FILENO)
	{
		if (dup2(p->infd, STDIN_FILENO) < 0)
			exit(errno);
		close(p->infd);
	}
	dup2(pipefd[1], STDOUT_FILENO);
	close(p->infd);
	close(p->outfd);
	if (execve(ft_get_path(px->clean_paths, px->cmd_args[0]), px->cmd_args, path) < 0)
		exit(errno);
} */
void	ft_first_process(t_pipex *px, t_proc *p, char *path[], t_env **exp)
{
 	if (px->in != STDIN_FILENO)
	{ 
		if (dup2(px->in, STDIN_FILENO) < 0)
			exit(errno);
		close(px->in);
	}
	px->out = p->outfd;
	dup2(px->pipes[1], STDOUT_FILENO);
	if (px->out != STDOUT_FILENO)
		close(px->out);
	close(px->in);
	if (p->is_builtin == true)
	{
		ft_builtin_execute(p, &px->all_paths, exp);
		exit(0);
	}
	else if (execve(ft_get_path(px->clean_paths, px->cmd_args[0]), px->cmd_args, path) < 0)
		exit(errno);
}

void	ft_child_process(t_pipex *px , t_proc *p, char *path[], t_env **exp)
{
	if (px->in != STDIN_FILENO)
	{
		if (dup2(px->in, STDIN_FILENO) < 0)
			exit(errno);
		close(px->in);
		unlink("here_doc");
	}
	if (px->pipes[1]!= STDOUT_FILENO)
	{
		dup2(px->pipes[1], STDOUT_FILENO);
		close(px->pipes[1]);
	}	
	close(px->pipes[0]);
	if (p->is_builtin == true)
	{
		ft_builtin_execute(p, &px->all_paths, exp);
		exit(0);
	}
	else if (execve(ft_get_path(px->clean_paths, px->cmd_args[0]), px->cmd_args, path) < 0)
		exit(errno);
}


void	ft_last_process(t_pipex *px, t_proc *p, char *path[], t_env **exp)
{
	if (dup2(px->in, STDIN_FILENO) < 0)
		exit(errno);
	close(px->in);
	px->out = p->outfd;
	if (px->out != STDOUT_FILENO)
	{
		dup2(px->out, STDOUT_FILENO);
		close(px->out);
	}
	if (p->is_builtin == true)
	{
		ft_builtin_execute(p, &px->all_paths, exp);
		exit(0);
	}
	else if (execve(ft_get_path(px->clean_paths, px->cmd_args[0]), px->cmd_args, path) < 0)
		exit(errno);
}

int	ft_set_inputfd(int pipein, int pipeout)
{
	close(pipeout);
	return (pipein);
}

int	ft_pipes(t_pipex *pipex, t_proc *p, char **env, t_env **exp)
{
	if (pipe(pipex->pipes) < 0)
		return (perror("Error\n creating pipe"), -1);
	pipex->pids = fork();
	if (pipex->pids < 0)
		return (perror("Error\n forking process"), -1);
	if (pipex->pids == 0)
	{
		if (pipex->iterator == 0)
			ft_first_process(pipex, p, env, exp);
		else if (pipex->iterator == pipex->p_count - 1)
			ft_last_process(pipex, p, env, exp);
		else
			ft_child_process(pipex, p, env, exp);
	}
	if (pipex->iterator != pipex->p_count - 1)
		pipex->in = ft_set_inputfd(pipex->pipes[0], pipex->pipes[1]);
	waitpid(pipex->pids, &pipex->status, 0);
	if (WIFEXITED(pipex->status) && pipex->status != 0)
		pipex->status = WEXITSTATUS(pipex->status);
	return (pipex->status);
}
