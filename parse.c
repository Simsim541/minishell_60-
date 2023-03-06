/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberri <mberri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 17:59:49 by mberri            #+#    #+#             */
/*   Updated: 2023/03/06 18:52:33 by mberri           ###   ########.fr       */
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
	char	*str;

	i = 0;
	command = ft_split(line, ' ');
	cmd->cmd = command[i];
	i++;
	while (command[i])
	{
		if (is_option(command[i]))
			cmd->option = ft_strjoin(cmd->option, command[i]);
		else
		{
			ft_strjoin(str, command[i]);
			ft_strjoin(str, " ");
		}
		i++;
	}
	cmd->argument = ft_split(str, ' ');
	free(str);
}

void	parsing_with_redirection(t_cmd *cmd, char *line)
{
    int i;

    i = 0;
    while (line[i])
    {
        
    }
    
}

void	init_command(t_cmd *cmd, char **args)
{
	int		i;
	t_cmd	*begin;

	i = 0;
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
