/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiampor <jgiampor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 15:51:23 by jgiampor          #+#    #+#             */
/*   Updated: 2023/06/22 13:19:25 by jgiampor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int	statuscode(int etat)
{
	int	statuscode;

	if (etat == 1)
		return (1);
	statuscode = 0;
	if (WIFEXITED(etat))
	{
		statuscode = WEXITSTATUS(etat);
		if (statuscode != 0)
			return (statuscode);
	}
	return (statuscode);
}

void	write_errn(char *s, char *t)
{
	write(2, "minishell: ", 11);
	write(2, s, ft_strlen(s));
	write(2, t, ft_strlen(t));
}

int	accesserr(t_command	*cmd)
{
	if (cmd->value[1] == NULL && cmd->value[0][0]
		!= '.' && nbr_slash(cmd->value[0]) == 0)
	{
		write_errn(cmd->name, ": command not found\n");
		exit (127);
	}
	if (access(cmd->name, F_OK) == 0)
	{
		if (open(cmd->name, O_DIRECTORY) != -1)
		{
			write_errn(cmd->name, ": is a directory\n");
			exit (126);
		}
		write_errn(cmd->name, ": Permission denied\n");
		exit (126);
	}
	if (access(cmd->name, F_OK) == -1 && open(cmd->name, O_DIRECTORY) == -1
		&& access(cmd->name, X_OK) == -1
		&& cmd->name[0] != '/' && cmd->name[0] != '.')
	{
		write_errn(cmd->name, ": Permission denied\n");
		exit (126);
	}
	write_errn(cmd->name, ": No such file or directory\n");
	exit (127);
}
