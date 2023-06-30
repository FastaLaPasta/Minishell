/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiampor <jgiampor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 13:01:15 by sboulogn          #+#    #+#             */
/*   Updated: 2023/06/22 16:00:02 by jgiampor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

extern char	**environ;

void	ft_exec_multip(t_minishell *arg)
{
	int		i;

	i = 0;
	while (i < arg->nbr_cmd)
	{
		if (pipe(arg->fd[i]) == -1)
			exit (127);
		i++;
	}
	i = 0;
	while (i < arg->nbr_cmd)
	{
		exec(arg, arg->cmd, i);
		if (arg->cmd && arg->cmd->next != NULL)
			arg->cmd = arg->cmd->next;
		i++;
	}
	close_everything(arg, arg->nbr_cmd);
	i = 0;
	while (i < arg->nbr_cmd)
	{
		waitpid(arg->child[i], &arg->etat, 0);
		i++;
	}
}

void	handle_signal(int signal)
{
	int	id;

	id = waitpid(-1, NULL, WNOHANG);
	if (signal == SIGINT)
	{
		if (id < 0)
		{
			printf("\n");
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
		else if (signal == SIGINT && id >= 0)
		{
			rl_on_new_line();
			rl_replace_line("", 0);
		}
	}
	if (signal == SIGQUIT)
		return ;
}

void	ft_signal(void)
{
	struct sigaction	sa;

	sa.sa_handler = &handle_signal;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	rl_catch_signals = 0;
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGINT, &sa, NULL);
}

void	ft_syntax(t_minishell *arg)
{
	t_command			*tmp;

	tmp = arg->cmd;
	if (verif_syntax(arg->input) != 258)
	{
		if (fill_struct(arg, environ) == 0)
		{
			tmp = arg->cmd;
			ft_mallocpip(arg);
			if (arg->nbr_cmd == 1 && choise(arg, arg->cmd) == 0)
				waitpid(-1, &arg->etat, 0);
			else
				ft_exec_multip(arg);
		}
		arg->cmd = tmp;
		ft_structfree(arg);
	}
	else
		printf("Minishell: syntax error\n");
}

int	main(void)
{
	t_minishell			arg;
	struct termios		ok;

	tcgetattr(STDIN_FILENO, &ok);
	ft_signal();
	arg.etat = 0;
	while (1)
	{
		tcsetattr(STDIN_FILENO, TCSANOW, &ok);
		arg.input = readline("minishell-1.0$ ");
		if (!arg.input)
		{
			printf("\r\e[1A");
			printf("minishell-1.0$ exit\n");
			break ;
		}
		add_history(arg.input);
		ft_syntax(&arg);
		free(arg.input);
	}
	exit (arg.etat);
}
