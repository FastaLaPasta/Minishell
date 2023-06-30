/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiampor <jgiampor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 14:13:25 by jgiampor          #+#    #+#             */
/*   Updated: 2023/06/24 13:24:32 by jgiampor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

void	ft_wrernoexp(char *value)
{
	char	*tmp;

	tmp = ft_strjoin("export: `", value);
	write_errn(tmp, "': not a valid identifier\n");
	free(tmp);
}

void	ft_addexp(char **splt, char **env)
{
	char	*tmp;
	char	*env_str;

	if (splt[1])
	{
		tmp = ft_strjoin(splt[0], "=");
		env_str = ft_free_join(tmp, splt[1]);
	}
	else
		env_str = ft_strjoin(splt[0], "");
	while (*env && ft_strncmp(*env, "_=", 2) != 0)
		env++;
	tmp = *env;
	*env = env_str;
	*(env + 1) = tmp;
	*(env + 2) = NULL;
}	

void	print_environment(char **env)
{
	int		i;
	char	*equal_sign;

	i = 0;
	while (env && env[i] != NULL && ft_strncmp(env[i], "_=", 2) != 0)
	{
		equal_sign = ft_strchr(env[i], '=');
		if (equal_sign != NULL)
		{
			*equal_sign = '\0';
			printf("declare -x %s=\"%s\"\n", env[i], equal_sign + 1);
			*equal_sign = '=';
		}
		else
			printf("declare -x %s=\"\"\n", env[i]);
		i++;
	}
}

void	sort_environment(char **env)
{
	int		i;
	int		j;
	char	*tmp;
	int		size;

	size = 0;
	i = 0;
	while (env && env[size] != NULL && ft_strncmp(env[size], "_=", 2) != 0)
		size++;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - i - 1)
		{
			if (ft_strncmp(env[j], env[j + 1], -1) > 0)
			{
				tmp = env[j];
				env[j] = env[j + 1];
				env[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

int	ft_export(char **value, char **env, t_minishell	*arg)
{
	int		i[3];
	char	**splt;

	i[1] = 1;
	if (value[i[1]] == NULL)
		return (exp_only(env));
	while (value[i[1]] != NULL)
	{
		splt = ft_split_for_quotes(value[i[1]], '=');
		if (splt[0] == NULL)
		{
			ft_wrernoexp(value[i[1]]);
			arg->etat = 1;
			free_tab(splt);
			return (0);
		}
		i[2] = ft_experr0(splt, value, arg, i[1]);
		i[0] = 0;
		exp_exec(i, splt, env);
		if (i[2] == 0)
			ft_addexp(splt, env);
		free_tab(splt);
		i[1]++;
	}
	return (0);
}
