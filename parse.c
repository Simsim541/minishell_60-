/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberri <mberri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 17:59:49 by mberri            #+#    #+#             */
/*   Updated: 2023/03/08 20:36:04 by mberri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	quotes_counter(char c, int *db, int *s)
{
	if (c == '"')
		(*db)++;
	if (c == '\'')
		(*s)++;
}

static int	count_argument(char *line)
{
	int		i;
	int		db;
	int		s;
	int		count;
	int		j;

	i = 0;
	db = 0;
	j = 0;
	s = 0;
	count = 0;
	while (is_white_space(line[i]))
		i++;
	while (!is_white_space(line[i]) && (line[i] != '<' && line[i] != '>')
		&& (!(db % 2) && !(s % 2)))
	{
		quotes_counter(line[i], &db, &s);
		i++;
	}
	while (line[i])
	{
		quotes_counter(line[i], &db, &s);
		while (is_white_space(line[i]))
		{
			i++;
			j = 0;
		}
		while (!is_white_space(line[i]) && (line[i] != '<' && line[i] != '>')
			&& (!(db % 2) && !(s % 2)) && !j)
		{
			quotes_counter(line[i], &db, &s);
			i++;
		}
		while (line[i] == '>' || line[i] == '<' && (!(db % 2) && !(s % 2)))
			j = i++;
		if (j)
		{
			while (!is_white_space(line[i])
				&& (line[i] != '<' && line[i] != '>')
				&& (!(db % 2) && !(s % 2)))
			{
				quotes_counter(line[i], &db, &s);
					i++;
			}
		}
		if (!j)
			count++;
	}
	return (count);
}

void	normal_parsing(t_cmd *cmd, char *line)
{
	char	**command;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 1;
	command = ft_split(line, ' ');
	while (command[k])
		k++;
	if (k > 1)
	{
		cmd->argument = malloc(sizeof(char *) * k + 1);
		cmd->argument[k] = NULL;
	}
	cmd->cmd = ft_strdup(command[i]);
	i++;
	while (command[i])
	{
		printf("(insid LOOP) command is  %s\n", cmd->cmd);
		if (k > 1)
		{
			cmd->argument[j] = ft_strdup(command[i]);
			printf ("(inside LOOP) argument is : %s\n", cmd->argument[j]);
			j++;
		}
		i++;
	}
	j = 0;
	while (command[j])
	{
		free(command[j]);
		j++;
	}
	free(command);
	printf("command is %s\n", cmd->cmd);
	if (cmd->argument != NULL)
	{
		j = 0;
		while (cmd->argument[j])
		{
			printf("argument is %s\n", cmd->argument[j]);
			j++;
		}
	}
}

void	fill_redirection(t_redirection *redirect, char *line, int *i)
{
	int	db;
	int	s;

	db = 0;
	s = 0;
	//printf("here in fill redirection\n");
	if (line[*i] == '>' && line[(*i) + 1] == '>')
		redirect->type = RED_DOUBLE_OUT;
	else if (line[*i] == '<' && line[(*i) + 1] == '<')
		redirect->type = RED_DOUBLE_INP;
	else if (line[*i] == '<' && line[(*i) + 1] == '>')
		redirect->type = RED_INP;
	else if (line[*i] == '>' && (line[(*i) + 1] != '>'
			&& line[(*i) + 1] != '<'))
		redirect->type = RED_OUT;
	else if (line[*i] == '<' && (line[(*i) + 1] != '>'
			&& line[(*i) + 1] != '<'))
		redirect->type = RED_INP;
	while (line[*i] == '>' || line[*i] == '<')
		(*i)++;
	while (is_white_space(line[*i]))
		(*i)++;
	redirect->index = *i;
	while (line[*i] && !(is_white_space(line[*i]))
		&& (line[*i] != '>' && line[*i] != '<')
		&& (!(db % 2) && !(s % 2)))
	{
		quotes_counter(line[*i], &db, &s);
		(*i)++;
	}
	redirect->file_name = ft_substr(line, redirect->index, (*i) - redirect->index);
	redirect->next = init_redirecttion();
	redirect = redirect->next;
	//printf("everything okay !\n");
}

void	parsing_with_redirection(t_cmd *cmd, char *line)
{
	t_redirection	*begin_red;
	int				i;
	int				start;
	int				db;
	int				s;
	int				j;

	begin_red = cmd->redirect;
	j = 0;
	init_var(&i, &start, &db, &s);
	while (is_white_space(line[i]))
		i++;
	start = i;
	while (line[i])
	{
		quotes_counter(line[i], &db, &s);
		if (((!(db % 2) && !(s % 2))) && ((line[i] == '<' || line[i] == '>')
				|| (is_white_space(line[i]))))
			break ;
		i++;
	}
	cmd->cmd = ft_substr(line, start, i - start);
	while (line[i])
	{
		quotes_counter(line[i], &db, &s);
		while (is_white_space(line[i]) && (!(db % 2) && !(s % 2)))
			i++;
		if ((line[i] == '>' || line[i] == '<')
			&& (!(db % 2) && !(s % 2)))
			fill_redirection(cmd->redirect, line, &i);
		//printf("index of i is:   %d\n", i);
		if (line[i])
		{
			start = i;
			while ((line[i] != '>' && line[i] != '<')
				&& (!is_white_space(line[i])) && (!(db % 2) && !(s % 2)))
			{
				i++;
				quotes_counter(line[i], &db, &s);
			}
			cmd->argument[j] = ft_substr(line, start, i - start);
		}
		//printf("OK HERE ??\n");
		while (is_white_space(line[i]))
			i++;
	}
	cmd->redirect = begin_red;
	//printf("%s\n", begin_red->file_name);
	//printf("%s\n", cmd->redirect->file_name);
	while (cmd->redirect)
	{
		cmd->redirect = cmd->redirect->next;
	}
}

t_cmd	*init_command(char **args)
{
	t_cmd	*begin;
	t_cmd	*cmd;
	int		i;

	i = 0;
	cmd = init_cmd();
	begin = cmd;
	while (args[i])
	{
		if (there_is_a_redirection(args[i]))
			parsing_with_redirection(cmd, args[i]);
		else
			normal_parsing(cmd, args[i]);
		if (args[i + 1])
		{
			cmd->next = init_cmd();
			cmd = cmd->next;
		}
		i++;
	}
	cmd = begin;
	return (cmd);
}

/*void parse(t_cmd *cmd, char **commands)
{
    int i;
    int j;
    int start;
    t_cmd   *temp;

    i = 0;
    j = 0;
    temp = cmd;
    while (commands[i])
    {
        j = 0;
        start = 0;
        while (commands[i][j])
        {
            while (is_white_space(commands[i][j]))
                j++;
            if (!commands[i][j])
                break;
            start = j;
            while (commands[i][j] && !is_white_space(commands[i][j]))
                    j++;
            cmd->command = ft_substr(commands[i], start, j - start);
            while (commands[i][j] && is_white_space(commands[i][j]))
                j++;
            if (commands[i][j])
                cmd->argumet = ft_substr(commands[i], j, ft_strlen(commands[i]) - j);
            if (commands[i + 1])
            {
                cmd->next = init_cmd();
                cmd = cmd->next;
            }
            j = ft_strlen(commands[i]);
        }
        i++;
    }
    cmd = temp;
}*/
