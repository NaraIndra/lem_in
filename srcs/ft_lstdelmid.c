/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelmid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstygg <mstygg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 14:09:43 by jstokes           #+#    #+#             */
/*   Updated: 2019/10/13 17:54:25 by mstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void	relink(t_list *prev, t_list **tmp)
{
	if (!prev || !*tmp || prev->next != *tmp)
		return ;
	prev->next = (*tmp)->next;
	(*tmp)->next = NULL;
	ft_lstdelstr(tmp);
}

void	ft_lstdelmid(t_list **lst, t_list **targ)
{
	t_list	*tmp;

	tmp = *lst;
	if (!lst || !(*lst) || !*targ)
		return ;
	if (tmp == *targ)
	{
		*lst = tmp->next;
		tmp->next = NULL;
		ft_lstdelstr(targ);
		return ;
	}
	else
		while (tmp && tmp->next != *targ)
			tmp = tmp->next;
	if (!tmp)
		return ;
	relink(tmp, targ);
}
