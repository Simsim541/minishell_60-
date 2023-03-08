/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberri <mberri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 09:57:56 by aaammari          #+#    #+#             */
/*   Updated: 2023/03/08 17:26:46 by mberri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*init_cmd(void)
{
	t_cmd	*new_mem;

	new_mem = malloc(sizeof(t_cmd));
	new_mem->cmd = NULL;
	new_mem->argument = NULL;
	new_mem->next = NULL;
	new_mem->redirect = init_redirecttion();
	return (new_mem);
}

t_redirection	*init_redirecttion(void)
{
	t_redirection	*new_mem;

	new_mem = malloc(sizeof(t_redirection));
	new_mem->index = 0;
	new_mem->file_name = NULL;
	new_mem->next = NULL;
	return (new_mem);
}

static int	white_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] > 32 && str[i] < 127)
			return (0);
		i++;
	}
	return (1);
}
/*
echo -n "hello"
   ls  -al>>A >>B>> C>>D
ls >> Z>> X -al>> E
*/

int	check_syntax_init(char *line)
{
	if (!check_quotes(line))
		return (0);
	if (!check_pipes(line))
		return (0);
	if (!check_redirect(line))
		return (0);
	return (1);
}

int	main(int ac, char **av, char **env)
{
	char	*line;
	char	**args;
	t_cmd	*command;
	int		i;

	(void)ac;
	(void)av;
	(void)env;
	while (1)
	{
		line = readline("minishell$> ");
		if (!line)
			break ;
		add_history(line);
		if (line && !(white_space(line)) && check_syntax_init(line))
		{
			args = ft_split(line, '|');
			command = init_command(args);
			printf("OKAY   here before while loop is Okay\n");
			while (command)
			{
				i = 0;
				printf("command is :%s\n", command->cmd);
				if (command->argument != NULL)
				{
					while (command->argument[i])
					{	
						printf("argument %d is : %s\n", i + 1, command->argument[i]);
						i++;
					}
				}
				if (command->redirect->file_name)
				{
					while (command->redirect)
					{
						printf("file_name is : %s\n", command->redirect->file_name);
						printf("type is %d\n", command->redirect->type);
						command->redirect = command->redirect->next;
					}
				}
				command = command->next;
			}
		}
	free(command);
	}
	return (0);
}
