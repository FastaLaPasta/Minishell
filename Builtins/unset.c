/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiampor <jgiampor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 16:47:28 by jgiampor          #+#    #+#             */
/*   Updated: 2023/06/24 13:25:20 by jgiampor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

int	ft_unset(char *av, char **envp)
{
	int			i[2];
	static int	p = 0;

	i[0] = 0;
	if (av == NULL)
		return (0);
	//besoin de la verif de export dans unset
	while (envp[i[0]])
	{
		if (ft_strncmp(envp[i[0]], av, ft_strlen(av)) == 0
			&& envp[i[0]][ft_strlen(av)] == '=')
		{
			i[1] = i[0];
			if (p > 0)
				free(envp[i[1]]);
			while (envp[i[1] + 1])
			{
				envp[i[1]] = envp[i[1] + 1];
				i[1]++;
			}
			envp[i[1]] = NULL;
		}
		i[0]++;
	}
	p++;
	return (0);
}
