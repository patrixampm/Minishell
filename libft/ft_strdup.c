/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeckham <ppeckham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 11:09:57 by ppeckham          #+#    #+#             */
/*   Updated: 2025/01/16 13:17:19 by ppeckham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*nstr;
	int		j;
	int		i;

	j = 0;
	i = 0;
	while (str[j] != '\0')
		j++;
	nstr = (char *)malloc(j + 1);
	if (nstr == NULL)
		return (NULL);
	while (i < j)
	{
		nstr[i] = str[i];
		i++;
	}
	nstr[i] = '\0';
	return (nstr);
}
