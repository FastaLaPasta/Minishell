/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiampor <jgiampor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 12:53:43 by sboulogn          #+#    #+#             */
/*   Updated: 2023/06/18 14:56:51 by jgiampor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	ft_shlvl2(char **environ, int i, char *shlvl_value)
{
	char		*new_shlvl_str;
	char		*new_env_var;
	int			new_shlvl;

	new_shlvl = 0;
	new_shlvl_str = NULL;
	new_env_var = NULL;
	if (shlvl_value != NULL)
	{
		new_shlvl = ft_atoi(shlvl_value) + 1;
		new_shlvl_str = ft_itoa(new_shlvl);
		new_env_var = ft_strjoin("SHLVL=", new_shlvl_str);
		if (new_env_var != NULL)
		{
			environ[i] = new_env_var;
		}
		free(new_shlvl_str);
	}
}

void	ft_shlvl(char **environ)
{
	int			i;
	char		*shlvl_value;
	int static	j = 0;

	if (j > 0)
		return ;
	j++;
	shlvl_value = NULL;
	i = 0;
	while (environ[i] != NULL)
	{
		if (ft_strncmp(environ[i], "SHLVL=", ft_strlen("SHLVL=")) == 0)
		{
			shlvl_value = environ[i] + ft_strlen("SHLVL=");
			break ;
		}
		i++;
	}
	ft_shlvl2(environ, i, shlvl_value);
}

int	ft_replacedollar(t_command *start, t_minishell *minishell)
{
	int		i;
	int		j;

	i = 0;
	while (start->value != NULL && start->value[i] != NULL)
	{
		j = 0;
		while (start->value[i][j] != '\0')
		{
			if (start->value[i][j] == '$' && start->quotes[i] != 1)
			{
				start->value[i] = true_file(start->value[i], start->quotes[i]);
				if (start->value[i] == NULL)
					return (-1);
				if (start->value[i][j + 1] == '?')
					start->value[i] = dollarintmp(start, minishell, i, j);
				if (i == 0)
					start->name = start->value[i];
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	fill_lst(t_minishell *minishell)
{
	t_command	*new;
	t_command	*start;
	int			i;

	i = 0;
	new = NULL;
	start = NULL;
	while (minishell->cpip[i])
	{
		new = ft_lstnew(minishell->cpip[i]);
		ft_lstadd_back(&start, new);
		i++;
	}
	minishell->cmd = start;
	while (start)
	{
		if (ft_replacedollar(start, minishell) == -1)
			return (-1);
		start = start->next;
	}
	return (0);
}

int	fill_struct(t_minishell *minishell, char **env)
{
	if (minishell == NULL)
		init_struct(minishell);
	minishell->cpip = ft_split(minishell->input, '|');
	fill_path (minishell, env);
	if (fill_lst(minishell) == -1)
		return (-1);
	minishell->nbr_cmd = nbr_cmd(minishell);
	minishell->env = env;
	ft_shlvl(minishell->env);
	return (0);
}
