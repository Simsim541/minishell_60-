/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaammari <aaammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 10:07:18 by aaammari          #+#    #+#             */
/*   Updated: 2023/02/19 13:53:13 by aaammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdlib.h>
#include"libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int	b;

	if (!s1)
		return (0);
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	b = ft_strlen(s1);
	while (b && ft_strchr(set, s1[b]))
		b--;
	return (ft_substr(s1, 0, b + 1));
}
