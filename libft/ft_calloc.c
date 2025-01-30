/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeckham <ppeckham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:48:10 by ppeckham          #+#    #+#             */
/*   Updated: 2025/01/14 14:48:27 by ppeckham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t num, size_t size)
{
	size_t		i;
	size_t		arr_size;
	char		*arr;

	i = 0;
	arr_size = num * size;
	arr = malloc(arr_size);
	if (arr == NULL)
		return (NULL);
	while (i < arr_size)
	{
		arr[i] = 0;
		i++;
	}
	return (arr);
}
