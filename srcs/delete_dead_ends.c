/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_dead_ends.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstokes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 14:09:45 by jstokes           #+#    #+#             */
/*   Updated: 2019/10/14 14:09:46 by jstokes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

int		delete_dead_ends(t_lemin *lemin)
{
	int		j;
	t_list	*tmp;
	t_list	*next;
	t_cont	*cont;

	tmp = lemin->list;
	j = 0;
	while (tmp)
	{
		cont = hm_find(lemin->map, tmp->content);
		if (cont && cont->bfs_lev > 0 && cont->bfs_lev < MAX_INT &&
			ft_lstlen(cont->list) == 1)
		{
			j++;
			next = tmp->next;
			delete_room(tmp->content, cont, lemin);
			lst_move_from_to(&(lemin->list),
				&(lemin->deleted_rooms), tmp->content);
			tmp = next;
		}
		else
			tmp = tmp->next;
	}
	return (j);
}
