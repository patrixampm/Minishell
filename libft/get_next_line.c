/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeckham <ppeckham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:05:30 by ppeckham          #+#    #+#             */
/*   Updated: 2025/01/29 16:47:09 by ppeckham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_buffer(char *buffer, int fd)
{
	char	*aux;
	int		br;

	if (buffer == NULL)
		buffer = ft_calloc_gnl(1, 1);
	br = 1;
	aux = ft_calloc_gnl(BUFFER_SIZE + 1, 1);
	while (ft_strchr_gnl(buffer, '\n') == NULL && br > 0)
	{
		br = read(fd, aux, BUFFER_SIZE);
		if (ft_strlen_gnl(aux) > br)
		{
			aux[br] = '\0';
		}
		buffer = ft_strjoin_gnl(buffer, aux);
	}
	free(aux);
	return (buffer);
}

static char	*read_line(char *buffer)
{
	char	*line;
	int		i;

	line = NULL;
	i = 0;
	if (buffer[i] == 0)
		return (NULL);
	while (buffer[i] != '\0' && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	line = ft_calloc_gnl(i + 1, 1);
	i = 0;
	while (buffer[i] != '\0' && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		line[i] = '\n';
	return (line);
}

static char	*update_buffer(char *buffer)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (buffer[i] != '\0')
		i++;
	while (buffer[j] != '\0' && buffer[j] != '\n')
		j++;
	if (buffer[j] == '\0')
		return (free(buffer), NULL);
	new = ft_calloc_gnl(i - j + 1, 1);
	i = 0;
	if (buffer[j] == '\n')
		j++;
	while (buffer[j] != '\0')
	{
		new[i] = buffer[j];
		i++;
		j++;
	}
	free(buffer);
	return (new);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	buffer = read_buffer(buffer, fd);
	line = read_line(buffer);
	buffer = update_buffer(buffer);
	return (line);
}
