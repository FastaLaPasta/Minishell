/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiampor <jgiampor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:04:01 by jgiampor          #+#    #+#             */
/*   Updated: 2023/06/22 15:54:10 by jgiampor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	handle_signal3(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		exit (1);
	}
	if (signal == SIGQUIT)
		return ;
}

void	close_everything(t_minishell *arg, int i)
{
	int	j;

	j = 0;
	if (arg->nbr_cmd == 1)
		return ;
	while (j < arg->nbr_cmd)
	{
		if (j != i || i == 0)
			close(arg->fd[j][0]);
		if (j != (i + 1))
			close(arg->fd[j][1]);
		j++;
	}
}

int	ft_skip(char c)
{
	if (c != ' ' && c != '\t' && c != '\n' && c != '\0'
		&& c != '>' && c != '<')
		return (1);
	return (0);
}

int	choise(t_minishell *arg, t_command *cmd)
{
	if (!cmd)
		return (9);
	if (ft_strncmpmaj(cmd->name, "pwd", -1) == 0)
		return (exec(arg, cmd, 0));
	if (ft_strncmpmaj(cmd->name, "echo", -1) == 0)
		return (exec(arg, cmd, 0));
	if (ft_strncmp(cmd->name, "cd", -1) == 0)
		return (exec_built_in(arg, cmd));
	if (ft_strncmp(cmd->name, "export", -1) == 0)
		return (exec_built_in(arg, cmd));
	if (ft_strncmp(cmd->name, "unset", -1) == 0)
		return (exec_built_in(arg, cmd));
	if (ft_strncmpmaj(cmd->name, "env", -1) == 0)
		return (exec_built_in(arg, cmd));
	if (ft_strncmp(cmd->name, "exit", -1) == 0)
		return (exec_built_in(arg, cmd));
	return (1);
}

char	*ft_replacedollar_heredoc(char *tmp, t_minishell *minishell)
{
	int		j;
	char	*add;
	int		l;

	l = 0;
	j = 0;
	add = NULL;
	if (!tmp)
		return (NULL);
	if (tmp[j] == '$')
	{
		if (add)
			free (add);
		add = true_file_heredoc(tmp, 0);
		if (add == NULL)
			return (NULL);
		l = ft_strchrint(add, '$');
		if (add[l + 1] == '?')
			add = dollarinhdoc(add, minishell, l);
	}
	if (add)
		return (return_char(add, tmp));
	return (tmp);
}
