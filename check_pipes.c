/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simoberri <simoberri@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 18:37:14 by mberri            #+#    #+#             */
/*   Updated: 2023/03/05 20:36:56 by simoberri        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// condition in check_pipes function forget why i use it
/*else if (line[i] == '|' && j > 0 && (!(db % 2) || !(s % 2))
			&& line[i + 1] == '\0')
			command++;*/
static int check_pipe_in_begin(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		while (is_white_space(line[i]))
			i++;
		if (line[i] == '|')
			return (0);
		return (1);
	}
	return (0);
}

static void quotes_counter(char c, int *db, int *s)
{
	if (c == '"')
		(*db)++;
	if (c == '\'')
		(*s)++;
}

int number_of_pipes(char *line)
{
	int i;
	int db;
	int s;
	int pipe;

	pipe = 0;
	i = 0;
	db = 0;
	s = 0;
	while (line[i])
	{
		if (line[i] == '|' && (!(db % 2) && !(s % 2)))
			pipe++;
		quotes_counter(line[i], &db, &s);
		i++;
	}
	return (pipe);
}

int check_pipes(char *line)
{
	int i;
	int command;
	int db;
	int s;
	int j;

	init_var(&command, &db, &s, &j);
	if (!check_pipe_in_begin(line))
		return (print_error("syntax error near unexpected token '|' \n"));
	i = -1;
	while (line[++i])
	{
		quotes_counter(line[i], &db, &s);
		while (line[i] && !(is_white_space(line[i])) && line[i] != '|')
		{
			j = i++;
			quotes_counter(line[i], &db, &s);
		}
		if (line[i] == '|' && j > 0 && (!(db % 2) || !(s % 2)))
		{
			command++;
			j = 0;
		}
		else if (line[i + 1] == '\0' && j > 0 && (!(db % 2) || !(s % 2)))
			command++;
	}
	if (command <= number_of_pipes(line) && command != 0)
		return (print_error("syntax error near unexpected token '|' \n"));
	return (1);
}
