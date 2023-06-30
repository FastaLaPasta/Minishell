/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_analize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiampor <jgiampor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 12:45:52 by sboulogn          #+#    #+#             */
/*   Updated: 2023/06/16 11:25:23 by jgiampor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	copie_first_word(int *i, int *d, char *str, char *file)
{
	char	quotes;

	while (ft_skip(str[*i]) == 1)
	{
		if (str[*i] == '\'' || str[*i] == '"')
		{
			quotes = str[*i];
			file[(*d)++] = str[(*i)++];
			while (str[*i] != quotes && str[*i] != '\0')
				file[(*d)++] = str[(*i)++];
			file[(*d)++] = str[(*i)++];
		}
		if (ft_skip(str[*i]) == 1)
			file[(*d)++] = str[(*i)++];
	}
}

char	*ft_first_word(char	*str)
{
	int		i;
	int		d;
	char	*file;

	i = 1;
	d = 0;
	file = ft_calloc((ft_strlenfw1(str + i) + 1), sizeof(char));
	if (!file)
		return (NULL);
	while (((str[i] >= 9 && str[i] <= 13) || str[i] == 32
			|| str[i] == '|') && str[i] != '\0' )
		i++;
	if (str[i] != '\0')
		copie_first_word(&i, &d, str, file);
	file[d] = '\0';
	return (file);
}

int	handle_left_chevron(int	*i, char *cmd, t_command *chaine)
{
	char	*file;

	if (cmd[(*i) + 1] == cmd [*i])
	{
		(*i)++;
		if (cmd[(*i) + 1] == cmd[*i])
			return (-1);
		file = ft_first_word(cmd + (*i));
		chaine->output_file = ft_opensimple(file, 2);
		if (chaine->output_file == -1)
			return (-1);
	}
	else
	{
		file = ft_first_word(cmd + (*i));
		chaine->output_file = ft_opensimple(file, 1);
		if (chaine->output_file == -1)
			return (-1);
	}
	return (0);
}

int	handle_right_chevron(int *i, char *cmd, t_command *chaine)
{
	char	*file;

	if (cmd[(*i) + 1] == cmd [*i])
	{
		(*i)++;
		if (cmd[(*i) + 1] == cmd[*i])
			return (-1);
		if (chaine->limiter != NULL)
		{
			ft_fake_heredoc(chaine);
			free (chaine->limiter);
		}
		chaine->limiter = ft_first_word(cmd + (*i));
	}
	else
	{
		file = ft_first_word(cmd + (*i));
		chaine->input_file = ft_opensimple(file, 3);
		if (chaine->input_file == -1)
			return (-1);
	}
	return (0);
}

int	ft_analize(char	*cmd, t_command *chaine)
{
	int	i;

	i = 0;
	if (cmd == NULL)
		return (-1);
	while (cmd[i])
	{
		handle_quotes(&i, cmd);
		if (cmd[i] == '>')
		{
			if (handle_left_chevron(&i, cmd, chaine) == -1)
				return (0);
		}
		if (cmd[i] == '<')
		{
			if (handle_right_chevron(&i, cmd, chaine) == -1)
				return (0);
		}
		if (cmd[i] != '\0')
			i++;
	}
	return (0);
}
