/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaammari <aaammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 12:07:51 by aaammari          #+#    #+#             */
/*   Updated: 2021/11/21 20:39:48 by aaammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<string.h>

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	int	i;

	if (!dest && !src)
		return (NULL);
	i = 0;
	if (((char *)dest) > ((char *)src))
	{
		while ((int)--len >= 0)
		{
			*((char *)dest + (int)len) = *((char *)src + (int)len);
		}
	}
	else
	{
		while (i < (int)len)
		{
			*((char *)dest + i) = *((char *)src + i);
			i++;
		}
	}
	return (dest);
}
