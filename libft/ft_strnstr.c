/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaammari <aaammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 10:41:43 by aaammari          #+#    #+#             */
/*   Updated: 2021/11/11 12:54:06 by aaammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	nl;
	char	*hay;

	hay = (char *)haystack;
	nl = ft_strlen(needle);
	if (*needle == '\0' || haystack == needle)
		return (hay);
	i = 0;
	while (hay[i] && i < len)
	{
		j = 0;
		while (needle[j] && hay[i + j] && i + j < len
			&& hay[i + j] == needle[j])
			j++;
		if (j == nl)
			return (hay + i);
		i++;
	}
	return (0);
}
