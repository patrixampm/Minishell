/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeckham <ppeckham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:03:30 by ppeckham          #+#    #+#             */
/*   Updated: 2025/02/17 16:13:50 by ppeckham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;

	i = 0;
	if (len == 0)
		return ("");
	if (start > (size_t)ft_strlen(s))
		len = 0;
	if (len > (size_t)ft_strlen(s) - start)
		len = ((size_t)ft_strlen(s) - start);
	sub = malloc(len + 1);
	if (!s || !sub)
	{
		return (NULL);
	}
	while (s[i] != '\0' && i < len)
	{
		sub[i] = s[start];
		i++;
		start++;
	}
	sub[i] = '\0';
	return (sub);
}
