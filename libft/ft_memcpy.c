/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeckham <ppeckham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 12:29:46 by ppeckham          #+#    #+#             */
/*   Updated: 2025/01/16 13:16:29 by ppeckham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*ndest;
	const unsigned char	*nsrc;

	i = 0;
	ndest = dest;
	nsrc = src;
	if (!src && !dest)
		return (NULL);
	while (i < n)
	{
		ndest[i] = nsrc[i];
		i++;
	}
	return (ndest);
}
