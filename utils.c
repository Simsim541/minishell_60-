/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberri <mberri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 14:31:11 by aaammari          #+#    #+#             */
/*   Updated: 2023/03/06 18:53:40 by mberri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_white_space(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	print_error(char *str)
{
	ft_putstr_fd(str, 2);
	return (0);
}

int	is_option(char *line)
{
	int	i;
	int	size;

	size = ft_strlen(line);
	if (line[0] == '-' && size <= 3)
		return (1);
	return (0);
}

int	there_is_a_redirection(char *str)
{
	int	db;
	int	s;
	int	i;

	i = 0;
	db = 0;
	s = 0;
	while (str[i])
	{
		quotes_counter(str[i], &db, &s);
		if ((str[i] == '>' || str[i] == '<') && (!(db % 2) && !(s % 2)))
			return (1);
        i++;
	}
	return (0);
}
/*int	nbr_of_char(char *str, char c, int n, int ds)
{
	int	i;
	int	nbr;

	nbr = 0;
	i = 0;
	while (str[i] && i < n && ds % 2 == 0)
	{
		if (str[i] == c)
			nbr++;
		i++;
	}
	if (nbr % 2 == 0)
		return (0);
	return (nbr);
}*/
