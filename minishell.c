/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simoberri <simoberri@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 09:57:56 by aaammari          #+#    #+#             */
/*   Updated: 2023/03/06 10:19:17 by simoberri        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*init_cmd()
{
	t_cmd	*new_mem;

	new_mem = malloc(sizeof(t_cmd));
	new_mem->command = NULL;
	new_mem->argument = NULL;
	new_mem->option = NULL;
	new_mem-> next = NULL;
	new_mem->redirect->is_output_red = 0;
	new_mem->redirect->is_two_output_red = 0;
	new_mem->redirect->is_input_red = 0;
	new_mem->redirect->is_two_input_red = 0;
	new_mem->redirect->next = NULL;	
	return (new_mem);
}

static int	white_space(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if(str[i] > 32 && str[i] < 127)
			return (0);
		i++;
	}
	return (1);
}

int	check_syntax_init(char *line)
{
	if (!check_quotes(line))
		return(0);
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
	int		i;
	t_cmd	*cmd;
	
	cmd = init_cmd();
	i = 0;
	(void)ac;
	(void)av;
	(void)env;
	while(1)
	{
		line = readline("minishell$> ");
		if(!line)
			break;
		add_history(line);
		if (line && !(white_space(line)) && check_syntax_init(line))
		{
			printf("ok\n");	
			line = expand_env(line, env);
			printf("Line is : %s\n", line);
		}
	args = ft_split(line, '|');
	init_command(cmd, args);
	/*while (args[i])
	{
		printf("args : %s\n", args[i]);
		i++;
	}
	ft_exec_pipe(args, env);*/
	return (0);
}
