/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboulogn <sboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 19:07:42 by sboulogn          #+#    #+#             */
/*   Updated: 2022/11/10 12:39:20 by sboulogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count(int c)
{
	int	i;

	i = 0;
	if (c <= 0)
	{
		while (c < 0)
		{
			i++;
			c = (c / 10);
		}
		i++;
		return (i);
	}
	while (c > 0)
	{
		i++;
		c = (c / 10);
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char			*ptr;
	int				j;
	unsigned int	res;
	int				sign;

	j = count(n);
	res = n;
	sign = 1;
	ptr = malloc(sizeof(char) * (j + 1));
	if (!ptr)
		return (NULL);
	if (n < 0)
		res = n * -1;
	if (n < 0)
		sign *= -1;
	ptr[j] = '\0';
	while (j > 0)
	{
		j--;
		ptr[j] = ((res % 10) + '0');
		res = (res / 10);
	}
	if (ptr[j] == 48 && sign < 0)
		ptr[j] = 45;
	return (ptr);
}
