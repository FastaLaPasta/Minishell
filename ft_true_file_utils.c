/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_true_file_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiampor <jgiampor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 13:18:02 by jgiampor          #+#    #+#             */
/*   Updated: 2023/06/18 16:34:27 by jgiampor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int	ft_increase_i(char *str, int i)
{
	i++;
	while (ft_skip(str[i]) == 1 && str[i] != '$'
		&& str[i] != '\'' && str[i] != '"' && str[i] != ':')
		i++;
	return (i);
}

void	ft_movein_dollar(char *dollar, char *file, int *d)
{
	int		k;

	k = 0;
	while (file && dollar && dollar[k])
		file[(*d)++] = dollar[k++];
}

void	ft_i_file(char *str, int q, char *file)
{
	size_t		i;
	int			d;

	d = 0;
	i = 0;
	while (i < ft_strlen(str) && str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			i += dollarinquote(file, str + i, &d, q);
		else
			i += dollaroutquote(file, str + i, &d, q);
	}
	file[d] = '\0';
}

void	ft_getenv(char *tmp, int	*len)
{
	char	*dollar;

	dollar = getenv(tmp);
	free(tmp);
	if (dollar)
		*len = *len + ft_strlen(dollar);
}

int	interogation_after_dollar(char *str, char **file, int *d, int *i)
{
	char	*dollar;
	char	*tmp;

	tmp = true_dollars(str + (*i));
	if (!tmp)
		return (1);
	if (tmp[0] == '$')
	{
		*file[(*d)++] = str[(*i)++];
		free(tmp);
		return (1);
	}
	if (tmp[0] != '?')
	{
		dollar = getenv(tmp);
		free(tmp);
		if (!dollar)
			return (0);
		ft_movein_dollar(dollar, *file, d);
		while (ft_skip(str[(*i)]) == 1 && str[(*i)] != '$')
			(*i)++;
	}
	return (0);
}
