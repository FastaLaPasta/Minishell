/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiampor <jgiampor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 14:55:03 by sboulogn          #+#    #+#             */
/*   Updated: 2023/06/22 16:08:31 by jgiampor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

char	*dollarintmp(t_command *start, t_minishell *minishell, int i, int j)
{
	char	*tmp;

	tmp = ft_free2_join(ft_free2_join(ft_substr(start->value[i], 0, j),
				ft_itoa(minishell->etat)), ft_substr(start->value[i],
				j + 2, ft_strlen(start->value[i])));
	free(start->value[i]);
	return (tmp);
}

void	the_while(char const **s, int i[2], char *ptr)
{
	char	quotes;

	quotes = '\0';
	while (**s && i[0] < i[1])
	{
		if (**s == '\'' || **s == '"')
		{
			quotes = **s;
			(*s)++;
			while (**s != quotes)
			{
				ptr[i[0]++] = **s;
				(*s)++;
			}
		}
		else
			ptr[i[0]++] = **s;
		(*s)++;
	}
	while (**s && (**s == '\'' || **s == '"'))
		(*s)++;
}

int	nbr_cmd(t_minishell *a)
{
	int	i;

	i = 0;
	while (a->cpip[i])
	{
		i++;
	}
	return (i);
}

void	init_struct(t_minishell *minishell)
{
	ft_bzero(&minishell, sizeof(minishell));
}

void	fill_path(t_minishell	*all, char **env)
{
	char	*test;
	int		j;

	j = 0;
	test = NULL;
	while (test == NULL && env[j] != NULL)
	{
		test = ft_strnstr(env[j], "PATH=", ft_strlen(env[j]));
		j++;
	}
	if (test == NULL)
		test = "PATH= ";
	all->path = ft_split(&test[5], ':');
	j = 0;
	while (all->path[j])
	{
		all->path[j] = ft_free_join(all->path[j], "/");
		j++;
	}
}
