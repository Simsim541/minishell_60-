/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberri <mberri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 09:46:34 by aaammari          #+#    #+#             */
/*   Updated: 2023/02/24 12:15:23 by mberri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"
#include <stdio.h>

static int	ft_count_word(char const *tosplit, char delim)
{
	int	lenstr;
	int	nword;
	int	s;
	int	d;

	lenstr = 0;
	nword = 0;
	s = 0;
	d = 0;
	while (tosplit[lenstr])
	{
		if (tosplit[lenstr] == '\'' && (d % 2 == 0))
			s++;
		if (tosplit[lenstr] == '"' && (s % 2 == 0))
			d++;
		if (tosplit[lenstr] != delim && (s % 2 == 0) && (d % 2 == 0)
			&& (tosplit[lenstr + 1] == delim || tosplit[lenstr + 1] == '\0'))
			nword++;
		lenstr++;
	}
	return (nword);
}

static char	**free_alloc(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (NULL);
}

int	ft_sqeep_sp(const char *s, char c, int *single, int *d)
{
	size_t	len;

	len = 0;
	while (s[len])
	{
		if (s[len] == c && (*single % 2 == 0) && (*d % 2 == 0))
			break ;
		if (s[len] == '\'' && (*d % 2 == 0))
			(*single)++;
		if (s[len] == '"' && (*single % 2 == 0))
			*d += 1;
		len++;
	}
	return (len);
}

char	**ft_splt(char const *s, char c, char **tab)
{
	int			single;
	int			d;
	size_t		i;
	size_t		len;

	init(&single, &d, &i);
	while (*s)
	{
		while (*s && *s == c && (single % 2 == 0) && (d % 2 == 0))
			s++;
		len = 0;
		len = ft_sqeep_sp(s, c, &single, &d);
		if (len != 0)
		{
			if (*s == '\'' || *s == '"')
				tab[i++] = delete_quetes(s, len);
			else
				tab[i++] = ft_substr(s, 0, len);
		}
		if (!tab[i - 1] && len != 0)
			return (free_alloc(tab));
		s += len;
	}
	return (tab[i] = NULL, tab);
}

char	**ft_split(char const *s, char c)
{
	char		**tab;

	if (!s)
		return (0);
	tab = (char **)malloc((ft_count_word(s, c) + 1) * sizeof(char *));
	if (!tab)
		return (tab);
	return (ft_splt(s, c, tab));
}

// char	**ft_split(char const *s, char c)
// {
// 	char		**tab;
// 	size_t		i;
// 	size_t		len;
// 	int			single;
// 	int			d;

// 	i = 0;
// 	single = 0;
// 	d = 0;
// 	if (!s)
// 		return (0);
// 	tab = (char **)malloc((ft_count_word(s, c) + 1) * sizeof(char *));
// 	if (!tab)
// 		return (tab);
// 	while (*s)
// 	{
// 		len = 0;
// 		while (*s && *s == c && (single % 2 == 0) && (d % 2 == 0))
// 			s++;
// 		while (s[len])
// 		{
// 			if (s[len] == c && single % 2 == 0 && d % 2 == 0)
// 				break ;
// 			if (s[len] == '\'' && (d % 2 == 0))
// 				single++;
// 			if (s[len] == '"' && (single % 2 == 0))
// 				d++;
// 			len++;
// 		}
// 		if (len != 0)
// 		{
// 			if (*s == '\'' || *s == '"')
// 				tab[i++] = ft_strtrim(s + 1, "'\"");
// 			else
// 				tab[i++] = ft_substr(s, 0, len);
// 		}	
// 		if (!tab[i - 1] && len != 0)
// 			return (free_alloc(tab));
// 		s += len;
// 	}
// 	tab[i] = NULL;
// 	return (tab);
// }
// char	**ft_split(char const *s, char c)
// {
// 	char		**tab;
// 	size_t		i;
// 	size_t		len;
// 	int			single;
// 	int			d;

// 	i = 0;
// 	single = 0;
// 	d = 0;
// 	if (!s)
// 		return (0);
// 	tab = (char **)malloc((ft_count_word(s, c) + 1) * sizeof(char *));
// 	if (!tab)
// 		return (tab);
// 	while (*s)
// 	{
// 		len = 0;
// 		while (*s && *s == c && (single % 2 == 0) && (d % 2 == 0))
// 			s++;
// 		while (s[len])
// 		{
// 			if (s[len] == c && single % 2 == 0 && d % 2 == 0)
// 				break ;
// 			if (s[len] == '\'' && (d % 2 == 0))
// 				single++;
// 			if (s[len] == '"' && (single % 2 == 0))
// 				d++;
// 			len++;
// 		}
// 		if (len != 0)
// 		{
// 			if (*s == '\'' || *s == '"')
// 				tab[i++] = ft_strtrim(s + 1, "'\"");
// 			else
// 				tab[i++] = ft_substr(s, 0, len);
// 		}	
// 		if (!tab[i - 1] && len != 0)
// 			return (free_alloc(tab));
// 		s += len;
// 	}
// 	tab[i] = NULL;
// 	return (tab);
// }