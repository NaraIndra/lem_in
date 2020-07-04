/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_unuseful_rooms.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstokes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 14:10:19 by jstokes           #+#    #+#             */
/*   Updated: 2019/10/14 14:10:20 by jstokes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void	delete_link(t_cont *cont, void *name)
{
	t_list	*tmp;

	if (!cont || !name)
		return ;
	tmp = NULL;
	lst_move_from_to(&(cont->list), &tmp, name);
	lst_del(&tmp);
}

void	delete_room(void *key, t_cont *key_cont, t_lemin *lemin)
{
	t_list	*tmp;
	t_list	*next;

	tmp = (key_cont)->list;
	while (tmp)
	{
		next = tmp->next;
		delete_link(hm_find(lemin->map, tmp->content), key);
		delete_link(key_cont, tmp->content);
		tmp = next;
	}
}

void	delete_unuseful_rooms(t_lemin *lemin)
{
	t_list	*tmp;
	t_list	*next;
	t_cont	*cont;

	tmp = lemin->list;
	while (tmp)
	{
		cont = hm_find(lemin->map, tmp->content);
		if (cont && cont->bfs_lev < 0)
		{
			delete_room(tmp->content, cont, lemin);
			next = tmp->next;
			lst_move_from_to(&(lemin->list),
					&(lemin->deleted_rooms), tmp->content);
			tmp = next;
		}
		else
			tmp = tmp->next;
	}
}
