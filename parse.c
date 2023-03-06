/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simoberri <simoberri@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 17:59:49 by mberri            #+#    #+#             */
/*   Updated: 2023/03/06 10:49:48 by simoberri        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void quotes_counter(char c, init *db, int *s)
{
    if (c == '"')
        (*db)++;
    if (c == '\'')
        (*s)++;
}

static int  there_is_a_redirection(char *str)
{
    int db;
    int s;
    int i;

    i = 0;
    db = 0;
    s = 0;
    while (str[i])
    {
        quotes_counter(str[i], &db, &s);
        if (str[i] == '>' || str[i] == '<' && (!(db%2) && !(s%2)))
            return (1);
        i++;
    }
    return(0);  
}

static int is_option(char *line)
{
    int i;
    int size;

    size = ft_strlen(line);
    if (line[0] == '-' && size <= 3)
            return(1);
    return (0);
}

void    normal_parsing(t_cmd *cmd, char *line)
{
    char    *command;
    int     i;

    i = 0;
    command = ft_split(line, ' ');
    cmd->command = command[i];
    i++;
    while (command[i])
    {
        if (is_option(command[i]))
            ft_strdup(cmd->option, command[i]);
        else
            ft_strjoin(cmd->argument, command[i]);
    }
}

void    parsing_with_redirection(t_cmd  *cmd, char  *line)
{
    
}
void    init_command(t_cmd  *cmd, char **args)
{
    int i;
    t_cmd   *begin;

    i = 0;
    begin = cmd;
    while (args[i])
    {
        if(there_is_a_redirection(args[i]))
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