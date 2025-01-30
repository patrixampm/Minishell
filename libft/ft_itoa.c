/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeckham <ppeckham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 16:20:13 by ppeckham          #+#    #+#             */
/*   Updated: 2025/01/16 13:15:12 by ppeckham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(int n)
{
	int	digits;

	if (n <= 0)
		digits = 1;
	else
		digits = 0;
	while (n != 0)
	{
		n /= 10;
		digits++;
	}
	return (digits);
}

char	*ft_itoa(int n)
{
	char	*result;
	int		len;
	long	num;

	num = n;
	len = ft_count(num);
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	result[len--] = '\0';
	if (n < 0)
	{
		result[0] = '-';
		num = num * -1;
	}
	while (num > 0)
	{
		result[len--] = (num % 10) + '0';
		num /= 10;
	}
	if (n == 0)
		result[0] = '0';
	return (result);
}
