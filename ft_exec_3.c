/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiampor <jgiampor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 12:47:07 by jgiampor          #+#    #+#             */
/*   Updated: 2023/06/19 13:18:51 by jgiampor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int	nbr_slash(char *str)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			count++;
		i++;
	}
	return (count);
}

int	error_bck_slash(char *str)
{
	int	slash;

	slash = nbr_slash(str);
	if ((slash == 1 && str[0] == '/' ) || slash == 0)
		return (0);
	return (slash);
}
