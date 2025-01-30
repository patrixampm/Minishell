/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeckham <ppeckham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 10:44:18 by ppeckham          #+#    #+#             */
/*   Updated: 2025/01/16 13:17:34 by ppeckham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t destsize)
{
	size_t	i;
	size_t	j;
	size_t	p;

	i = 0;
	j = 0;
	p = 0;
	while (dest[i] != '\0' && i < destsize)
		i++;
	while (src[p] != '\0')
		p++;
	while (src[j] != '\0' && (i + j + 1) < destsize)
	{
		dest[j + i] = src[j];
		j++;
	}
	if (i < destsize)
		dest[j + i] = '\0';
	return (i + p);
}
