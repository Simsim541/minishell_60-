/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaammari <aaammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 12:01:56 by aaammari          #+#    #+#             */
/*   Updated: 2021/11/21 20:37:08 by aaammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*pmlc;

	pmlc = malloc(count * size);
	if (!pmlc)
		return (NULL);
	ft_bzero(pmlc, count * size);
	return (pmlc);
}
