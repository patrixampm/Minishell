/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrl <aehrl@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 13:32:55 by ppeckham          #+#    #+#             */
/*   Updated: 2025/04/22 17:41:24 by aehrl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_free_ms(t_ms *ms)
{
	ft_free_arg_list(&ms->arg_lst);
	ft_free_env_list(&ms->env_lst);
	if (ms->proc_lst != NULL)
		ft_free_proc_lst(&ms->proc_lst);
	free(ms->str);
	free(ms);
}


/* typedef struct s_pipex
{
	int		iterator; 
	int		p_count;
	int		cmd_count;
	int		**pipes;
	pid_t	*pids;
	bool	here_doc;
	t_env	*all_paths;
	char	**clean_paths;
	char	**cmd_args;
	int		status;
}	t_pipex;

 */

t_pipex	ft_init_pipex(t_proc *p, char ***env)
{
	t_pipex	pipex;
	t_proc	*aux;
	char *temp;
	int		i;

	aux = p;
	temp = getenv("PATH");
	i = 0;
	pipex.iterator = 0;
	pipex.pipes[0] = 0;
	pipex.pipes[1] = 1;
	pipex.in = 1; // 
	pipex.out = 2; // 
	pipex.p_count = ft_proc_lstsize(&p);
	while (aux->args[i])
		i++;
	pipex.cmd_count = i; 
	pipex.all_paths = *env;
	//pipex.clean_paths = ft_split(temp, ':');
	pipex.cmd_args = p->args;
	pipex.status = 0;
	return (pipex);
}

void	ft_print_pipex(t_pipex *pipex)
{
	int	i;

	i = 0;
	ft_putnbr_fd(pipex->cmd_count, 2);
	ft_putstr_fd("\nproccess count:\n", 2);
	ft_putnbr_fd(pipex->p_count, 2);
	ft_putstr_fd("\ncommands:\n", 2);
	while (pipex->cmd_args[i])
	{
		ft_putstr_fd(pipex->cmd_args[i], 2);
		i++;
	}
	/*i = 0;
	 while (pipex->clean_paths[i])
	{
		ft_putstr_fd(pipex->clean_paths[i], 2);
		ft_putstr_fd("\n", 2);
		i++;
	} */
	ft_putstr_fd("pipex iterator:", 2);
	ft_putnbr_fd(pipex->iterator, 2);
	ft_putstr_fd("\npipex pipefd[0]:", 2);
	ft_putnbr_fd(pipex->pipes[0], 2);
	ft_putstr_fd("\npipex pipefd[1]:", 2);
	ft_putnbr_fd(pipex->pipes[1], 2);
	ft_putstr_fd("\npipex in:", 2);
	ft_putnbr_fd(pipex->in, 2);
	ft_putstr_fd("\npipex out:", 2);
	ft_putnbr_fd(pipex->out, 2);
	ft_putstr_fd("\npipex status:", 2);
	ft_putnbr_fd(pipex->status, 2);
	ft_putstr_fd("\n", 2);
}
void ft_excecute(t_proc *p, char ***env, t_env **exp)
{
	t_pipex pipex;
	t_proc	*aux;

	aux = p;
	pipex = ft_init_pipex(p, env);
	while(pipex.iterator < pipex.p_count && aux != NULL) // check status
	{
		pipex.clean_paths = ft_split(getenv("PATH"), ':');
		//if (p->outfd != STDOUT_FILENO)
			pipex.out = p->outfd;
	/* 	if (p->infd)
			pipex.in = p->infd;
		 */
		//ft_print_pipex(&pipex);
		if (aux->is_builtin == true)
			ft_builtin_execute(aux, env, exp); // add fd for where to put strings
		else
		{
			ft_pipes(&pipex, aux, *env);
			//pipex.in = pipefd[0];
			//pipex.out = pipefd[1];
		}

		pipex.iterator++;
		if (aux->next != NULL)
		{
			aux = aux->next;
			pipex.cmd_args = aux->args;
		}
		ft_free_matrix(pipex.clean_paths);
	}
	//ft_free_matrix(pipex.clean_paths);
}
/* void ft_excecute(t_proc *p, char ***env, t_env **exp)
{
	t_proc *aux;
	int		pipe;
	int		size;
	int		e;

	aux = p;
	size = ft_proc_lstsize(&aux);
	pipe = 0;
	if (size == 1)
	{
		e = ft_pipes_solo_process()
		return ;
	}
	//if (aux->next != NULL && ft_strncmp(aux->next->arg[0], "head"))
	//	ft_do_head_action(aux->next, ) 
	while(aux)
	{
		if (aux->is_builtin == true)
			ft_builtin_execute(aux, env, exp);
		else
			e = ft_pipes(aux, *env, pipe);
		size--;
		if (size == 0)
			pipe = 2;
		else
			pipe = 1;
	}
	//add check for head
	//add check for only one argument
	//add error handling
	
} */

bool	ft_minishell(char *str, char ***env, t_env **exp)
{
	t_ms	*ms;

	ms = malloc(sizeof(t_ms));
	ms->proc_lst = NULL;
	if (ms == NULL)
		return (false);
	ms->env_lst = ft_get_env_lst(*env);
	if (ms->env_lst == NULL)
		return (false);
	ms->str = ft_strdup(str);
	ms->arg_lst = ft_arg_lst(str, ms->env_lst);
	if (ms->arg_lst == NULL)
		return (ft_free_ms(ms), false);
	ms->proc_lst = ft_proc(ms);
	if (ms->proc_lst == NULL)
		return (ft_free_ms(ms), false);
	//ft_print_arg_lst(&ms->arg_lst);
	ft_print_proc_lst(&ms->proc_lst);
	//ft_builtin_execute(ms->proc_lst, env, exp);
	ft_excecute(ms->proc_lst, env, exp);
	return (ft_free_ms(ms), true);
}
	
int	main(int ac, char **av, char **env)
{
	char	*str;
	char 	**new_env;
	t_env	*exp;
	
	if (env == NULL)
		exp = ft_create_export_lst(env);
	new_env = ft_create_env(env, &exp);
	(void)av;
	//ft_print_export_lst(&exp);
	if (ac == 1)
	{
		while (1)
		{
			str = readline("Minishell:>");
			add_history(str);
			if (!ft_strncmp(str, "EXIT", 5))
				break ;
			ft_minishell(str, &new_env, &exp);
			free(str);
		}
	}
	else
		return (1);
	ft_free_matrix(new_env);
	ft_free_env_list(&exp);
	return (free(str), 0);
}
