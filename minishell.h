/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeckham <ppeckham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 13:32:50 by ppeckham          #+#    #+#             */
/*   Updated: 2025/03/03 16:47:13 by ppeckham         ###   ########.fr       */
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
	char			*temp;
	char			*temp2;
	char			*pre;
	char			*post;
	char			*exp;
	int				start;
	int				end;
	int				len;
	int				type;
	char			job;
	bool			has_expand;
	bool			valid_expand;
	struct s_arg	*next;
	struct s_arg	*prev;
}	t_arg;

/*
JOBS:
'<' -> 'i' -> type 3 | infile: must be the first node or come after a 'p'
'<<' -> 'h' -> type 4 | here_doc: must be just after a 'C', and before a 'D'
'>' -> 'o' -> type 5 | outfile: must come after a 'C' (or various) and before an 'O'
'>>' -> 'a' -> type 6 | append: the same as 'o'
'|' -> 'p' -> type 7 | pipe

-------the above are literal, the bellow are examples-------------------

'intext.txt' -> 'I' -> type 0/1/2 | Infile name, must come after 'i'
'outtext.txt' -> 'O' -> type 0/1/2 | Outfile name, must come after 'o'
'cat' -> 'C' -> type 0/1/2 | Command, must be the first node or  come after an 'I', and must have 
				an 'o' after if it has an outfile, or nothing if it goes to terminal
'STOP' -> 'D' -> type 0/1/2 | delimiter: must be first or after a 'p' and before a 'h'
*/

typedef struct s_ms
{
	t_env	*env_lst;
	t_arg	*arg_lst;
	char	*str;
}	t_ms;

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
void	ft_lst_del_node(t_arg **lst, t_arg *node);
void	ft_free_arg_list(t_arg **lst);

// ENV LIST
t_env	*ft_new_env(char *name, char *content);
t_env	*ft_last_env(t_env *lst);
void	ft_add_env_back(t_env **lst, t_env *new);
int		ft_env_lstsize(t_env **lst);
void	ft_free_env_list(t_env **lst);

// ENV STRUCT
void	ft_print_env_lst(t_env **env_lst);
t_env	*ft_create_env_lst(t_env **lst, char **env);
t_env	*ft_get_env_lst(char **env);

// ARG STRUCT
void	ft_free_node_n_list(t_arg **lst, t_arg *node);
void	ft_print_arg_lst(t_arg **arg_lst); //
int		ft_get_type(char *str, char c, int *i);
bool	ft_qt(char *str, int *i, t_arg *node, t_env *env);
void	ft_simple_qt(char *str, int *i, t_arg *arg_node);
void	ft_end_here(t_arg *node, int *i, int k);
void	ft_reset_str_temp(t_arg *arg_node);
void	ft_iter_n_check(char *s, int j, int *k, t_arg *node);
int		ft_pre_n_exp1(char *s, t_arg *node, int *i, int j);
int		ft_pre_n_exp2(char *s, t_arg *node, int *i, int j);
void	ft_iter_k(char *s, int *i, int *k);
void	ft_check_n_iter(char *s, int *i, int j, int *k);
void	ft_compose_temp1(t_arg *node, char *s, int *i, int j);
void	ft_compose_temp2(t_arg *node, char *s, int *i, int j);
bool	ft_check_closure(char *str, int *i, t_arg *node);
bool	ft_check_qt_closure(char *str, int k);
void	ft_double_qt(char *str, int *i, t_arg *arg_node, t_env *env_lst);
void	ft_no_qt(char *str, int *i, t_arg *node, t_env *env_lst);
void	ft_expand_str(t_arg *arg_node);
void	ft_form_str(t_arg *arg_node);
bool	ft_set_simple_str(t_arg *node, char *str, int *i, int len);
bool	ft_set_alt_str(char *str, int *i, t_arg *arg_node, t_env *env_lst);
bool	ft_set_arg_str(t_arg *arg_node, char *str, int *i, t_env *env_lst);
void	ft_create_arg_lst(char *str, t_arg **arg_lst, t_env *env_lst);
t_arg	*ft_arg_lst(char *str, t_env *env_lst);

// ENV EXPAND
void	ft_reset_expand_s(t_arg *arg_node);
void	ft_reset_expand_s2(t_arg *arg_node);
void	ft_reset_expand_b(t_arg *arg_node);
void	ft_check_expand(t_arg *nd, t_env *env_lst);

// CHUNKS
void	ft_give_job(t_arg *node);
void	ft_arg_jobs(t_ms *ms);
void	ft_chunks(t_ms *ms);

#endif
