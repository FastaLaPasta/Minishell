/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiampor <jgiampor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 17:18:18 by sboulogn          #+#    #+#             */
/*   Updated: 2023/06/02 16:29:54 by jgiampor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned long long	ft_atoi(const char *str)
{
	unsigned long long	i;
	unsigned long long	sign;
	unsigned long long	res;

	i = 0;
	sign = 1;
	res = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		sign = 0;
		i++;
	}		
	while (ft_isdigit(str[i]))
		res = (res * 10) + str[i++] - '0';
	if (sign == 0)
		res = 9223372036854775807 - res + 1;
	return (res);
}
