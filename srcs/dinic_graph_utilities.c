/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinic_graph_utilities.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstygg <mstygg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 23:37:23 by mstygg            #+#    #+#             */
/*   Updated: 2019/10/22 00:14:10 by mstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void	flush_levels_visits(t_lemin *lemin)
{
	t_cont		*cont;
	t_list		*vertice_list;

	vertice_list = lemin->list;
	while (vertice_list)
	{
		cont = hm_find(lemin->map, vertice_list->content);
		cont->bfs_lev = -1;
		cont->visited = 0;
		cont->parent = NULL;
		cont->deleted_layers = NULL;
		vertice_list = vertice_list->next;
	}
	hm_find(lemin->map, lemin->start->content)->visited = 1;
	hm_find(lemin->map, lemin->start->content)->bfs_lev = 0;
	hm_find(lemin->map, lemin->end->content)->visited = 1;
	hm_find(lemin->map, lemin->end->content)->bfs_lev = INT32_MAX;
}

void	flush_visits(t_lemin *lemin)
{
	t_list		*vertice_list;

	vertice_list = lemin->list;
	while (vertice_list)
	{
		hm_find(lemin->map, vertice_list->content)->visited = 0;
		vertice_list = vertice_list->next;
	}
}

void	return_bfs_augm_index_edges(t_lemin *lemin)
{
	t_list	*lst;
	t_cont	*cont;

	lst = lemin->list;
	while (lst)
	{
		cont = hm_find(lemin->map, lst->content);
		if (cont->deleted_bfs_augm_index)
			lst_move_all_from_to(&(cont->deleted_bfs_augm_index),
													&(cont->list));
		lst = lst->next;
	}
}
