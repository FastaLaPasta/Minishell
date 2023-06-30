/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_join.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiampor <jgiampor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 10:11:25 by sboulogn          #+#    #+#             */
/*   Updated: 2023/06/19 17:21:55 by jgiampor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_free2_join(char *s1, char *s2)
{
	char		*ptr;
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	ptr = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (!ptr)
		return (NULL);
	while (j < ft_strlen(s1))
	{
		ptr[j] = s1[j];
		j++;
	}
	free(s1);
	while (i <= ft_strlen(s2))
	{
		ptr[j + i] = s2[i];
		i++;
	}
	free(s2);
	return (ptr);
}

char	*ft_free_join(char *s1, char const *s2)
{
	char		*ptr;
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	ptr = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (!ptr)
		return (NULL);
	while (j < ft_strlen(s1))
	{
		ptr[j] = s1[j];
		j++;
	}
	free(s1);
	while (i <= ft_strlen(s2))
	{
		ptr[j + i] = s2[i];
		i++;
	}
	return (ptr);
}
