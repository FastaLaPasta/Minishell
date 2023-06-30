/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_verif_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiampor <jgiampor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 10:23:38 by sboulogn          #+#    #+#             */
/*   Updated: 2023/06/16 15:49:22 by jgiampor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int	handle_quotes(int *i, char *str)
{
	char	quotes;

	if (str[*i] == '\'' || str[*i] == '"')
	{
		quotes = str[*i];
		(*i)++;
		while (str[*i] != quotes)
		{
			if (str[*i] == '\0')
				return (258);
			(*i)++;
		}
	}
	return (0);
}

int	handle_chevron(int *i, char *str)
{
	if (str[(*i) + 1] != '\0' && str[(*i) + 1] == str[*i]
		&& str[(*i) + 2] == str[*i])
		return (258);
	if (str[(*i) + 1] != '\0' && str[*i + 1] == str[*i])
	{
		(*i) += 2;
		if (str[*i] == '|')
			return (258);
	}
	if (str[*i] == '<' && str[(*i) + 1] == '|')
		return (258);
	else
		(*i)++;
	while (str[*i] && str[*i] != '<' && str[*i] != '>' && str[*i] != '|')
	{
		if (ft_isalnum(str[*i]) == 1 || str[*i] == '"' || str[*i] == '\'')
		{
			handle_quotes(i, str);
			break ;
		}
		(*i)++;
		if (str[*i] == '<' || str[*i] == '>' || str[*i] == '|')
			return (258);
	}
	return (0);
}

int	handle_pipe(int *i, char *str)
{
	if (str[(*i) + 1] != '\0' && str[(*i) + 1] == str[*i])
		return (258);
	(*i)++;
	while (str[*i] != '\0' && str[*i] != '|')
	{
		if (ft_isalnum(str[*i]) == 1 || str[*i] == '$')
			break ;
		(*i)++;
		if (str[*i] == '\0' || str[*i] == '|')
		{
			if (str[*i] == '|' && str[(*i) - 1] == '>' && str[(*i) - 2]
				!= '>' && str[(*i) - 2] != '<')
				break ;
			return (258);
		}
	}
	return (0);
}

int	handle_start_end_str(int *i, char *str)
{
	while (str[*i] == ' ' || str[*i] == '\t' || str[*i] == '\n')
	{
		if (str[*i] == '|' || str[ft_strlen(str) - 1] == '|'
			|| str[ft_strlen(str) - 1] == '<' || str[ft_strlen(str) - 1] == '>')
			return (258);
		(*i)++;
	}
	return (0);
}

int	verif_syntax(char *str)
{
	int	i;

	i = 0;
	if (handle_start_end_str(&i, str) == 258)
		return (258);
	while (str[i])
	{
		if (handle_quotes(&i, str) == 258)
			return (258);
		else if (str[i] == '>' || str[i] == '<')
		{
			if (handle_chevron(&i, str) == 258)
				return (258);
		}
		if (str[i] == '|')
		{
			if (handle_pipe(&i, str) == 258)
				return (258);
		}
		else if (str[i] != '\0')
			i++;
	}
	return (0);
}
