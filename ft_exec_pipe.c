/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaammari <aaammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 10:45:42 by aaammari          #+#    #+#             */
/*   Updated: 2023/02/22 18:57:28 by aaammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*void	pipes(char **cmds, char **env, char **cmd)
{
	int	i;
	int	fd[2];

	i = 0;
	while (cmds[i + 1])
	{
		cmd = ft_split(cmds[i], ' ');
		if (pipe(fd) == -1)
			return ;
		ft_execve(cmd, env, fd);
		ft_free(cmd);
		i++;
	}
	cmd = ft_split(cmds[i], ' ');
	ft_execve(cmd, env, fd);
	wait(NULL);
	ft_free(cmd);
}

void	ft_exec_pipe(char **cmds, char **env)
{
	char	**cmd;

	cmd = NULL;
	if (!cmds || !*cmds || !env || !*env)
		return ;
	pipes(cmds, env, cmd);
	ft_free(cmds);
}*/
