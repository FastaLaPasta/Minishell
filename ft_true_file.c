/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_true_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiampor <jgiampor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 12:13:01 by sboulogn          #+#    #+#             */
/*   Updated: 2023/06/18 17:24:31 by jgiampor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

char	*len_dollar(int	*len, char *str, int q)
{
	int		i;
	char	*tmp;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && q != 1)
		{
			tmp = true_dollars(str + i);
			if (!tmp)
				return (NULL);
			if ((tmp[0]) != '?')
			{
				if (tmp[0] == '$')
					return (tmp);
				ft_getenv(tmp, len);
			}
			else if (tmp[0] == '?')
				return (tmp);
		}
		(*len)++;
		i++;
	}
	return (NULL);
}

int	dollarinquote(char *file, char *str, int *d, int q)
{
	char	quotes;
	int		i;

	i = 0;
	quotes = str[(i)++];
	while (str[i] != quotes && str[i] != '\0')
	{
		if (str[i] == '$' && q != 1)
			interogation_after_dollar(str, &file, d, &i);
		else
			file[(*d)++] = str[i++];
	}
	i++;
	return (i);
}

int	free_if_dollardollar(char *tmp)
{
	free(tmp);
	return (1);
}

int	dollaroutquote(char *file, char *str, int *d, int q)
{
	char	*dollar;
	int		i;
	char	*tmp;

	i = 0;
	if (str[i] == '$' && q != 1)
	{
		tmp = true_dollars(str + i);
		if (!tmp)
			return (1);
		if (tmp[0] == '$')
		{
			file[(*d)++] = str[i++];
			return (free_if_dollardollar(tmp));
		}
		if (tmp[0] != '?')
		{
			dollar = getenv(tmp);
			ft_movein_dollar(dollar, file, d);
			i = ft_increase_i(str, i);
		}
		free(tmp);
	}
	file[(*d)++] = str[i++];
	return (i);
}

char	*true_file(char *str, int q)
{
	char		*file;
	int			len;
	char		*tmp;

	len = 0;
	tmp = len_dollar(&len, str, q);
	if (tmp != NULL && tmp[0] != '$' && tmp[0] != '?')
		return (tmp);
	if (tmp)
		free(tmp);
	file = ft_calloc((ft_strlen(str) + len + 2), sizeof(char));
	if (!file)
		return (NULL);
	ft_i_file(str, q, file);
	free(str);
	return (file);
}
