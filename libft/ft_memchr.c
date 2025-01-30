/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeckham <ppeckham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 11:29:48 by ppeckham          #+#    #+#             */
/*   Updated: 2025/01/16 13:16:17 by ppeckham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *ptr, int value, size_t num)
{
	unsigned char	*nptr;
	size_t			i;

	i = 0;
	nptr = (unsigned char *)ptr;
	while (i < num)
	{
		if (nptr[i] == (unsigned char)value)
			return (nptr + i);
		i++;
	}
	return (NULL);
}
