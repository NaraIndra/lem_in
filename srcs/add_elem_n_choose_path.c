/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_elem_n_choose_path.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstokes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 20:25:09 by jstokes           #+#    #+#             */
/*   Updated: 2019/10/25 20:25:10 by jstokes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

int		walk_cur_sour(t_lemin *lemin,
								t_path *path, void *name, t_cont *cont)
{
	cont->visited = 1;
	if (add_elem_n_choose_path(lemin, path, name, cont->parent) == 1)
		return (1);
	return (0);
}

int		walk_kid(t_lemin *lemin, t_path *path, void *name, t_cont *cont)
{
	cont->visited = 1;
	if (add_elem_n_choose_path(lemin, path, name, cont->kid) == 1)
		return (1);
	return (0);
}

int		the_last_case(t_lemin *lemin, t_path *path, void *prev, void *tmp)
{
	t_cont	*cont;

	cont = hm_find(lemin->map, tmp);
	if (hm_find(lemin->map, cont->parent)->visited == 1
			&& hm_find(lemin->map, cont->kid)->visited == 1)
		return (0);
	if (prev == cont->parent ||
			hm_find(lemin->map, cont->parent)->visited == 1)
		return (walk_kid(lemin, path, tmp, cont));
	else if (prev == cont->kid ||
			hm_find(lemin->map, cont->kid)->visited == 1)
		return (walk_cur_sour(lemin, path, tmp, cont));
	else if (hm_find(lemin->map, prev)->kid == tmp)
		return (walk_cur_sour(lemin, path, tmp, cont));
	else if (hm_find(lemin->map, prev)->parent == tmp)
		return (walk_kid(lemin, path, tmp, cont));
	return (0);
}

int		add_elem_n_choose_path(t_lemin *lemin,
										t_path *path, void *prev, void *tmp)
{
	t_cont	*cont;

	cont = hm_find(lemin->map, tmp);
	if (!(lst_push_front_void(&(path->list), tmp)))
		clean_n_error(lemin, NULL, 0);
	cont->visited = 1;
	if (cont->parent == lemin->start->content ||
		cont->kid == lemin->start->content)
		return (1);
	if (!cont->parent && !cont->kid)
		clean_n_error(lemin, NULL, 0);
	if (cont->parent && !(cont->kid))
		return (walk_cur_sour(lemin, path, tmp, cont));
	else if (!(cont->parent) && cont->kid)
		return (walk_kid(lemin, path, tmp, cont));
	else
		return (the_last_case(lemin, path, prev, tmp));
	return (0);
}
