/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_struct_b.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeckham <ppeckham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 16:32:31 by ppeckham          #+#    #+#             */
/*   Updated: 2025/02/11 13:43:27 by ppeckham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_get_type(char *str, char c, int *i)
{
	int		type;

	type = -1;
	if (ft_isalpha(c) == 1)
		return (type = 0);
	if (c == '\'')
		return (type = 1);
	if (c == '"')
		return (type = 2);
	if (str[*i + 1] && c == '<' && str[*i + 1] == '<')
		return (type = 4);
	if (c == '<')
		return (type = 3);
	if (str[*i + 1] && c == '>' && str[*i + 1] == '>')
		return (type = 6);
	if (c == '>')
		return (type = 5);
	if (c == '|')
		return (type = 7);
	return (type);
}

bool	ft_set_str(t_arg *node, char *str, int *i, int len)
{
	int	k;

	k = *i;
	if ((str[*i] == '\'' || str[*i] == '"')
		&& !ft_check_q_end(str, i, str[*i], NULL))
		return (false);
	node->str = ft_substr(str, k, len);
	node->len = len;
	return (true);
}

bool	ft_set_q_str(char *str, t_arg *arg_node, t_strqt *s, t_strqt *qt)
{
	while (ft_check_quote(str, s->start, qt))
	{
		if (!ft_check_q_end(str, &qt->start, str[qt->start], qt))
			return (false);
		if (str[s->start] != '\'' && str[s->start] != '"')
		{
			s->end = qt->start - 1;
			s->len = qt->start - s->start;
			s->substr = ft_substr(str, s->start, s->len);
			qt->substr = ft_substr(str, (qt->start + 1), qt->len);
			arg_node->temp = ft_strjoin(s->substr, qt->substr);
			ft_check_if_first_i(arg_node);
			s->start = qt->end + 1;
			arg_node->end = ft_strlen(arg_node->str);
		}
		else
		{
			qt->substr = ft_substr(str, (qt->start + 1), qt->len);
			arg_node->str = ft_strjoin(arg_node->str, qt->substr);
			s->start = qt->end + 1;
		}
		arg_node->end = s->start;
	}
	return (true);
}

bool	ft_set_0_str(char *str, int *i, t_arg *arg_node)
{
	t_strqt	*qt;
	t_strqt	*s;
	char	*temp;

	qt = malloc(sizeof(t_strqt));
	s = malloc(sizeof(t_strqt));
	s->start = *i;
	arg_node->end = 0;
	if (!ft_set_q_str(str, arg_node, s, qt))
		return (false);
	if (!(ft_check_quote(str, s->start, qt)) && str[s->start]
		&& (str[s->start] != ' '))
	{
		arg_node->end = ft_get_s_end(str, s->start);
		arg_node->len = arg_node->end - s->start;
		temp = ft_substr(str, s->start, arg_node->len);
		if (arg_node->str)
			arg_node->str = ft_strjoin(arg_node->str, temp);
		else
			arg_node->str = temp;
	}
	*i = arg_node->end + 1;
	ft_free_aux_str(qt, s);
	arg_node->len = ft_strlen(arg_node->str);
	return (true);
}

bool	ft_set_argstr(t_arg *arg_node, char *str, int *i)
{
	if (arg_node->type == 1 || arg_node->type == 2
		|| arg_node->type == 3 || arg_node->type == 5 || arg_node->type == 7)
	{
		if (!ft_set_str(arg_node, str, i, 1))
			return (false);
		(*i)++;
	}
	else if (arg_node->type == 4 || arg_node->type == 6)
	{
		if (!ft_set_str(arg_node, str, i, 2))
			return (false);
		*i += 2;
	}
	else if (arg_node->type == 0)
	{
		if (!ft_set_0_str(str, i, arg_node))
			return (false);
	}
	else
		return (false);
	// printf("%s\n", arg_node->str);
	// printf("%d\n", arg_node->len);
	// printf("%d\n", arg_node->type);
	return (true);
}
