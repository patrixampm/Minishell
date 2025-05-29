/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_a.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeckham <ppeckham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:08:47 by aehrl             #+#    #+#             */
/*   Updated: 2025/05/29 13:43:29 by ppeckham         ###   ########.fr       */
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

void	ft_handle_in(t_pipex *pipex, t_proc *proc, t_env *exp)
{
	if (proc->hd == true)
	{
		read_input_limiter(proc, exp);
		if (proc->exit_status == 2 || !proc->args)
			exit(2);
		proc->infd = open("here_doc", O_RDWR , S_IRWXU);
		if (dup2(proc->infd, STDIN_FILENO) < 0)
			ft_print_dup2err(pipex);
		close(proc->infd);
	}
	else if (pipex->in != STDIN_FILENO)
	{ 
		if (proc->infd != STDIN_FILENO)
			pipex->in = proc->infd;
		if (pipex->in == -1)
		{
			printf("%s: No such file or directory\n", proc->infile);
			pipex->status = 1;
			exit(1);
		}
		if (dup2(pipex->in, STDIN_FILENO) < 0)
			ft_print_dup2err(pipex);
		close(pipex->in);
	}
}

void	ft_handle_out(t_pipex *pipex, t_proc *proc)
{
	if (proc->outfd != STDOUT_FILENO)
	{
		close(pipex->pipes[1]);
		pipex->out = proc->outfd;
	}
	if (pipex->out != STDIN_FILENO)
	{ 
		if (dup2(pipex->out, STDIN_FILENO) < 0)
			ft_print_dup2err(pipex);
		close(pipex->out);
	}
	/* px->out = p->outfd;
	if (px->out != STDOUT_FILENO)
	{
		dup2(px->out, STDOUT_FILENO);
		close(px->out);
	} */
}

void	ft_solo_process(t_pipex *px, t_proc *p, char ***env, t_env **exp)
{
	if (p->hd == true && p->is_builtin == true)
	{
		read_input_limiter(p, *exp);
		if (p->exit_status == 2)
			return ;
		p->infd = open("here_doc", O_RDWR , S_IRWXU);
	}
	if (p->is_builtin == true)
	{
		ft_builtin_execute(p, env, exp, px);
		return ;
	}
	px->pids = fork();
	if (px->pids == 0)
	{
		px->out = p->outfd;
		ft_handle_in(px, p, *exp);
		if (px->out != STDOUT_FILENO)
		{
			// ft_putstr_fd("\nenter\n", 2);
			if (dup2(px->out, STDOUT_FILENO) < 0)
				ft_print_dup2err(px);
			close(px->out);
		}
		if (px->cmd_args)
		{
			px->clean_path = ft_get_path(px->all_paths, px->cmd_args[0]);
			if (execve(px->clean_path, px->cmd_args, *env) < 0)
				ft_print_execve_err(px, p->args[0]);
		}
	}
	waitpid(px->pids, &px->status, 0);
	if (WIFEXITED(px->status) && px->status != 0)
		px->status = WEXITSTATUS(px->status);
	else
		px->status = 0;
}

void	ft_first_process(t_pipex *px, t_proc *p, char ***env, t_env **exp)
{
 	ft_handle_in(px, p, *exp);
	if (p->exit_status == 2)
		return ;
	dup2(px->pipes[1], STDOUT_FILENO); // should error handling be added here?
	if (px->out != STDOUT_FILENO)
		close(px->out);
	close(px->in);
	if (p->is_builtin == true)
	{
		ft_builtin_execute(p, &px->all_paths, exp, px);
		return ;
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
	if (p->exit_status == 2)
		return ;
	if (px->pipes[1]!= STDOUT_FILENO)
	{
		dup2(px->pipes[1], STDOUT_FILENO); // error handling?
		close(px->pipes[1]);
	}	
	close(px->pipes[0]);
	if (p->is_builtin == true)
	{
		ft_builtin_execute(p, env, exp, px);
		return ;
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
	ft_handle_in(px, p, *exp);
	if (p->exit_status == 2)
		return ;
	close(px->in);
	if (px->out != STDOUT_FILENO)
	{
		dup2(px->out, STDOUT_FILENO);
		close(px->out);
	}
	if (p->is_builtin == true)
	{
		ft_builtin_execute(p, &px->all_paths, exp, px);
		return ;
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
	if (pipe(px->pipes) < 0)
		return (ft_printerr("Error creating pipe", NULL, 1, px), -1);
	px->pids = fork();
	if (px->pids < 0)
		return (ft_printerr("Error forking process", NULL, 1, px), -1);
	if (px->pids == 0)
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
	else
		px->status = 0;
	unlink("here_doc");
	return (px->status);
}
