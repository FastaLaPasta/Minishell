/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiampor <jgiampor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 13:11:06 by sboulogn          #+#    #+#             */
/*   Updated: 2023/06/22 16:08:25 by jgiampor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

char	**free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return (NULL);
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

static size_t	word(char const *s, char c)
{
	size_t	i;
	size_t	j;
	char	keep;

	i = 0;
	j = 1;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		if (s[i] != c && s[i] != '\0')
			j++;
		while (s[i] != c && s[i] != '\0')
		{
			if (s[i] == '"' || s[i] == '\'')
			{
				keep = s[i];
				i++;
				while (s[i] != keep && s[i] != '\0')
					i++;
			}
			i++;
		}
	}
	return (j);
}

static int	ft_len(char const *s, char c)
{
	size_t	count;
	char	quotes;
	int		i;

	count = 0;
	i = 0;
	while ((s[i] != c && s[i] != '\0'))
	{
		if (s[i] == '\'' || s[i] == '"')
		{
			quotes = s[i];
			i++;
			while (s[i] != quotes)
			{
				if (s[i] == '\0')
					return (-1);
				count++;
				i++;
			}
		}
		else
			count++;
		i++;
	}
	return (count);
}

static char	*malloc_word(char const **s, char c)
{
	char	*ptr;
	int		i[2];

	i[0] = 0;
	i[1] = ft_len(*s, c);
	ptr = ft_calloc(i[1] + 1, sizeof(char));
	if (!ptr || i[1] == -1)
		return (NULL);
	the_while(s, i, ptr);
	ptr[i[0]] = '\0';
	return (ptr);
}

char	**ft_split_for_quotes(char const *s, char c)
{
	char	**splt;
	int		j;

	j = 0;
	splt = ft_calloc(word(s, c), sizeof(char *));
	if (!splt)
		return (NULL);
	while (*s != '\0')
	{
		while (*s == c && *s != '\0')
			s++;
		if (*s != c && *s != '\0')
		{
			splt[j] = malloc_word(&s, c);
			if (!(splt[j]))
				return (free_tab(splt));
			j++;
		}	
	}
	splt[j] = NULL;
	return (splt);
}
