/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaammari <aaammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 10:28:07 by aaammari          #+#    #+#             */
/*   Updated: 2023/02/19 14:02:31 by aaammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdio.h"

void	init(int *single, int *d, size_t *i)
{
	*single = 0;
	*d = 0;
	*i = 0;
}

void	init_var(int *var1, int *var2, int *var3, int *var4)
{
	*var1 = 0;
	*var2 = 0;
	*var3 = 0;
	*var4 = 0;
}

char	*delete_quetes(const char *str, size_t len)
{
	while (*str && ft_strchr("\"\'", *str))
	{
		str++;
		len--;
	}
	while (len && ft_strchr("\"\'", str[len - 1]))
		len--;
	return (ft_substr(str, 0, len));
}
