/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberri <mberri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 09:57:56 by aaammari          #+#    #+#             */
/*   Updated: 2023/03/06 18:54:10 by mberri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*init_cmd(void)
{
	t_cmd	*new_mem;

	new_mem = malloc(sizeof(t_cmd));
	new_mem->cmd = NULL;
	new_mem->argument = NULL;
	new_mem->option = NULL;
	new_mem->next = NULL;
	new_mem->redirect = malloc(sizeof(t_redirection));
	new_mem->redirect->is_output_red = 0;
	new_mem->redirect->is_two_output_red = 0;
	new_mem->redirect->is_input_red = 0;
	new_mem->redirect->is_two_input_red = 0;
	new_mem->redirect->next = NULL;
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
ls -al>>A >>B>> C>>D
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

	command = init_cmd();
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
			printf("ok\n");	
			line = expand_env(line, env);
			printf("Line is : %s\n", line);
		}
	}
	args = ft_split(line, '|');
	init_command(command, args);
	/*while (args[i])
	{
		printf("args : %s\n", args[i]);
		i++;
	}*/
	return (0);
}