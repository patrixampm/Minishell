/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_a.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrl <aehrl@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:08:47 by aehrl             #+#    #+#             */
/*   Updated: 2025/04/22 17:43:53 by aehrl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// add ft_only_process function/handling

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
void	ft_first_process(t_pipex *px, t_proc *p, int pipefd[], char *path[])
{
	ft_putstr_fd("ENTER FIRST PROCESS\n", 0);
	ft_putnbr_fd(p->infd, 2);
	ft_putstr_fd("\n----------\n", 2);
 	if (px->in != STDIN_FILENO)
	{ 
	//	ft_putstr_fd("\nENTER\n", 2);
		if (dup2(px->in, STDIN_FILENO) < 0)
			exit(errno);
		close(px->in);
	}
	dup2(pipefd[1], STDOUT_FILENO);
	if (px->out != STDOUT_FILENO)
	{
		close(px->out);
		//dup2(pipefd[1], STDOUT_FILENO);
	}	
	close(px->in);
	if (execve(ft_get_path(px->clean_paths, px->cmd_args[0]), px->cmd_args, path) < 0)
		exit(errno);
}

void	ft_child_process(t_pipex *px , int pipefd[], char *path[])
{
	if (px->in != STDIN_FILENO)
	{
		if (dup2(px->in, STDIN_FILENO) < 0)
			exit(errno);
		close(px->in);
		unlink("here_doc");
	}
	if (pipefd[1]!= STDOUT_FILENO)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
	}	
	close(pipefd[0]);
	if (execve(ft_get_path(px->clean_paths, px->cmd_args[0]), px->cmd_args, path) < 0)
		exit(errno);
}
/* void	ft_child_process(char **cmd, t_proc *p, int pipefd[], char *path[])
{
	if (p->infd != STDIN_FILENO)
	{
		if (dup2(p->infd, STDIN_FILENO) < 0)
			exit(errno);
		close(p->infd);
		unlink("here_doc");
	}
	if (pipefd[1]!= STDOUT_FILENO)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
	}	
	close(pipefd[0]);
	if (execve(getenv("PATH"), cmd, path) < 0)
		exit(errno);
} */

void	ft_last_process(t_pipex *px, t_proc *p, char *path[])
{
	ft_putstr_fd("ENTER LAST PROCESS\n", 2);
	ft_putnbr_fd(p->infd, 2);
	ft_putstr_fd("\n----------\n", 2);
	if (px->in != STDIN_FILENO)
	{
		if (dup2(px->in, STDIN_FILENO) < 0)
			exit(errno);
		close(px->in);
	}
	if (p->outfd != STDOUT_FILENO)
		px->out = p->outfd;
	if (px->out != STDOUT_FILENO)
	{
		dup2(px->out, STDOUT_FILENO);
	}
	close(px->out);
	ft_putnbr_fd(p->outfd, 2);
	ft_putstr_fd("\n----------\n", 2);
	if (execve(ft_get_path(px->clean_paths, px->cmd_args[0]), px->cmd_args, path) < 0)
		exit(errno);
}

int	ft_set_inputfd(int pipein, int pipeout)
{
	close(pipeout);
	return (pipein);
}
/* 
int	ft_pipes(char *cmd, int fds[], char *envp[], int first_last[])
{
	pid_t	pid;
	int		pipefd[2];

	//add check for only one argument
	if (!first_last[1] && pipe(pipefd) < 0)
		return (perror("Error\n creating pipe"), -1);
	pid = fork();
	if (pid < 0)
		return (perror("Error\n forking process"), -1);
	if (pid == 0)
	{
		if (first_last[0] == 2)
			ft_first_process(ft_split(cmd, ' '), fds, pipefd, envp);
		else if (first_last[1])
			ft_last_process(ft_split(cmd, ' '), fds, envp);
		else
			ft_child_process(ft_split(cmd, ' '), fds, pipefd, envp);
	}
	if (!first_last[1])
		fds[0] = ft_set_inputfd(pipefd[0], pipefd[1]);
	waitpid(pid, &fds[2], 0);
	if (WIFEXITED(fds[2]) && fds[2] != 0)
		fds[2] = WEXITSTATUS(fds[2]);
	return (fds[2]);
} */
int	ft_pipes(t_pipex *pipex, t_proc *p, char **env)
{
	//pid_t	pipex->pids;
	//int		pipefd[2];
	//add check for only one argument
	ft_putstr_fd("\n----ENTER PIPES------\n", 2);
	if (pipe(pipex->pipes) < 0)
		return (perror("Error\n creating pipe"), -1);
	pipex->pids = fork();
	if (pipex->pids < 0)
		return (perror("Error\n forking process"), -1);
	if (pipex->pids == 0)
	{
		//new first last checks with the p list
		if (pipex->iterator == 0)
			ft_first_process(pipex, p, pipex->pipes, env);
		else if (pipex->iterator == pipex->p_count - 1)
			ft_last_process(pipex, p, env);
		else
		{
			ft_child_process(pipex, pipex->pipes, env);
			ft_putstr_fd("\n----EXIT------\n", 2);
		}
	}
		/* if (pipex->iterator == 0)
			ft_first_process(p->args, p, pipex->pipes, env);
		else if (pipex->iterator == pipex->p_count)
			ft_last_process(p->args, p, env);
		else
			ft_child_process(p->args, p, pipex->pipes, env);
	} */
	if (pipex->iterator != pipex->p_count - 1)
		pipex->in = ft_set_inputfd(pipex->pipes[0], pipex->pipes[1]);
	waitpid(pipex->pids, &pipex->status, 0);
	if (WIFEXITED(pipex->status) && pipex->status != 0)
		pipex->status = WEXITSTATUS(pipex->status);
	return (pipex->status);
}


/* int	main(int argc, char *argv[], char *envp[])
{
	int		first_last[2];
	int		fd[3];
	char	**aux;

	first_last[0] = 2;
	if (argc != 5)
		return (ft_printf("Error\nUsage: infile cmd1 cmd2 ... outfile\n"), -1);
	if (ft_access_rights(argv[first_last[0] - 1], argv[argc - 1]) < 0)
		exit(2);
	fd[0] = open(argv[first_last[0] - 1], O_RDONLY);
	fd[1] = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	first_last[1] = 0;
	aux = ft_get_environment(envp);
	while (first_last[0] < argc - 1)
	{
		if (first_last[0] == argc - 2)
			first_last[1] = 1;
		fd[2] = ft_pipes(argv[first_last[0]], fd, aux, first_last);
		if (fd[2] != 0)
			return (close(fd[0]), close(fd[1]), ft_err_msg(fd[2], aux), fd[2]);
		first_last[0]++;
	}
	return (free_matrix(aux), close(fd[0]), close(fd[1]), 0);
} */