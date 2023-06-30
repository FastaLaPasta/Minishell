/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboulogn <sboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 17:07:47 by sboulogn          #+#    #+#             */
/*   Updated: 2022/11/09 13:08:47 by sboulogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t		i;
	char		*ptr;
	const char	*ptrs;

	i = 0;
	ptr = dst;
	ptrs = src;
	if (!dst && !src)
		return (NULL);
	if (ptrs < ptr)
	{
		i = len;
		while (i > 0)
		{
			i--;
			ptr[i] = ptrs[i];
		}
		return (dst);
	}
	while (i < len)
	{
		ptr[i] = ptrs[i];
		i++;
	}
	return (dst);
}
