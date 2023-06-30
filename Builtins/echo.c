/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiampor <jgiampor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 13:46:32 by jgiampor          #+#    #+#             */
/*   Updated: 2023/06/22 13:56:43 by jgiampor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

int	check_sentence(char **str, int i)
{
	int			j;
	static int	err_flag = 0;

	if (ft_strncmp(str[i], "-n", -1) != 0 || i != 1)
	{	
		j = 0;
		while (str[i][j])
		{
			if ((str[i][j] != 'n' && j != 0) || str[i][0] != '-'
				|| err_flag == 1)
			{
				if (printf("%s", str[i]) < 0)
					return (-1);
				if (str[i + 1] != NULL)
					printf(" ");
				err_flag = 1;
				break ;
			}
			j++;
		}
	}
	return (0);
}

void	ft_printligne(t_command *cmd)
{
	if (cmd->value[1] == NULL)
		printf("\n");
}

int	ft_echo(t_command *cmd)
{
	int	i;
	int	j;

	i = 1;
	while (cmd->value[i])
	{
		if (check_sentence(cmd->value, i) == -1)
			return (-1);
		i++;
	}
	if (cmd->value[1] && ft_strncmp(cmd->value[1], "-n", -1) != 0)
	{
		j = 0;
		while (cmd->value[1][j])
		{
			if ((cmd->value[1][j] != 'n' && j != 0) || cmd->value[1][0] != '-')
			{
				printf("\n");
				break ;
			}
			j++;
		}
	}
	ft_printligne(cmd);
	return (0);
}
