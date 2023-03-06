/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberri <mberri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 14:17:51 by aaammari          #+#    #+#             */
/*   Updated: 2023/02/24 16:56:35 by mberri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Function: check if there are  double quotes in the string
int	double_quotes(char *str, int i, int *db, int sg)
{
	i++;
	if (sg % 2 == 0)
		(*db)++;
	while (str[i])
	{
		if (str[i] == '"')
		{
			(*db)++;
			return (i);
		}	
		i++;
	}
	return (i);
}

// Function: check if there are single quotes in the string
int	single_quotes(char *str, int i, int *single, int db)
{
	i++;
	if (db % 2 == 0)
		(*single)++;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			(*single)++;
			return (i);
		}
		i++;
	}
	return (i);
}

// Function: check if there are quotes in the string and if they are closed
int	check_quotes(char *str)
{
	int	i;
	int	db;
	int	single;
	int	len;

	len = ft_strlen(str);
	i = -1;
	db = 0;
	single = 0;
	if (!str)
		return (0);
	while (str[++i] && i < len)
	{
		if (str[i] == '"')
			i = double_quotes(str, i, &db, single);
		if (str[i] == '\'')
			i = single_quotes(str, i, &single, db);
	}
	if (db % 2)
		ft_putstr_fd("Error: Double quotes not closed\n", 2);
	if (single % 2)
		ft_putstr_fd("Error: Single quotes not closed\n", 2);
	if (db % 2 || single % 2)
		return (0);
	return (1);
}
