/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiampor <jgiampor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 14:18:04 by jgiampor          #+#    #+#             */
/*   Updated: 2023/06/22 13:27:43 by jgiampor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

int	ui(t_command *cmd)
{
	char	*tmp;

	tmp = ft_strjoin("exit: ", cmd->value[1]);
	write_errn(tmp, ": numeric argument required\n");
	free (tmp);
	return (255);
}

int	ft_exit(t_minishell *arg, t_command *cmd)
{
	int		i;

	i = 0;
	if (cmd->value[1] != NULL)
	{
		while (cmd->value[1][i])
		{
			if ((ft_isdigit(cmd->value[1][i]) == 0 && cmd->value[1][i]
				!= '+' && cmd->value[1][i] != '-') ||
					ft_atoi(cmd->value[1]) > 9223372036854775807)
				exit (ui(cmd));
			i++;
			if (cmd->value[1] != NULL && cmd->value[2] != NULL)
			{
				write_errn("exit: ", "too many arguments\n");
				arg->etat = 1;
				return (0);
			}	
		}
		exit (ft_atoi(cmd->value[1]));
	}
	exit (statuscode(arg->etat));
}
