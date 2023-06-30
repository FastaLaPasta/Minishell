/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_analize2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiampor <jgiampor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 16:08:50 by jgiampor          #+#    #+#             */
/*   Updated: 2023/06/18 16:29:51 by jgiampor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int	ft_strlenfw2(char *str, int i, char quotes)
{
	int		count;

	count = 0;
	while (ft_skip(str[i]) == 1)
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			quotes = str[i];
			i++;
			count++;
			while (str[i] != quotes && str[i] != '\0')
			{
				i++;
				count++;
			}
		}
		if (ft_skip(str[i]) == 1)
		{
			i++;
			count++;
		}
	}
	return (count);
}

int	ft_strlenfw1(char *str)
{
	int		i;
	char	quotes;

	i = 0;
	quotes = '\0';
	while (((str[i] >= 9 && str[i] <= 13) || str[i] == 32) && str[i] != '\0')
		i++;
	return (ft_strlenfw2(str, i, quotes));
}

char	*true_dollars(char	*str)
{
	int		i;
	char	*cop;
	int		j;

	j = 0;
	i = 1;
	cop = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (!cop)
		return (NULL);
	if (str[i] == '?')
	{
		cop[j] = str[i];
		cop[j + 1] = '\0';
		return (cop);
	}
	if (str[i] != ' ')
	{
		while (ft_skip(str[i]) == 1 && str[i] != '$'
			&& str[i] != '\'' && str[i] != '"' && str[i] != ':')
			cop[j++] = str[i++];
	}
	if (j == 0)
		cop[j++] = '$';
	cop[j] = '\0';
	return (cop);
}

void	error_right(char *file)
{
	write(2, "Minishell: ", 12);
	write(2, file, ft_strlen(file));
	write(2, ": ", 2);
	perror("");
}

int	ft_opensimple(char *file, int how_many_chvr)
{
	int	i;
	int	*q;

	q = fill_quotes(file);
	file = true_file(file, q[0]);
	free(q);
	if (!file)
	{
		write(1, "Minishell : ambiguous redirect\n", 31);
		return (-1);
	}
	if (how_many_chvr == 1)
		i = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (how_many_chvr == 2)
		i = open(file, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (how_many_chvr == 3)
		i = open(file, O_RDONLY);
	if (i < 0)
		error_right(file);
	free(file);
	return (i);
}
