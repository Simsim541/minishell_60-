/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_dollar_qts.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaammari <aaammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 14:31:11 by aaammari          #+#    #+#             */
/*   Updated: 2023/02/18 18:07:23 by aaammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	nbr_of_char(char *str, int *d, int *s, int i)
{
	if (str[i] == '\'' && (*d % 2 == 0))
		*s += 1;
	if (str[i] == '"' && (*s % 2 == 0))
		*d += 1;
}

int	fill_cmd(char *cmd, int status)
{
	char	*tmp;
	size_t	j;

	tmp = NULL;
	j = 0;
	tmp = ft_itoa(status);
	while (j < ft_strlen(tmp))
	{
		cmd[j] = tmp[j];
		j++;
	}
	free(tmp);
	return (j);
}

void	fill_cmd2(char *cmd, int *j, int status, int dollar)
{
	while (dollar > 0)
	{
		*j += fill_cmd(cmd + *j, status);
		dollar -= 2;
	}
}

int	check_dollar(char *str, int *i, int status, char *cmd)
{
	int		dollar;
	int		j;

	j = 0;
	dollar = 0;
	while (str[*i] == '$')
	{
		*i += 1;
		dollar++;
	}
	if (dollar % 2 == 0 && dollar != 0)
		fill_cmd2(cmd, &j, status, dollar);
	else if (dollar % 2 != 0 && dollar != 0)
	{
		dollar--;
		fill_cmd2(cmd, &j, status, dollar);
		if (*i != 0)
			*i -= 1;
	}
	return (j);
}
