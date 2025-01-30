/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeckham <ppeckham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 13:32:50 by ppeckham          #+#    #+#             */
/*   Updated: 2025/01/30 14:51:27 by ppeckham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <sys/wait.h>
# include <aio.h>
# include <string.h>
# include <stdio.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "libft/libft.h"

# define READ 0
# define WRITE 1

typedef struct s_env
{
	char			*name;
	char			*content;
	struct s_env	*next;
}	t_env;

typedef struct s_arg
{
	char			*str;
	int				len;
	int				type;
	char			job;
	struct s_env	*next;
}	t_arg;

typedef struct s_pipex
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

// ARG LIST
t_arg	*ft_new_arg(t_arg *arg_node);
t_arg	*ft_last_arg(t_arg *lst);
void	ft_add_arg_back(t_arg **lst, t_arg *new);
int		ft_arg_lstsize(t_arg **lst);
void	ft_free_arg_list(t_arg **lst);

// ENV LIST
t_env	*ft_new_env(char *name, char *content);
t_env	*ft_last_env(t_env *lst);
void	ft_add_env_back(t_env **lst, t_env *new);
int		ft_env_lstsize(t_env **lst);
void	ft_free_env_list(t_env **lst);

// ARG STRUCT
t_arg	*ft_create_arg_lst(char *str);
void	ft_arg_lst(char *str);

#endif
