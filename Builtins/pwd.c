/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiampor <jgiampor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 14:45:52 by jgiampor          #+#    #+#             */
/*   Updated: 2023/06/02 13:36:01 by jgiampor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

int	ft_pwd(void)
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
	printf("%s\n", buf);
	free(buf);
	return (0);
}
