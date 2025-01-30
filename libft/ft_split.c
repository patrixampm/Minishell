/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeckham <ppeckham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 12:14:28 by ppeckham          #+#    #+#             */
/*   Updated: 2025/01/16 13:17:08 by ppeckham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_freeup(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		free(str);
		i++;
	}
	free(str);
}

static int	check_num(char const *s, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			j++;
			while (s[i] != c && s[i] != '\0')
				i++;
			if (s[i] == '\0')
				return (j);
		}
		i++;
	}
	return (j);
}

static int	word_len(char const *s, char c, int j)
{
	int	len;

	len = 0;
	while (s[j] == c && s[j] != '\0')
		j++;
	while (s[j] != c && s[j] != '\0')
	{
		len++;
		j++;
	}
	return (len);
}

static char	*get_word(char const *s, char c, int *pj)
{
	char	*nstr;
	int		i;
	int		j;
	int		wordlen;

	i = *pj;
	j = 0;
	while (s[i] == c && s[i] != '\0')
		i++;
	wordlen = word_len(s, c, i);
	nstr = malloc(sizeof(char) * wordlen + 1);
	if (nstr == NULL)
		return (NULL);
	while (s[i] != c && s[i] != '\0')
	{
		nstr[j] = s[i];
		j++;
		i++;
	}
	nstr[j] = '\0';
	*pj = i;
	return (nstr);
}

char	**ft_split(char const *s, char c)
{
	int		words;
	char	**wordlist;
	int		i;
	int		j;

	words = check_num(s, c);
	wordlist = malloc((words + 1) * sizeof(char *));
	i = 0;
	j = 0;
	if (!wordlist)
		return (NULL);
	wordlist[words] = NULL;
	while (i < words)
	{
		wordlist[i] = get_word(s, c, &j);
		if (wordlist[i] == NULL)
			ft_freeup(wordlist[i]);
		i++;
	}
	return (wordlist);
}
