/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboulogn <sboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 14:11:09 by sboulogn          #+#    #+#             */
/*   Updated: 2022/11/09 11:39:50 by sboulogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*a;

	a = s;
	s = s + ft_strlen(s);
	if ((char)c == '\0')
		return ((char *)s);
	s--;
	while (s >= a)
	{
		if (*s == (unsigned char)c)
			return ((char *)s);
		s--;
	}
	return (NULL);
}
