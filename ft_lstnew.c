/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiampor <jgiampor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 14:53:08 by jgiampor          #+#    #+#             */
/*   Updated: 2023/06/19 16:57:52 by jgiampor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

t_command	*ft_lstnew(char	*content)
{
	t_command	*new;
	char		**spliter;
	char		*tmp;

	new = ft_calloc(1, sizeof(*new));
	if (!new)
		return (NULL);
	if (ft_analize(content, new) == -1)
		return (NULL);
	tmp = ft_clearchevron(content);
	spliter = ft_split_for_quotes(tmp, ' ');
	if ((new && *spliter) || new->limiter != NULL)
	{	
		new -> value = spliter;
		new -> quotes = fill_quotes(tmp);
		new -> name = spliter[0];
		new -> next = NULL;
	}
	else
	{
		new -> output_file = -2;
		new -> input_file = -2;
	}
	free(tmp);
	return (new);
}
