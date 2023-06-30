/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiampor <jgiampor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 14:52:22 by sboulogn          #+#    #+#             */
/*   Updated: 2023/06/11 12:50:48 by jgiampor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char const *s2)
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
	while (i <= ft_strlen(s2))
	{
		ptr[j + i] = s2[i];
		i++;
	}
	return (ptr);
}
