/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboulogn <sboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 15:44:52 by sboulogn          #+#    #+#             */
/*   Updated: 2022/11/10 16:12:13 by sboulogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	strtrim_verif_start(char const *s1, char const *set, size_t j)
{
	size_t	i;
	size_t	k;

	i = 0;
	k = 0;
	while (set[i] != '\0')
	{
		if (s1[j] == set[i])
		{
			j++;
			k = j;
			i = 0;
		}
		else
			i++;
	}
	return (k);
}

static size_t	strtrim_verif_end(char const *s1, char const *set, size_t j,
	size_t start)
{
	size_t	i;
	size_t	k;

	i = 0;
	k = 0;
	while (set[i] != '\0' && j > start)
	{
		if (s1[j - 1] == set[i])
		{
			j--;
			k++;
			i = 0;
		}
		else
			i++;
	}
	return (k);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ptr;
	size_t	start;
	size_t	end;

	if (!s1 || !set)
		return (NULL);
	start = strtrim_verif_start(s1, set, 0);
	end = strtrim_verif_end(s1, set, ft_strlen(s1), start);
	ptr = ft_substr(s1, start, ft_strlen(s1) - (start + end));
	return (ptr);
}
