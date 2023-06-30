/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboulogn <sboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:09:42 by sboulogn          #+#    #+#             */
/*   Updated: 2023/06/15 11:05:27 by sboulogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	can_we_exec(t_minishell *arg, t_command *cmd)
{
	int		i;
	char	*path;

	i = 0;
	while (arg->path[i] != NULL)
	{
		path = ft_strjoin(arg->path[i], cmd->name);
		if (access(path, X_OK) == 0)
		{
			if ((execve(path, cmd->value, arg->env)) == -1)
				perror("execve");
		}
		free(path);
		i++;
	}
}
