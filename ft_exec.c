/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiampor <jgiampor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 15:03:14 by jgiampor          #+#    #+#             */
/*   Updated: 2023/06/22 16:04:50 by jgiampor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int	access_path(t_minishell *arg, t_command	*cmd)
{
	int		j;

	j = 0;
	if (!cmd->name)
		return (0);
	if (cmd->name[0] == '\0' && cmd->value[1] != NULL)
	{
		while (cmd->value[j][0] == '\0')
			j++;
		if (cmd->value[j] != NULL)
		{
			cmd->name = cmd->value[j];
			cmd->value = &cmd->value[j];
		}
		else
			return (0);
	}
	if (cmd->name[0] == '\0')
		return (0);
	can_we_exec(arg, cmd);
	if (open(cmd->name, O_DIRECTORY) == -1 && access(cmd->name, X_OK) == 0)
		if (error_bck_slash(cmd->name) > 0)
			if ((execve(cmd->name, cmd->value, arg->env)) == -1)
				perror("execve");
	return (accesserr(cmd));
}

void	ft_here_doc(t_minishell *arg, t_command *all)
{
	char				*tmp;
	int					heredocpipe[2];
	struct sigaction	si;

	ft_memset(heredocpipe, 0, sizeof(heredocpipe));
	pipe(heredocpipe);
	si.sa_handler = &handle_signal3;
	sigemptyset(&si.sa_mask);
	si.sa_flags = SA_RESTART;
	rl_catch_signals = 0;
	sigaction(SIGQUIT, &si, NULL);
	sigaction(SIGINT, &si, NULL);
	tmp = readline("<");
	while (tmp && ft_strncmp(tmp, all->limiter, -1) != 0)
	{
		tmp = ft_replacedollar_heredoc(tmp, arg);
		write(heredocpipe[1], tmp, ft_strlen(tmp));
		write(heredocpipe[1], "\n", 1);
		free(tmp);
		tmp = readline("<");
	}
	free(tmp);
	dup2(heredocpipe[0], STDIN_FILENO);
	close(heredocpipe[1]);
}

int	exec(t_minishell *arg, t_command *cmd, int i)
{
	arg->child[i] = fork();
	if (arg->child[i] < 0)
		perror("Fork");
	if (arg->child[i] == 0)
	{
		if (cmd->input_file == -1 || cmd->output_file == -1)
			exit(1);
		if (cmd->limiter != NULL)
			ft_here_doc(arg, cmd);
		else if (cmd->input_file > 2)
			dup2(cmd->input_file, STDIN_FILENO);
		else if (i > 0)
			dup2(arg->fd[i][0], STDIN_FILENO);
		if (cmd->output_file > 2)
			dup2(cmd->output_file, STDOUT_FILENO);
		else if (i < arg->nbr_cmd - 1)
			dup2(arg->fd[i + 1][1], STDOUT_FILENO);
		if (arg->nbr_cmd > 1)
			close_everything(arg, i);
		exit(exec_bash(arg, cmd));
	}
	if (cmd->limiter != NULL)
		waitpid(arg->child[i], &arg->etat, 0);
	return (0);
}

int	exec_bash(t_minishell *arg, t_command *cmd)
{
	if (exec_built_in(arg, cmd) == 0)
		return (0);
	else
		exit(access_path(arg, cmd));
	exit (-1);
}

int	exec_built_in(t_minishell *arg, t_command *cmd)
{
	if (!cmd)
		return (9);
	if (ft_strncmpmaj(cmd->name, "pwd", -1) == 0)
		return (ft_pwd());
	if (ft_strncmpmaj(cmd->name, "echo", -1) == 0)
		return (ft_echo(cmd));
	if (ft_strncmp(cmd->name, "cd", -1) == 0)
		return (ft_cd(cmd->value[1], arg));
	if (ft_strncmp(cmd->name, "export", -1) == 0)
		return (ft_export(cmd->value, arg->env, arg));
	if (ft_strncmp(cmd->name, "unset", -1) == 0)
		return (ft_unset(cmd->value[1], arg->env));
	if (ft_strncmpmaj(cmd->name, "env", -1) == 0)
		return (ft_env(arg->env));
	if (ft_strncmp(cmd->name, "exit", -1) == 0)
	{
		if (arg->nbr_cmd == 1)
			printf("exit\n");
		return (ft_exit(arg, cmd));
	}
	if (ft_strncmp(cmd->name, "new", -1) == 0)
		return (rl_on_new_line());
	return (1);
}
