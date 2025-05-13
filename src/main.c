/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeckham <ppeckham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 13:32:55 by ppeckham          #+#    #+#             */
/*   Updated: 2025/05/13 14:51:23 by ppeckham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_signal_flag;

static void	ft_free_ms(t_ms *ms)
{
	ft_free_arg_list(&ms->arg_lst);
	ft_free_env_list(&ms->env_lst);
	if (ms->proc_lst != NULL)
		ft_free_proc_lst(&ms->proc_lst);
	free(ms->str);
	free(ms);
}

/* void	ft_wait(t_pipex *pipex)
{
	int	i;
	int	status;

	i = 0;
	while (i < (pipex->p_count))
	{
		if (waitpid(-1, &status, 0) == pipex->pids[pipex->cmd_count - 1])
			pipex->status = WEXITSTATUS(status);
		i++;
	}
} */

void ft_excecute(t_proc *p, t_info *info)
{
	t_pipex pipex;
	t_proc	*aux;

	aux = p;
	pipex = ft_init_pipex(p, &info->exp);
	pipex.in = p->infd;
	while(pipex.iter < pipex.p_count && aux != NULL) // check status
	{
		ft_builtin_check(p);
		ft_print_proc_lst(&p); //delete me later
		if (getenv("PATH") != NULL)
			pipex.all_paths = ft_split(getenv("PATH"), ':');
		pipex.out = p->outfd;
		if (pipex.p_count == 1)
			ft_solo_process(&pipex, p, &info->env, &info->exp);
		else
			ft_pipes(&pipex, aux, &info->env, &info->exp);
		if (aux->next != NULL)
		{
			aux = aux->next;
			pipex.cmd_args = aux->args;
		}
		if (pipex.all_paths != NULL)
			ft_free_matrix(pipex.all_paths);
		if (pipex.clean_path) 
			free(pipex.clean_path);
		if (pipex.status != 0)
			ft_putendl_fd(strerror(pipex.status), 2); // check these error messages
		pipex.iter++;
	}
}
bool	ft_minishell(char *str, t_info *info)
{
	t_ms	*ms;

	ms = malloc(sizeof(t_ms));
	ms->proc_lst = NULL;
	if (ms == NULL)
		return (false);
	ms->env_lst = ft_get_env_lst(info->env);
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
	//ft_print_proc_lst(&ms->proc_lst);
	//ft_builtin_execute(ms->proc_lst, info);
	ft_excecute(ms->proc_lst, info);
	return (ft_free_ms(ms), true);
}

void    ft_handle_c(int sig)
{
    (void)sig;
    if (g_signal_flag == 0)
    {
        printf("\n");
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
    else if (g_signal_flag == 1)
    {
        printf("\n");
        rl_replace_line("", 0);
    }
    else if (g_signal_flag == 2)
    {
        printf("\n");
        exit(130);
    }
    else if (g_signal_flag == 3)
        printf("");
    g_signal_flag = 0;
}

void    ft_init_info(t_info *info, char **env)
{
	if (*env)
        info->exp = ft_create_export_lst(env);
    info->env = ft_create_env(env, &info->exp);
    info->prev_exit = 0;
}

void	ft_free_info(t_info *info)
{
	ft_free_matrix(info->env);
    ft_free_env_list(&info->exp);
	free(info);
}
	
int main(int ac, char **av, char **env)
{
    char    *str;
    t_info  *info;

    (void)av;
	info = malloc(sizeof(t_info));
    ft_init_info(info, env);
    if (ac == 1)
    {
        while (1)
        {
            g_signal_flag = 0;
            signal(SIGINT, ft_handle_c);
            str = readline("Minishell:>");
            if (str == NULL)
			{
				break ;
                // ft_exit(info); // manage this exit depending on the level of the shell
			}
            add_history(str);
            if (!ft_strncmp(str, "EXIT", 5))
                break ;
            ft_minishell(str, info);
            free(str);
        }
    }
    else
		return (1);
	return (ft_free_info(info), free(str), 0);
}
