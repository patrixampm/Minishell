/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeckham <ppeckham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 11:44:45 by ppeckham          #+#    #+#             */
/*   Updated: 2025/01/16 13:16:42 by ppeckham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *ptr, int c, size_t count)
{
	size_t	i;
	char	*nptr;

	i = 0;
	nptr = ptr;
	while (i < count)
	{
		nptr[i] = c;
		i++;
	}
	return (nptr);
}
