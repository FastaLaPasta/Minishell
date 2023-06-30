/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_test_man.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiampor <jgiampor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 11:25:43 by jgiampor          #+#    #+#             */
/*   Updated: 2023/06/19 11:28:23 by jgiampor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

char	*len_dollar2(int	*len, char *str, int q)
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
		}
		(*len)++;
		i++;
	}
	return (NULL);
}

void	ft_fake_heredoc(t_command *all)
{
	char	*tmp;

	tmp = readline("<");
	while (ft_strncmp(tmp, all->limiter, -1) != 0)
	{
		free(tmp);
		tmp = readline("<");
	}
	free(tmp);
}

char	*return_char(char *str, char *tmp)
{
	free(tmp);
	return (str);
}

char	*dollarinhdoc(char *start, t_minishell *minishell, int j)
{
	char	*tmp;

	tmp = ft_free2_join(ft_free2_join(ft_substr(start, 0, j),
				ft_itoa(minishell->etat)), ft_substr(start,
				j + 2, ft_strlen(start)));
	free(start);
	return (tmp);
}

char	*true_file_heredoc(char *str, int q)
{
	char		*file;
	int			len;
	char		*tmp;

	len = 0;
	tmp = len_dollar2(&len, str, q);
	if (tmp != NULL && tmp[0] != '$' && tmp[0] != '?')
		return (tmp);
	if (tmp)
		free(tmp);
	file = ft_calloc((ft_strlen(str) + len + 6), sizeof(char));
	if (!file)
		return (NULL);
	ft_i_file(str, q, file);
	return (file);
}
