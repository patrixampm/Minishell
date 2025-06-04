/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrl <aehrl@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 13:32:55 by ppeckham          #+#    #+#             */
/*   Updated: 2025/06/04 17:49:20 by aehrl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_free_ms(t_ms *ms)
{
	ft_free_arg_list(&ms->arg_lst);
	if (ms->proc_lst != NULL)
		ft_free_proc_lst(&ms->proc_lst);
	free(ms->str);
	free(ms);
}

void	ft_wait(t_pipex *px)
{
	int	i;

	i = 0;
	while (i < (px->p_count))
	{
		waitpid(px->pids[i], &px->status, 0);
		if (WIFEXITED(px->status) && px->status != 0)
			px->status = WEXITSTATUS(px->status);
		if (WIFSIGNALED(px->status) && px->status != 0)
			px->status = WTERMSIG(px->status);
		i++;
	}
}

void ft_multi_process(t_pipex *pipex, t_proc *p, t_info *info)
{
	t_proc	*aux;

	aux = p;
	while(pipex->iter < pipex->p_count && aux != NULL) // check status
	{
		ft_builtin_check(aux);
		if (getenv("PATH") != NULL)
			pipex->all_paths = ft_split(getenv("PATH"), ':');
		ft_pipes(pipex, aux, &info->env, &info->exp);
		if (aux->next != NULL)
		{
			aux = aux->next;
			pipex->cmd_args = aux->args;
		}
		if (pipex->all_paths != NULL)
		{
			ft_free_matrix(pipex->all_paths);
			pipex->all_paths = NULL;
		}
		if (pipex->clean_path) 
			free(pipex->clean_path);
		pipex->iter++;
	}
}

void ft_excecute(t_proc *p, t_info *info)
{
	t_pipex pipex;
	
	pipex = ft_init_pipex(p, info);
	pipex.in = p->infd;
	ft_builtin_check(p);
	if (pipex.p_count == 1)
		ft_solo_process(&pipex, p, &info->env, &info->exp);
	else 
		ft_multi_process(&pipex, p, info);
	
	ft_wait(&pipex);
	free(pipex.pids);
	if (pipex.all_paths != NULL)
		ft_free_matrix(pipex.all_paths);
	if (pipex.status != 0)
		info->prev_exit = pipex.status;
	else
		info->prev_exit = 0;
	unlink("here_doc");
}

bool	ft_minishell(char *str, t_info *info)
{
	t_ms	*ms;

	ms = malloc(sizeof(t_ms));
	ms->proc_lst = NULL;
	if (ms == NULL)
		return (false);
	ms->str = ft_strdup(str);
	ms->arg_lst = ft_arg_lst(str, info);
	if (ms->arg_lst == NULL)
		return (ft_free_ms(ms), false);
	ms->proc_lst = ft_proc(ms, info);
	if (ms->proc_lst == NULL)
		return (ft_free_ms(ms), false);
	ft_excecute(ms->proc_lst, info);
	return (ft_free_ms(ms), true);
}

void    ft_handle_c(int sig)
{
    (void)sig;
    printf("\n");
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

void    ft_init_info(t_info *info, char **env)
{
	t_env	*exp;
	char	*lvl;

	exp = NULL;
	if (*env)
        info->exp = ft_create_export_lst(env, exp);
    info->env = ft_create_env(env, &info->exp);
	info->shlvl = atoi(ft_get_exp_content(info->exp, "SHLVL")) + 1;
	lvl = ft_itoa(info->shlvl);
	ft_search_export(&info->exp, "SHLVL", lvl);
	ft_env_add_or_set(info->env, ft_builtin_unset_checker(info->env, "SHLVL"),
	"SHLVL", lvl);
	free(lvl);
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

            signal(SIGINT, ft_handle_c);
            str = readline("Minishell:>");
            if (str == NULL)
			{
				write(2, "exit\n", 5);
				break ;
			}
			if (str[0] == '\0')
			{
			    free(str);
			    continue;
			}
            add_history(str);
            if (!ft_strncmp(str, "exit", ft_strlen(str)))
			{
				write(2, "exit\n", 5);
                break ;
			}
            ft_minishell(str, info);
            free(str);
        }
    }
    else
		return (1);
	return (ft_free_info(info), free(str), 0);
}
