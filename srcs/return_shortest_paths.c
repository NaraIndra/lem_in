/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_shortest_paths.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstokes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 23:01:44 by jstokes           #+#    #+#             */
/*   Updated: 2019/10/25 23:01:45 by jstokes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void	return_shortest_paths(t_lemin *lemin)
{
	t_cont	*cont;
	t_path	*path;
	t_list	*tmp;

	path = lemin->paths;
	while (path)
	{
		tmp = path->list->last;
		while (tmp->prev)
		{
			cont = hm_find(lemin->map, tmp->content);
			lst_move_from_to(&(cont->deleted_bfs_shortest),
				&(cont->list), tmp->prev->content);
			tmp = tmp->prev;
		}
		cont = hm_find(lemin->map, tmp->content);
		lst_move_from_to(&(cont->deleted_bfs_shortest),
			&(cont->list), lemin->start->content);
		path = path->next;
	}
}

void	return_oriented_edges(t_lemin *lemin)
{
	t_list	*lst;
	t_list	*tmp;
	t_cont	*cont;

	lst = lemin->list;
	while (lst)
	{
		cont = hm_find(lemin->map, lst->content);
		tmp = lst_pop_front(&(cont->deleted_orient));
		while (tmp)
		{
			lst_push_back(&(cont->list), tmp);
			tmp = lst_pop_front(&(cont->deleted_orient));
		}
		tmp = lst_pop_front(&(cont->deleted_layers));
		while (tmp)
		{
			lst_push_back(&(cont->list), tmp);
			tmp = lst_pop_front(&(cont->deleted_layers));
		}
		lst = lst->next;
	}
}
