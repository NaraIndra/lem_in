/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_cont_funcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstokes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 21:42:44 by jstokes           #+#    #+#             */
/*   Updated: 2019/10/25 21:42:45 by jstokes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

t_cont	*create_cont(int x, int y)
{
	t_cont	*cont;

	if (!(cont = (t_cont *)malloc(sizeof(t_cont))))
		return (NULL);
	cont->x = x;
	cont->y = y;
	cont->bfs_lev = -1;
	cont->list = NULL;
	cont->kid = NULL;
	cont->deleted_bfs_augm = NULL;
	cont->deleted_bfs_shortest = NULL;
	cont->deleted_layers = NULL;
	cont->deleted_orient = NULL;
	cont->deleted_bfs_augm_index = NULL;
	cont->coming_links = NULL;
	return (cont);
}

void	delete_cont(t_cont **cont)
{
	if (cont && *cont)
	{
		if ((*cont)->list)
			lst_del(&((*cont)->list));
		if ((*cont)->deleted_bfs_augm)
			lst_del(&((*cont)->deleted_bfs_augm));
		if ((*cont)->deleted_bfs_augm_index)
			lst_del(&((*cont)->deleted_bfs_augm_index));
		if ((*cont)->deleted_bfs_shortest)
			lst_del(&((*cont)->deleted_bfs_shortest));
		if ((*cont)->deleted_layers)
			lst_del(&((*cont)->deleted_layers));
		if ((*cont)->deleted_orient)
			lst_del(&((*cont)->deleted_orient));
		free(*cont);
		*cont = NULL;
	}
}

void	clean_all_cont(t_lemin *lemin)
{
	t_list	*tmp;
	t_cont	*cont;

	tmp = lemin->list;
	while (tmp)
	{
		cont = hm_find(lemin->map, tmp->content);
		if (cont)
			delete_cont(&cont);
		tmp = tmp->next;
	}
	tmp = lemin->deleted_rooms;
	while (tmp)
	{
		cont = hm_find(lemin->map, tmp->content);
		if (cont)
			delete_cont(&cont);
		tmp = tmp->next;
	}
}
