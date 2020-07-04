/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelstr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstokes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 20:11:46 by jstokes           #+#    #+#             */
/*   Updated: 2019/02/25 20:13:33 by jstokes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void	ft_lstdelstr(t_list **alst)
{
	t_list	*next;

	if (alst && *alst)
	{
		next = (*alst)->next;
		if (next)
			ft_lstdelstr(&next);
		if ((*alst)->content)
			free((*alst)->content);
		(*alst)->content = NULL;
		free(*alst);
		*alst = NULL;
	}
}
