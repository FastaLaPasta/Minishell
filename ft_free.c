/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboulogn <sboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 15:22:26 by jgiampor          #+#    #+#             */
/*   Updated: 2023/06/11 13:57:22 by sboulogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

extern char	**environ;

void	ft_freelst(t_command **lst)
{
	t_command	*current;
	t_command	*next;

	if (lst)
	{
		current = *lst;
		while (current)
		{
			next = current->next;
			current -> name = NULL;
			current->value = free_tab(current->value);
			free(current->limiter);
			free(current->quotes);
			free(current);
			current = next;
		}
		*lst = NULL;
	}
}

void	ft_mallocpip(t_minishell *all)
{
	int	i;

	i = 0;
	all->child = malloc(sizeof(pid_t) * all->nbr_cmd);
	all->fd = malloc(sizeof(int **) * (all->nbr_cmd + 1));
	ft_memset(all->fd, 0, sizeof(int **) * (all->nbr_cmd + 1));
	while (i < all->nbr_cmd)
	{
		all->fd[i] = malloc(sizeof(int) * 2);
		i++;
	}
}

void	ft_structfree2(t_minishell *arg)
{
	arg->cpip = free_tab(arg->cpip);
	free(arg->child);
	arg->child = NULL;
	ft_freelst(&arg->cmd);
	arg->etat = statuscode(arg->etat);
}

void	ft_structfree(t_minishell *arg)
{
	arg->fd = free_tab2(arg->fd);
	arg->path = free_tab(arg->path);
	ft_structfree2(arg);
}
