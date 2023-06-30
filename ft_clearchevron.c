/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clearchevron.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboulogn <sboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 15:30:52 by jgiampor          #+#    #+#             */
/*   Updated: 2023/06/14 14:04:14 by sboulogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int	handle_quotes_her(char	*org)
{
	int		total;
	int		i;
	char	quotes;

	total = 0;
	i = 0;
	if (org[i] == '\'' || org[i] == '"')
	{
		quotes = org[i++];
		total++;
		while (org[i] != quotes && org[i] != '\0')
		{
			i++;
			total++;
			if (org[i] == '\0')
				return (total);
		}
		i++;
		total++;
	}
	return (total);
}

int	get_total_characters(char *org)
{
	int		total;
	int		i;

	total = 0;
	i = 0;
	while (org[i])
	{
		if (org[i] == '\'' || org[i] == '"')
		{
			i += handle_quotes_her(org + i);
			total = i;
			if (org[i] == '\0')
				return (total);
		}
		if (org[i] && (org[i] == '>' || org[i] == '<'))
			i += strlen_mallocsize(org + i + 1) + 1;
		else if (org[i] != '\0')
		{
			i++;
			total++;
		}
	}
	return (total);
}

char	*ft_clearchevron(char *org)
{
	char		*cop;
	size_t		i[3];

	cop = ft_calloc(get_total_characters(org) + 1, sizeof(char));
	if (!cop)
		return (NULL);
	i[0] = 0;
	i[1] = 0;
	while (org[i[0]] && i[0] <= ft_strlen(org))
	{
		if (org[i[0]] == '\'' || org[i[0]] == '"')
		{
			i[2] = i[0];
			cop[i[1]++] = org[i[0]++];
			while (org[i[0]] != org[i[2]] && org[i[0]] != '\0')
				cop[i[1]++] = org[i[0]++];
			cop[i[1]++] = org[i[0]++];
		}
		else if (org[i[0]] == '>' || org[i[0]] == '<')
			i[0] += strlen_mallocsize(org + i[0] + 1) + 1;
		else if (org[i[0]] != '\0' && i[0] <= ft_strlen(org))
			cop[i[1]++] = org[i[0]++];
	}
	cop[i[1]] = '\0';
	return (cop);
}
