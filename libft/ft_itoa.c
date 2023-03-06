/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaammari <aaammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 16:48:19 by aaammari          #+#    #+#             */
/*   Updated: 2021/11/21 20:39:07 by aaammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static char	*ft_rev_tab(char *tab, int size)
{
	int		i;
	char	s;

	i = 0;
	while (i < size / 2)
	{
		s = tab[i];
		tab[i] = tab[size - (i + 1)];
		tab[size - (i + 1)] = s;
		i++;
	}
	return (tab);
}

static int	ft_nlen(int n)
{
	int	i;

	i = 0;
	while (n / 10 != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static char	*ft_rem_tab(char *str, int t, int s)
{
	int	i;

	i = 0;
	while (t / 10 != 0)
	{
		str[i] = t % 10 + 48;
		t /= 10;
		i++;
	}
	str[i] = t + 48;
	if (s == 1)
	{
		str[i + 1] = '-';
		str[i + 2] = '\0';
	}
	else
		str[i + 1] = '\0';
	return (str);
}

char	*ft_itoa(int n)
{
	int		i;
	int		s;
	char	*str;

	i = 1;
	s = 0;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n < 0)
	{
		n *= -1;
		i++;
		s = 1;
	}
	i += ft_nlen(n);
	str = malloc(i * sizeof(char) + 1);
	if (!str)
		return (0);
	return (ft_rev_tab(ft_rem_tab(str, n, s), ft_strlen(str)));
}
