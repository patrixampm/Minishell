/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_a.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrl <aehrl@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:08:47 by aehrl             #+#    #+#             */
/*   Updated: 2025/05/12 14:49:18 by aehrl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
/* void	ft_handle_pipes(t_pipex *pipex, t_proc *proc)
{
	if (proc->infd != STDIN_FILENO)
	{
		close(pipex->pipes[pipex->iter][0]);
		if (dup2(proc->infd, STDIN_FILENO) < 0)
			exit(errno);
		close(proc->infd);
	}
	else if (pipex->pipes[pipex->iter][0] != STDIN_FILENO)
	{
		if (dup2(pipex->pipes[pipex->iter][0], STDIN_FILENO) < 0)
			exit(errno);
		close(pipex->pipes[pipex->iter][0]);
	}
} */

void	ft_solo_process(t_pipex *px, t_proc *p, char ***env, t_env **exp)
{
	if (px->in != STDIN_FILENO)
	{ 
		if (dup2(px->in, STDIN_FILENO) < 0)
			exit(errno);
		close(px->in);
	}
	px->out = p->outfd;
	if (px->out != STDOUT_FILENO)
	{
		dup2(px->out, STDOUT_FILENO);
		close(px->out);
	}
	if (p->is_builtin == true)
	{
		ft_builtin_execute(p, env, exp);
		exit(0);
	}
/* 	dup2(px->pipes[0], STDIN_FILENO);
	dup2(px->pipes[1], STDOUT_FILENO); */
 	//close(p->infd);
//	close(p->outfd); 
	px->clean_path = ft_get_path(px->all_paths, px->cmd_args[0]);
	if (execve(px->clean_path, px->cmd_args, *env) < 0)
		exit(errno);
}
void	ft_first_process(t_pipex *px, t_proc *p, char ***env, t_env **exp)
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
	px->clean_path = ft_get_path(px->all_paths, px->cmd_args[0]);
	if (execve(px->clean_path, px->cmd_args, *env) < 0)
		exit(errno);
}

void	ft_child_process(t_pipex *px , t_proc *p, char ***env, t_env **exp)
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
		ft_builtin_execute(p, env, exp);
		exit(0);
	}
	px->clean_path = ft_get_path(px->all_paths, px->cmd_args[0]);
	if (execve(px->clean_path, px->cmd_args, *env) < 0)
		exit(errno);
}

void	ft_last_process(t_pipex *px, t_proc *p, char ***env, t_env **exp)
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
	px->clean_path = ft_get_path(px->all_paths, px->cmd_args[0]);
	if (execve(px->clean_path, px->cmd_args, *env) < 0)
		exit(errno);
}


/*  void	ft_close_pipe(t_pipex *pipex)
{
	int	i;

	i = 0;
	if (pipex->pipes)
	{
		while (i < pipex->cmd_count - 1)
		{
			close(pipex->pipes[i][READ]);
			close(pipex->pipes[i][WRITE]);
			i++;
		}
	}
} */

int	ft_pipes(t_pipex *px, t_proc *p, char ***env, t_env **exp)
{
	if (pipe(px->pipes) < 0)
		return (perror("Error\n creating pipe"), -1); //check errno number
	px->pids = fork();
	if (px->pids < 0)
		return (perror("Error\n forking process"), -1); //check errno number
	if (px->p_count == 1 && px->pids == 0)
		ft_solo_process(px, p, env, exp);
	else if (px->pids == 0)
	{
		if (px->iter == 0)
			ft_first_process(px, p, env, exp);
		else if (px->iter == px->p_count - 1)
			ft_last_process(px, p, env, exp);
		else
			ft_child_process(px, p, env, exp);
	}
	if (px->iter != px->p_count - 1)
		px->in = ft_set_infd(px->pipes[0], px->pipes[1]);
	waitpid(px->pids, &px->status, 0);
	if (WIFEXITED(px->status) && px->status != 0)
		px->status = WEXITSTATUS(px->status);
	return (px->status);
}
