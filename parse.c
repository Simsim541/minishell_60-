/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberri <mberri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 17:59:49 by mberri            #+#    #+#             */
/*   Updated: 2023/03/07 16:56:43 by mberri           ###   ########.fr       */
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

void	normal_parsing(t_cmd *cmd, char *line)
{
	char	**command;
	int		i;
	int		j;

	i = 0;
	j = 0;
	command = ft_split(line, ' ');
	cmd->cmd = command[i];
	i++;
	while (command[i])
	{
		if (is_option(command[i]))
		{
			cmd->option = ft_strjoin(cmd->option, command[i]);
			printf("option is %s\n", cmd->option);
		}
		else
		{
			cmd->argument[j] = ft_strdup(command[i]);
			j++;
		}
		i++;
	}
	j = 0;
	printf("command is %s\n", cmd->cmd);
	printf("option is %s\n", cmd->option);
	while (cmd->argument[j])
	{
		printf("argument is %s\n", cmd->argument[j]);
		j++;
	}
}

void	fill_redirection(t_cmd *cmd, char *line, int *i)
{
	int	start;

	start = 0;
	//printf("here in fill redirection\n");
	if (line[*i] == '>' && line[(*i) + 1] == '>')
		cmd->redirect->type = RED_DOUBLE_OUT;
	else if (line[*i] == '<' && line[(*i) + 1] == '<')
		cmd->redirect->type = RED_DOUBLE_INP;
	else if (line[*i] == '<' && line[(*i) + 1] == '>')
		cmd->redirect->type = RED_INP;
	else if (line[*i] == '>' && (line[(*i) + 1] != '>'
			&& line[(*i) + 1] != '<'))
		cmd->redirect->type = RED_OUT;
	else if (line[*i] == '<' && (line[(*i) + 1] != '>'
			&& line[(*i) + 1] != '<'))
		cmd->redirect->type = RED_INP;
	while (line[*i] == '>' || line[*i] == '<')
		(*i)++;
	while (is_white_space(line[*i]))
		(*i)++;
	start = *i;
	while (line[*i] && !(is_white_space(line[*i])))
		(*i)++;
	cmd->redirect->file_name = ft_substr(line, start, (*i) - start);
	cmd->redirect->next = init_redirecttion();
	cmd->redirect = cmd->redirect->next;
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
		while (is_white_space(line[i]))
			i++;
		if ((line[i] == '>' || line[i] == '<')
			&& (!(db % 2) && !(s % 2)))
			fill_redirection(cmd, line, &i);
		//printf("index of i is:   %d\n", i);
		if (line[i] && line[i] == '-' && (!(db % 2) && !(s % 2)))
		{
			quotes_counter(line[i], &db, &s);
			start = i;
			while (((!(db % 2) && !(s % 2)))
				&& ((line[i] != '>' && line[i] != '<')
					|| (!is_white_space(line[i]))))
				i++;
			cmd->option = ft_substr(line, start, i - start);
		}
		//printf("OK HERE ??\n");
		while (is_white_space(line[i]))
			i++;
		if (line[i])
		{
			start = i;
			while ((((!(db % 2) && !(s % 2)))
					&& ((line[i] != '>' && line[i] != '<')
						&& (!is_white_space(line[i])))))
			{
				quotes_counter(line[i], &db, &s);
				i++;
			}
			cmd->argument[j] = ft_substr(line, start, i - start);
			j++;
		}
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
		//printf("here Okay 2\n");
		if (args[i + 1])
		{
			cmd->next = init_cmd();
			cmd = cmd->next;
		}
		//printf("here Okay  3\n");
		i++;
	}
	//printf("here Okay ??\n");
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
