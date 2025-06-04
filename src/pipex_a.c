/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_a.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeckham <ppeckham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:08:47 by aehrl             #+#    #+#             */
/*   Updated: 2025/06/04 17:26:25 by ppeckham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_handle_in(t_pipex *pipex, t_proc *proc, t_env *exp)
{
	if (proc->infd != STDIN_FILENO)
	{
		close(pipex->in);
		pipex->in = proc->infd;
	}
	if (proc->hd == true)
	{
		read_input_limiter(proc, exp);
		if (proc->exit_status == 130 || !proc->args)
			return ;
		proc->infd = open("here_doc", O_RDWR , S_IRWXU);
		pipex->in = proc->infd;
		if (dup2(pipex->in, STDIN_FILENO) < 0)
			ft_print_dup2err(pipex);
		close(pipex->in);
	}
	else if (pipex->in != STDIN_FILENO)
	{ 
		if (pipex->in == -1)
		{
			printf("%s: No such file or directory\n", proc->infile);
			pipex->status = 1;
			exit(1); //maybe return?
		}
		//close(pipex->pipes[1]);
		if (dup2(pipex->in, STDIN_FILENO) < 0)
			ft_print_dup2err(pipex);
		close(pipex->in);
	}
}

void    ft_handle_out(t_pipex *pipex, t_proc *proc)
{
    if (proc->outfd != STDOUT_FILENO)
    {
		if (dup2(proc->outfd, STDOUT_FILENO) < 0)
			ft_print_dup2err(pipex);
    	close(pipex->pipes[WRITE]);
	}
	else
	{
		if (dup2(pipex->pipes[WRITE], STDOUT_FILENO) < 0)
            ft_print_dup2err(pipex);
	//	close(pipex->pipes[WRITE]);
	}
    
}

void	ft_solo_process(t_pipex *px, t_proc *p, char ***env, t_env **exp)
{
	//ft_handle_in(px, p, *exp);
	if (p->hd == true && p->is_builtin == true)
	{
		read_input_limiter(p, *exp);
		p->infd = open("here_doc", O_RDWR , S_IRWXU);
	}
	if (p->is_builtin == true)
	{
		ft_builtin_execute(p, env, exp, px);
		return ;
	}
	if (getenv("PATH") != NULL)
		px->all_paths = ft_split(getenv("PATH"), ':');
	px->pids[0] = fork();
	if (px->pids[0] == 0)
	{
		ft_handle_in(px, p, *exp);
		if (p->outfd != STDOUT_FILENO)
		{
			if (dup2(p->outfd, STDOUT_FILENO) < 0)
				ft_print_dup2err(px);
			close(p->outfd);
		}
		if (px->cmd_args)
		{
			px->clean_path = ft_get_path(px->all_paths, px->cmd_args[0]);
			if (execve(px->clean_path, px->cmd_args, *env) < 0)
				ft_print_execve_err(px, p->args[0]);
		}
	}
	if (px->all_paths != NULL)
	{
		ft_free_matrix(px->all_paths);
		//px->all_paths = NULL;
	}
	unlink("here_doc");
}

void	ft_first_process(t_pipex *px, t_proc *p, char ***env, t_env **exp)
{

	ft_handle_in(px, p, *exp);
	ft_handle_out(px, p);
	
/* 	close(px->pipes[0]);
	close(px->in); */
	if (p->is_builtin == true)
	{
		ft_builtin_execute(p, env, exp, px);
		exit(px->status);
	}
	if (px->cmd_args)
	{
		px->clean_path = ft_get_path(px->all_paths, px->cmd_args[0]);
		if (execve(px->clean_path, px->cmd_args, *env) < 0)
			ft_print_execve_err(px, p->args[0]);
	}
}

void	ft_child_process(t_pipex *px , t_proc *p, char ***env, t_env **exp)
{
	ft_handle_in(px, p, *exp);
	
	if (px->status == 130)
		return ;
	//ft_putstr_fd("enter child", 2);
	ft_handle_out(px, p);
	/* if (px->pipes[1]!= STDOUT_FILENO)
	{
		dup2(px->pipes[1], STDOUT_FILENO); // error handling?
		close(px->pipes[1]);
	}	 
	close(px->pipes[0]); */
	if (p->is_builtin == true)
	{
		ft_builtin_execute(p, env, exp, px);
		exit(px->status);
	}
	if (px->cmd_args)
	{
		px->clean_path = ft_get_path(px->all_paths, px->cmd_args[0]);
		if (execve(px->clean_path, px->cmd_args, *env) < 0)
			ft_print_execve_err(px, p->args[0]);
	}
}

void	ft_last_process(t_pipex *px, t_proc *p, char ***env, t_env **exp)
{
	if (px->in != STDIN_FILENO)
	{
		if (dup2(px->in, STDIN_FILENO) < 0)
			exit(errno);
		close(px->in);
	}
	if (px->pipes[1] != STDOUT_FILENO)
	{
		dup2(px->pipes[1], STDOUT_FILENO);
		close(px->pipes[1]);
	}
	if (p->outfd != STDOUT_FILENO)
	{
		dup2(p->outfd, STDOUT_FILENO);
		close(p->outfd);
	}
	if (p->is_builtin == true)
	{
		ft_builtin_execute(p, env, exp, px);
		exit(px->status);
	}
	if (px->cmd_args)
	{
		px->clean_path = ft_get_path(px->all_paths, px->cmd_args[0]);
		if (execve(px->clean_path, px->cmd_args, *env) < 0)
			ft_print_execve_err(px, p->args[0]);
	}
}

int	ft_pipes(t_pipex *px, t_proc *p, char ***env, t_env **exp)
{
	if (px->iter != px->p_count - 1 && pipe(px->pipes) < 0)
		return (perror("Error\n creating pipe"), -1); //check errno number
	px->pids[px->iter] = fork();
	if (px->pids[px->iter] < 0)
		return (perror("Error\n forking process"), -1); //check errno number
	if (px->pids[px->iter] == 0)
	{
		if (px->iter == 0)
			ft_first_process(px, p, env, exp);
		else if (px->iter == px->p_count - 1)
			ft_last_process(px, p, env, exp);
		else
			ft_child_process(px, p, env, exp);
	}
	// if (p->is_builtin == true) // dont think i need this
	// 	close(p->infd);
	if (px->iter != px->p_count - 1)
		px->in = ft_set_infd(px->pipes[0], px->pipes[1]);
	if (ft_strncmp(p->args[0], "head", 4))
		px->pids[px->iter] = -1;
	unlink("here_doc");
	return (px->pids[px->iter]);
}
