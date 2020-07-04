/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstokes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 14:55:38 by jstokes           #+#    #+#             */
/*   Updated: 2018/12/14 20:58:50 by jstokes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void	ft_lstaddend(t_list **alst, t_list *new)
{
	t_list	*pred;
	t_list	*tmp;

	if (alst && !(*alst) && new)
		*alst = new;
	else if (alst && *alst && new && !((*alst)->next))
		(*alst)->next = new;
	else if (alst && *alst && new)
	{
		pred = *alst;
		tmp = pred->next;
		while (tmp)
		{
			pred = tmp;
			tmp = tmp->next;
		}
		pred->next = new;
	}
}
