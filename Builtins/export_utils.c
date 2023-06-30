/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiampor <jgiampor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 13:30:42 by sboulogn          #+#    #+#             */
/*   Updated: 2023/06/24 13:24:33 by jgiampor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

int	ft_experr0(char **splt, char **value, t_minishell *arg, int j)
{
	int	i;

	i = 1;
	while (splt[0][i])
	{
		if (ft_isalpha(splt[0][0]) == 0 && splt[0][0] != '_')
		{
			ft_wrernoexp(value[j]);
			arg->etat = 1;
			return (1);
		}
		else if (ft_isalnum(splt[0][i]) == 0)//verifier le premier again
		{
			ft_wrernoexp(value[j]);
			arg->etat = 1;
			return (1);
		}	
		i++;
	}
	return (0);
}

size_t	ft_len_space(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

int	exp_exec(int *i, char **splt, char **env)
{
	char		*env_str;
	static int	p = 0;

	while (i[2] == 0 && env[i[0]] != NULL && ft_strncmp(*env, "_=", 2) != 0)
	{
		if (ft_strncmp(env[i[0]], splt[0], ft_len_space(env[i[0]])) == 0)
		{
			if (splt[1])
				env_str = ft_free_join(ft_strjoin(splt[0], "="), splt[1]);
			else
				env_str = ft_strjoin(splt[0], "=");
			if (p > 0 && env[i[0]])//protection a refaire
				free (env[i[0]]);
			env[i[0]] = env_str;
			i[2] = 1;
		}
		i[0]++;
	}
	p++;
	return (0);
}

int	exp_only(char **env)
{
	char	**tmp;
	int		i;

	i = 0;
	while (env[i])
		i++;
	tmp = malloc(sizeof(char **) * (i + 1));
	i = 0;
	while (env[i])
	{
		tmp[i] = malloc(sizeof(char *) * ((ft_strlen(env[i]))));
		ft_strlcpy(tmp[i], env[i], ft_strlen(env[i]) + 1);
		i++;
	}
	tmp[i] = NULL;
	sort_environment(tmp);
	print_environment(tmp);
	free_tab(tmp);
	return (0);
}
