/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiampor <jgiampor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 11:56:37 by sboulogn          #+#    #+#             */
/*   Updated: 2023/06/10 14:32:36 by jgiampor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int	ft_nbr_case_quotes(char *value)
{
	char	**split;
	int		i;
	char	*tmp;

	tmp = value;
	i = 0;
	split = ft_split_for_quotes(tmp, ' ');
	while (split[i])
		i++;
	free_tab(split);
	return (i);
}

void	process_quotes(char *value, int **k, char *keep, int *i)
{
	if (value[*i] == '"' || value[*i] == '\'')
	{
		*keep = value[*i];
		if (value[*i] == '\'')
			**k = 1;
		else
			**k = 2;
		(*i)++;
		(*k)++;
		while ((value[*i] != *keep || value[*i + 1] != ' ')
			&& value[*i] != '\0')
			(*i)++;
	}
	else
	{
		**k = 0;
		(*k)++;
		while (value[*i] != ' ' && value[*i] != '\0')
			(*i)++;
	}
}

void	process_non_quotes(char *value, int **k, int *i)
{
	**k = 0;
	(*k)++;
	while (value[*i] != ' ' && value[*i] != '\0')
		(*i)++;
}

void	iterate_string(char *value, int *quotes)
{
	int		i;
	char	keep;

	i = 0;
	while (value[i])
	{
		while (value[i] == ' ')
			i++;
		if (value[i] == '"' || value[i] == '\'')
			process_quotes(value, &quotes, &keep, &i);
		else
			process_non_quotes(value, &quotes, &i);
		if (value[i] != '\0')
			i++;
	}
}

int	*fill_quotes(char *value)
{
	int		*quotes;
	char	*ok;

	ok = value;
	quotes = ft_calloc((ft_nbr_case_quotes(ok) + 1), sizeof(int));
	if (!quotes)
		return (NULL);
	iterate_string(ok, quotes);
	return (quotes);
}
