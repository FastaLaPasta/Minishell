/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiampor <jgiampor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 15:34:48 by jgiampor          #+#    #+#             */
/*   Updated: 2023/04/29 16:31:13 by jgiampor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	ft_lstadd_back(t_command **lst, t_command *new)
{
	t_command	*poi;

	poi = *lst;
	if (!poi)
	{
		*lst = new;
		return ;
	}
	poi = ft_lstlast(*lst);
	poi -> next = new;
}
