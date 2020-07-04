/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   augmenting_reverse_paths.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstokes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 21:22:04 by jstokes           #+#    #+#             */
/*   Updated: 2019/10/26 21:22:06 by jstokes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void	deal_with_start_edges(t_lemin *lemin)
{
	t_path	*path;
	t_cont	*cont;

	cont = hm_find(lemin->map, lemin->start->content);
	if (cont->deleted_orient)
		lst_move_all_from_to(&(cont->deleted_orient), &(cont->list));
	if (cont->deleted_bfs_shortest)
		lst_move_all_from_to(&(cont->deleted_bfs_shortest), &(cont->list));
	if (cont->deleted_layers)
		lst_move_all_from_to(&(cont->deleted_layers), &(cont->list));
	if (cont->deleted_bfs_augm)
		lst_move_all_from_to(&(cont->deleted_bfs_augm), &(cont->list));
	path = lemin->best_paths;
	while (path)
	{
		lst_move_from_to(&(cont->list),
			&(cont->deleted_bfs_augm), path->list->content);
		path = path->next;
	}
	cont->kid = NULL;
	cont->visited = 1;
}

void	deal_with_end_edges(t_lemin *lemin)
{
	t_cont	*cont;

	cont = hm_find(lemin->map, lemin->end->content);
	if (cont->deleted_orient)
		lst_move_all_from_to(&(cont->deleted_orient), &(cont->list));
	if (cont->deleted_bfs_shortest)
		lst_move_all_from_to(&(cont->deleted_bfs_shortest), &(cont->list));
	if (cont->deleted_layers)
		lst_move_all_from_to(&(cont->deleted_layers), &(cont->list));
	cont->visited = 1;
}

void	return_deleted(t_cont *cont)
{
	if (cont->deleted_orient)
		lst_move_all_from_to(&(cont->deleted_orient), &(cont->list));
	if (cont->deleted_bfs_shortest)
		lst_move_all_from_to(&(cont->deleted_bfs_shortest), &(cont->list));
	if (cont->deleted_layers)
		lst_move_all_from_to(&(cont->deleted_layers), &(cont->list));
	if (cont->deleted_bfs_augm)
		lst_move_all_from_to(&(cont->deleted_bfs_augm), &(cont->list));
}

void	augmenting_reverse_paths(t_lemin *lemin)
{
	t_cont	*cont;
	t_list	*lst;
	t_path	*path;

	path = lemin->best_paths;
	deal_with_start_edges(lemin);
	while (path)
	{
		lst = path->list;
		while (lst->next)
		{
			cont = hm_find(lemin->map, lst->content);
			cont->visited = 1;
			if (!lst->prev)
				cont->kid = lemin->start->content;
			else
				cont->kid = lst->prev->content;
			return_deleted(cont);
			lst_move_from_to(&(cont->list),
				&(cont->deleted_bfs_augm), lst->next->content);
			lst = lst->next;
		}
		path = path->next;
	}
	deal_with_end_edges(lemin);
}

void	return_all_other_edges(t_lemin *lemin)
{
	t_list	*lst;
	t_cont	*cont;

	lst = lemin->list;
	while (lst)
	{
		cont = hm_find(lemin->map, lst->content);
		if (cont->visited == 0)
		{
			if (cont->deleted_orient)
				lst_move_all_from_to(&(cont->deleted_orient), &(cont->list));
			if (cont->deleted_bfs_shortest)
				lst_move_all_from_to(&(cont->deleted_bfs_shortest),
															&(cont->list));
			if (cont->deleted_layers)
				lst_move_all_from_to(&(cont->deleted_layers), &(cont->list));
			if (cont->deleted_bfs_augm)
				lst_move_all_from_to(&(cont->deleted_bfs_augm), &(cont->list));
			cont->kid = NULL;
		}
		lst = lst->next;
	}
}
