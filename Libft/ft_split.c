/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiampor <jgiampor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 11:15:50 by sboulogn          #+#    #+#             */
/*   Updated: 2023/06/14 12:13:39 by jgiampor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**free_tab(char **tab)
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

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		if (s[i] != c && s[i] != '\0')
			j++;
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	j++;
	return (j);
}

static char	*malloc_word(char const *s, char c)
{
	size_t	len;
	char	*ptr;
	int		k;

	len = 0;
	while ((s[len] != c || s[len - 1] == '>') && s[len] != '\0')
	{
		if (s[len] == '\'' || s[len] == '"')
		{
			k = len;
			len++;
			while (s[len] != s[k] && s[len] != '\0')
				len++;
		}
		len++;
	}
	ptr = ft_substr(s, 0, len);
	return (ptr);
}

int	avance(char *s, char c)
{
	int	i;
	int	k;

	i = 0;
	while ((s[i] != c || s[i - 1] == '>') && s[i] != '\0')
	{
		if (s[i] == '\'' || s[i] == '"')
		{
			k = i;
			i++;
			while (s[i] != s[k] && s[i] != '\0')
				i++;
		}
		i++;
	}
	return (i);
}

char	**ft_split(char *s, char c)
{
	char	**splt;
	int		i;
	int		j;

	i = 0;
	j = 0;
	splt = malloc(sizeof(*splt) * word(s, c));
	if (!splt)
		return (NULL);
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		if (s[i] != c && s[i] != '\0')
		{
			splt[j] = malloc_word(s + i, c);
			if (!(splt[j]))
				return (free_tab(splt));
			j++;
		}	
		i = i + avance(s + i, c);
	}
	splt[j] = NULL;
	return (splt);
}
