/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstokes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 23:00:48 by jstokes           #+#    #+#             */
/*   Updated: 2019/10/25 23:00:49 by jstokes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void	reverse_path(t_lemin *lemin)
{
	t_cont	*cont;
	t_cont	*nextcont;
	void	*name;

	if (!(hm_find(lemin->map, lemin->end->content)->parent))
		return ;
	name = lemin->end->content;
	cont = hm_find(lemin->map, name);
	while (cont->parent != lemin->start->content)
	{
		nextcont = hm_find(lemin->map, cont->parent);
		lst_move_from_to(&(nextcont->list),
			&(nextcont->deleted_bfs_shortest), name);
		lst_move_from_to(&(cont->deleted_orient),
			&(cont->deleted_bfs_shortest), cont->parent);
		cont->kid = cont->parent;
		name = cont->parent;
		cont = nextcont;
	}
	nextcont = hm_find(lemin->map, cont->parent);
	lst_move_from_to(&(nextcont->list),
		&(nextcont->deleted_bfs_shortest), name);
	lst_move_from_to(&(cont->deleted_orient),
		&(cont->deleted_bfs_shortest), cont->parent);
	cont->kid = cont->parent;
}
