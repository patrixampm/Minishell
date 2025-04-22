/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_b.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrl <aehrl@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:11:38 by aehrl             #+#    #+#             */
/*   Updated: 2025/04/15 12:07:35 by aehrl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	read_input_limiter(int i, char *argv[])
{
	char	*input;
	int		fd;

	fd = open(argv[i], O_RDWR, S_IRWXU);
	while (1)
	{
		write(1, "here_doc> ", 10);
		input = get_next_line(0);
		if (input && ft_strlen(input) - 1 != ft_strlen(argv[i + 1]))
			ft_putstr_fd(input, fd);
		else if (input
			&& ft_strncmp(input, argv[i + 1], ft_strlen(argv[i + 1])) != 0)
			ft_putstr_fd(input, fd);
		else
			break ;
		free(input);
	}
	if (!input)
	{
		unlink("here_doc");
		exit(2);
	}
	free(input);
	close(fd);
}

void	del_heredoc(t_proc *p)
{
	bool	check;
	t_proc	*aux;

	aux = p;
	while(aux)
	{
		if (aux->hd == true)
			check = true;
	}
	if (p->hd == true || check == true)
		unlink("here_doc");
}

/* char	*ft_get_path(char **env);
{
	int	i;

	while (envp[i] && !ft_strnstr(envp[i], "PATH=", 5))
		i++;
	if (envp[i] == NULL)
		return (NULL);
	return (ft_split(envp[i] + 5, ':'));
} */