/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaammari <aaammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 18:53:40 by aaammari          #+#    #+#             */
/*   Updated: 2021/11/18 19:57:16 by aaammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*currlst;

	if (!(*lst))
		*lst = new;
	else
	{
		currlst = ft_lstlast(*lst);
		currlst->next = new;
	}
}
