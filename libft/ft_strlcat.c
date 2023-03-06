/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaammari <aaammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 13:01:20 by aaammari          #+#    #+#             */
/*   Updated: 2021/11/21 11:35:59 by aaammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t dstsize)
{
	size_t	lendest;
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	j = 0;
	lendest = ft_strlen(dest);
	if (lendest >= dstsize)
		return (ft_strlen(src) + dstsize);
	else
	{
		while (dest[i])
			i++;
		len = (ft_strlen(dest) + ft_strlen(src));
		while (src[j] != '\0' && (i < dstsize - 1))
		{
			dest[i] = src[j];
			j++;
			i++;
		}
		dest[i] = '\0';
	}
	return (len);
}

/*int main()
{
    char t[50] = "hello 1337";
    char t1[] = "hhhh";
    size_t tt = ft_strlcat(t,t1,13);
    printf("%ld\n",tt);
    printf("%s",t);
}*/
