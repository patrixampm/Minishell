/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_struct_c.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeckham <ppeckham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 16:30:16 by ppeckham          #+#    #+#             */
/*   Updated: 2025/02/25 11:44:36 by ppeckham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	ft_check_closure(char *str, int *i, t_arg *node, int *end)
{
	int	j;

	j = *i + 1;
	while (str[j] != '\0')
	{
		if (str[j] == str[*i])
		{
			if (*end == 0)
				*end = j;
			return (true);
		}
		j++;
	}
	if (ft_strlen(node->str) != 0)
		free(node->str);
	free(node);
	return (false);
}

void	ft_final_str(int *i, int j, t_arg *arg_node)
{
	char	*temp;

	ft_reset_expand_s2(arg_node);
	printf("*i: %d\n", *i);
	printf("j: %d\n", j);
	printf("pre: %s\n", arg_node->pre);
	printf("ext: %s\n", arg_node->exp_str);
	printf("post: %s\n", arg_node->post);
	if (!arg_node->pre && !arg_node->exp_str && !arg_node->post)
		arg_node->temp = NULL;
	if (arg_node->pre && arg_node->exp_str && arg_node->post)
	{
		temp = ft_join_free(arg_node->pre, arg_node->exp_str);
		arg_node->temp = ft_join_free(temp, arg_node->post);
	}
	else if (arg_node->pre && arg_node->exp_str && !arg_node->post)
		arg_node->temp = ft_join_free(arg_node->pre, arg_node->exp_str);
	else if (arg_node->pre && !arg_node->exp_str && arg_node->post)
		arg_node->temp = ft_join_free(arg_node->pre, arg_node->post);
	else if (!arg_node->pre && arg_node->exp_str && arg_node->post)
		arg_node->temp = ft_join_free(arg_node->exp_str, arg_node->post);
	else
	{
		if (!arg_node->pre && arg_node->exp_str && !arg_node->post)
			arg_node->temp = ft_strdup(arg_node->exp_str);
		else if (!arg_node->pre && !arg_node->exp_str && arg_node->post)
			arg_node->temp = ft_strdup(arg_node->post);
		else if (arg_node->pre && !arg_node->exp_str && !arg_node->post)
			arg_node->temp = ft_strdup(arg_node->pre);
		ft_reset_expand_s(arg_node);
	}
	*i = j;
}

void	ft_final_str2(int *i, int j, t_arg *arg_node)
{
	char	*temp;

	ft_reset_expand_s2(arg_node);
	printf("*i: %d\n", *i);
	printf("j: %d\n", j);
	printf("pre: %s\n", arg_node->pre);
	printf("ext: %s\n", arg_node->exp_str);
	printf("post: %s\n", arg_node->post);
	if (!arg_node->pre && !arg_node->exp_str && !arg_node->post)
		arg_node->temp = NULL;
	if (arg_node->pre && arg_node->exp_str && arg_node->post)
	{
		temp = ft_join_free(arg_node->pre, arg_node->exp_str);
		arg_node->temp = ft_join_free(temp, arg_node->post);
	}
	else if (arg_node->pre && arg_node->exp_str && !arg_node->post)
		arg_node->temp = ft_join_free(arg_node->pre, arg_node->exp_str);
	else if (arg_node->pre && !arg_node->exp_str && arg_node->post)
		arg_node->temp = ft_join_free(arg_node->pre, arg_node->post);
	else if (!arg_node->pre && arg_node->exp_str && arg_node->post)
		arg_node->temp = ft_join_free(arg_node->exp_str, arg_node->post);
	else
	{
		if (!arg_node->pre && arg_node->exp_str && !arg_node->post)
			arg_node->temp = ft_strdup(arg_node->exp_str);
		else if (!arg_node->pre && !arg_node->exp_str && arg_node->post)
			arg_node->temp = ft_strdup(arg_node->post);
		else if (arg_node->pre && !arg_node->exp_str && !arg_node->post)
			arg_node->temp = ft_strdup(arg_node->pre);
		ft_reset_expand_s(arg_node);
	}
}

void	ft_simple_qt(char *str, int *i, t_arg *arg_node)
{
	int			j;
	t_substr	*qt;

	qt = malloc(sizeof(t_substr));
	j = *i + 1;
	qt->start = *i;
	while (str[j] != str[qt->start] && j < ft_strlen(str))
		j++;
	qt->end = j;
	qt->len = qt->end - (qt->start + 1);
	arg_node->temp = ft_substr(str, (qt->start + 1), (qt->len));
	*i = qt->end;
	free(qt);
}

void	ft_double_qt(char *str, int *i, t_arg *arg_node, t_env *env_lst)
{
	int		j;
	int		k;

	j = *i + 1;
	while (str[j] != str[*i] && j < ft_strlen(str))
	{
		if (str[j] == '$')
		{
			k = j + 1;
			arg_node->pre = ft_substr(str, *i + 1, j - (*i + 1));
			while (str[k] && str[k] != '$' && str[k] != '\'' && str[k] != '"' && str[k] != ' ')
				k++;
			if (str[j] == '$' && (str[j + 1] == '\'' || str[j + 1] == '"' || str[j + 1] == '\0'))
				arg_node->exp_str = ft_strdup("$");
			else
				arg_node->exp_str = ft_substr(str, j + 1, k - (j + 1));
			ft_check_expand(arg_node, env_lst);
			if (str[k] == '$')
			{
				ft_final_str2(i, j, arg_node);
				*i = k - 1;
				return ;
			}
			j = k;
			if (str[j] != str[*i] && str[k] != '\0')
				k++;
			printf("*I: %d\n", *i);
			printf("J: %d\n", j);
			printf("K: %d\n", k);
			printf("pre: %s\n", arg_node->pre);
			printf("ext: %s\n", arg_node->exp_str);
			if (str[k] == '$')
			{
				ft_final_str2(i, j, arg_node);
				*i = k - 1;
				return ;
			}
			while (str[k] && str[k] != str[*i])
				k++;
			arg_node->post = ft_substr(str, j, k - j);
			printf("post: %s\n", arg_node->post);
			if (str[j] == str[*i])
				break ;
			
		}
		j++;
	}
	if (!arg_node->has_expand)
		ft_simple_qt(str, i, arg_node);
	else
		ft_final_str(i, k, arg_node);
}

void	ft_no_qt_no_exp(char *str, t_arg *node, int *i, int j)
{
	node->temp = ft_substr(str, *i, (j - *i));
	*i = j - 1;
}

void	ft_no_qt(char *s, int *i, t_arg *node, t_env *env_lst)
{
	int			j;
	int			k;

	j = *i;
	while (j <= ft_strlen(s) && s[j] != '\'' && s[j] != '"' && s[j] != ' ')
	{
		if (s[j] == '$')
		{
			k = j + 1;
			node->pre = ft_substr(s, *i, j - *i);
			while (s[k] && s[k] != '$' && s[k] != '\'' && s[k] != '"' && s[k] != ' ')
				k++;
			if (s[j] == '$' && (s[j + 1] == '\'' || s[j + 1] == '"' || s[j + 1] == '\0'))
				node->exp_str = ft_strdup("$");
			else
				node->exp_str = ft_substr(s, j + 1, k - (j + 1));
			ft_check_expand(node, env_lst);
			if (s[k] == '$')
			{
				ft_final_str2(i, j, node);
				*i = k - 1;
				return ;
			}
			else if (s[k] && (s[k] == '\'' || s[k] == '"'))
				k++;
			if (s[k] == '$')
			{
				ft_final_str2(i, j, node);
				*i = k - 1;
				return ;
			}
			j = k;
			while (s[k] && s[k] != '\'' && s[k] != '"' && s[k] != ' ')
				k++;
			node->post = ft_substr(s, j, k - j);
		}
		j++;
	}
	if (!node->has_expand)
		ft_no_qt_no_exp(s, node, i, j);
	else
		ft_final_str(i, k, node);
}
