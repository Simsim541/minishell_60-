/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaammari <aaammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 11:16:40 by aaammari          #+#    #+#             */
/*   Updated: 2023/02/22 18:13:40 by aaammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

char	**env_path(char **env)
{
	int		i;
	char	**args;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (env[i])
	{
		if (ft_strncmp("PATH", env[i], ft_strlen("PATH")) == 0
			&& env[i][4] == '=')
		{
			tmp = ft_strdup(env[i] + 5);
			break ;
		}
		i++;
	}
	if (!tmp)
		return (NULL);
	args = ft_split(tmp, ':');
	free(tmp);
	return (args);
}

char	*ft_path(char **cmd, char **env)
{
	int		i;
	char	**args;
	char	*tmp;
	char	*tmp1;

	if (!cmd || !*cmd || !env || !*env)
		return (NULL);
	if (access(*cmd, X_OK) == 0)
		return (*cmd);
	args = env_path(env);
	if (!args || !*args)
		return (NULL);
	i = 0;
	while (args[i])
	{
		tmp1 = ft_strjoin(args[i], "/");
		tmp = ft_strjoin(tmp1, *cmd);
		free(tmp1);
		if (access(tmp, X_OK) == 0)
			break ;
		i++;
	}
	ft_free(args);
	return (tmp);
}

void	ft_execve(char **cmd, char **env, int fd[2])
{
	char	*path;
	int		id;

	path = ft_path(cmd, env);
	if (!path || !*path)
		return ;
	id = fork();
	if (id == -1)
		return ;
	if (id == 0)
	{
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
		execve(path, cmd, env);
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(*cmd, 2);
		ft_putstr_fd(": comand not found\n", 2);
		exit(0);
	}
	else
	{
		dup2(fd[0], 0);
		close(fd[1]);
		close(fd[0]);
	}
	free(path);
}

// void	simple_pipe(char **cmd1, char **cmd2, char **env)
// {
// 	int	fd[2];
// 	int	id1;
// 	int	id2;

// 	if (pipe(fd) == -1)
// 		return ;
// 	id1 = fork();
// 	if (id1 == -1)
// 		return ;
// 	if (id1 == 0)
// 	{
// 		dup2(fd[1], 1);
// 		close(fd[0]);
// 		ft_execve(cmd1, env);
// 		exit(0);
// 	}
// 	id2 = fork();
// 	if (id2 == -1)
// 		return ;
// 	if (id2 == 0)
// 	{
// 		dup2(fd[0], 0);
// 		close(fd[1]);
// 		ft_execve(cmd2, env);
// 		exit(0);
// 	}
// 	wait(NULL);
// 	close(fd[1]);
// 	close(fd[0]);
// }