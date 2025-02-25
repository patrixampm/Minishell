/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_struct_b.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeckham <ppeckham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 16:32:31 by ppeckham          #+#    #+#             */
/*   Updated: 2025/02/25 10:27:24 by ppeckham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_get_type(char *str, char c, int *i)
{
	int		type;

	type = -1;
	if (ft_isalpha(c) == 1 || c == '$')
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

bool	ft_set_simple_str(t_arg *node, char *str, int *i, int len)
{
	int	k;

	k = *i;
	node->str = ft_substr(str, k, len);
	node->len = len;
	return (true);
}

char	*ft_join_free(char *s1, char *s2)
{
	char	*result;

	result = ft_strjoin(s1, s2);
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	return (result);
}

void	ft_form_str(t_arg *arg_node)
{
	char	*temp2;

	temp2 = NULL;
	if (ft_strlen(arg_node->str) == 0 && ft_strlen(arg_node->temp) == 0)
		return ;
	ft_reset_str_temp(arg_node);
	if (arg_node->str)
	{
		// printf("len temp: %d\n", ft_strlen(arg_node->temp));
		// printf("temp: %p\n", arg_node->temp);
		if (ft_strlen(arg_node->temp) == 0)
		{
			temp2 = ft_strdup(arg_node->str);
			free(arg_node->str);
		}
		else
			temp2 = ft_join_free(arg_node->str, arg_node->temp);
		arg_node->str = ft_strdup(temp2);
		free(temp2);
	}
	else if (!arg_node->str)
	{
		arg_node->str = ft_strdup(arg_node->temp);
		free(arg_node->temp);
	}
	ft_reset_str_temp(arg_node);
	arg_node->len = ft_strlen(arg_node->str);
}

// bool	ft_check_end(char *str, int *i)
// {
// 	int	qt_count;
// 	int	j;

// 	qt_count = 0;
// 	j = *i;
// 	while (j >= 0)
// 	{
// 		printf("j: %d\n", j);
// 		if (str[j] == '\'' || str[j] == '"')
// 			qt_count++;
// 		j--;
// 	}
// 	if (qt_count % 2 != 0)
// 	{
// 		(*i)++;
// 		return (false);
// 	}
// 	else
// 		return (true);
// }

bool	ft_set_alt_str(char *str, int *i, t_arg *arg_node, t_env *env_lst)
{
	int	end;
	bool is_end;

	end = 0;
	is_end = false;
	while (!is_end)
	{
		ft_reset_expand_b(arg_node);
		if (str[*i] == '\'' || str[*i] == '"')
		{
			if (!ft_check_closure(str, i, arg_node, &end))
				return (false);
			if (str[*i] == '\'')
				ft_simple_qt(str, i, arg_node);
			else
				ft_double_qt(str, i, arg_node, env_lst);
		}
		else
			ft_no_qt(str, i, arg_node, env_lst);
		printf("str1: %s\n", arg_node->str);
		ft_form_str(arg_node);
		printf("str2: %s\n", arg_node->str);
		if (*i >= (ft_strlen(str)))
			return (true);
		if (*i >= end && (str[*i + 1] == '\0' || str[*i + 1] == ' '))
			is_end = true;
		else if (*i >= end && str[*i + 1] && str[*i + 1] != ' ')
			end = 0;
		*i = *i + 1;
	}
	return (true);
}

bool	ft_set_arg_str(t_arg *arg_node, char *str, int *i, t_env *env_lst)
{
	if (arg_node->type < 3)
	{
		if (!ft_set_alt_str(str, i, arg_node, env_lst))
			return (false);
	}
	else if (arg_node->type == 3 || arg_node->type == 5 || arg_node->type == 7)
	{
		if (!ft_set_simple_str(arg_node, str, i, 1))
			return (false);
		(*i)++;
	}
	else if (arg_node->type == 4 || arg_node->type == 6)
	{
		if (!ft_set_simple_str(arg_node, str, i, 2))
			return (false);
		*i += 2;
	}
	else
		return (false);
	return (true);
}
