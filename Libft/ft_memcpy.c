/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboulogn <sboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 16:17:44 by sboulogn          #+#    #+#             */
/*   Updated: 2022/11/09 13:07:18 by sboulogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t		i;
	char		*ptr;
	const char	*ptrs;

	ptr = dst;
	ptrs = src;
	i = 0;
	if (!dst && !src)
		return (NULL);
	while (i < n)
	{
		ptr[i] = ptrs[i];
		i++;
	}
	return (dst);
}
