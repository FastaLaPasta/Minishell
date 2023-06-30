/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiampor <jgiampor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 15:34:20 by jgiampor          #+#    #+#             */
/*   Updated: 2023/06/19 17:32:40 by jgiampor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

int	ex_ec(char *splt, char *pwd, char **env)
{
	char		*env_str;
	static int	p = 0;
	int			i;

	i = 0;
	while (env[i] != NULL && ft_strncmp(*env, "_=", 2) != 0)
	{
		if (ft_strncmp(env[i], splt, ft_strlen(splt)) == 0)
		{
			if (pwd)
			{
				env_str = ft_free_join(ft_strjoin(splt, "="), pwd);
				if (p > 1 && env[i])
					free (env[i]);
				env[i] = env_str;
				p++;
			}
		}
		i++;
	}
	return (0);
}

char	*ft_cpwd(void)
{
	char	*buf;
	size_t	size;

	size = 1024;
	buf = (char *) malloc(size);
	if (buf == NULL)
	{
		perror("Erreur lors de l'allocation de mémoire");
		exit(EXIT_FAILURE);
	}
	if (getcwd(buf, size) == NULL)
	{
		perror("Erreur lors de l'obtention du chemin actuel");
		exit(EXIT_FAILURE);
	}
	return (buf);
}

int	ft_cd(char *path, t_minishell *arg)
{
	int		result;
	char	*buf;

	if (arg->cmd->value[1] == NULL)
	{
		write_errn("empty", ": need a path\n");
		return (-1);
	}
	buf = ft_cpwd();
	result = chdir(path);
	if (result != 0)
	{
		free(buf);
		perror("cd");
		return (-1);
	}
	ex_ec("OLDPWD", buf, arg->env);
	free(buf);
	buf = ft_cpwd();
	ex_ec("PWD", buf, arg->env);
	free(buf);
	return (0);
}
