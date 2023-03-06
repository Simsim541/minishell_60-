/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaammari <aaammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 15:12:31 by aaammari          #+#    #+#             */
/*   Updated: 2021/11/21 20:55:21 by aaammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include<stdio.h>
#include"libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		r;

	r = ft_strlen(s);
	while (r >= 0)
	{
		if (s[r] == (char)c)
			return ((char *)(s + r));
		r--;
	}
	return (0);
}
