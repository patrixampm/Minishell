/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_search_funcs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeckham <ppeckham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 13:41:29 by ppeckham          #+#    #+#             */
/*   Updated: 2025/05/21 13:42:18 by ppeckham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_get_exp_content(t_env *exp, char *name)
{
	t_env	*aux;

	aux = exp;
	while (aux)
	{
		if (ft_strncmp(aux->name, name, ft_strlen(aux->name)) == 0)
			return (aux->content);
		aux= aux->next;
	}
	return (NULL);
}

bool	ft_strnstr_ms(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (*needle == '\0')
		return (false);
	while (i < len && haystack[i] != '\0')
	{
		if (haystack[i] == needle[0])
		{
			j = 0;
			while (haystack[i + j] == needle[j]
				&& needle[j] != '\0'
				&& (i + j) < len)
				j++;
			if (needle[j] == '\0')
				return (true);
		}
		i++;
	}
	return (false);
}

bool	ft_search_env(char **env, char *var, char *content)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if ((ft_strncmp(env[i], var, ft_strlen(var)) == 0) &&
			ft_strnstr_ms(env[i], content, ft_strlen(env[i])))
			return (true);
		i++;
	}
	return (false);
}

char	*ft_search_env_2(char **env, char *var)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if ((ft_strncmp(env[i], var, ft_strlen(var)) == 0))
			return (env[i]);
		i++;
	}
	return (NULL);
}
