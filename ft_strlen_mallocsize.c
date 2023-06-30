/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen_mallocsize.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiampor <jgiampor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 11:04:34 by sboulogn          #+#    #+#             */
/*   Updated: 2023/05/28 12:47:22 by jgiampor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int	is_whitespace_or_pipe(char c)
{
	return ((c >= 9 && c <= 13) || c == 32 || c == '|');
}

int	count_initial_chars(char *str, int *i)
{
	int	j;
	int	count;

	j = *i;
	count = 0;
	while (is_whitespace_or_pipe(str[j]) && str[j] != '\0')
	{
		count++;
		j++;
	}
	*i = j;
	return (count);
}

int	count_quoted_chars(char *str, char quote, int *i)
{
	int	j;
	int	count;

	j = *i;
	count = 0;
	while (str[j] != quote && str[j] != '\0')
	{
		j++;
		count++;
	}
	j++;
	*i = j;
	return (count);
}

int	skip_special_chars(char *str, int *i)
{
	int		count;
	char	quote;
	int		j;

	j = *i;
	count = 0;
	while (ft_skip(str[j]) == 1)
	{
		if (str[j] == '\'' || str[j] == '"')
		{
			quote = str[j];
			j++;
			count++;
			count += count_quoted_chars(str + j, quote, i);
			j = *i;
		}
		if (ft_skip(str[j]) == 1)
		{
			j++;
			count++;
		}
	}
	*i = j;
	return (count);
}

int	strlen_mallocsize(char *str)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	count += count_initial_chars(str, &i);
	count += skip_special_chars(str, &i);
	return (count);
}
