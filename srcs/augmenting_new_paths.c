/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   augmenting_new_paths.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstokes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 20:24:57 by jstokes           #+#    #+#             */
/*   Updated: 2019/10/25 20:24:58 by jstokes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

t_path	*do_this_case(t_path **paths, t_lemin *lemin)
{
	t_path	*new;

	if (!(new = new_path()) ||
		!lst_push_back_void(&(new->list), lemin->end->content))
		clean_n_error(lemin, NULL, 0);
	path_add_end(&(lemin->paths), new);
	new->len = 1;
	*paths = (*paths)->next;
	return (*paths);
}

void	rebuild_old_paths(t_lemin *lemin)
{
	t_path	*new;
	t_path	*path;
	int		j;

	path = lemin->best_paths;
	while (path)
	{
		if (path->len == 1)
			if (!do_this_case(&path, lemin))
				break ;
		if (!(new = new_path()) ||
			!lst_push_back_void(&(new->list), lemin->end->content))
			clean_n_error(lemin, NULL, 0);
		j = add_elem_n_choose_path(lemin, new,
			lemin->end->content, path->list->last->prev->content);
		if (j == 0)
			del_path(&new);
		else
		{
			path_add_end(&(lemin->paths), new);
			new->len = ft_lstlen(new->list);
		}
		path = path->next;
	}
}

void	augmenting_new_paths(t_lemin *lemin)
{
	t_path	*path;
	t_cont	*cont;
	void	*name;
	int		j;

	name = lemin->end->content;
	cont = hm_find(lemin->map, name);
	if (!(cont->parent))
		return ;
	flush_visits(lemin);
	if (!(path = new_path()))
		clean_n_error(lemin, NULL, 0);
	if (!lst_push_back_void(&(path->list), name))
		clean_n_error(lemin, NULL, 0);
	j = add_elem_n_choose_path(lemin, path, name, cont->parent);
	if (j == 0)
		del_path(&path);
	else
	{
		path_add_end(&(lemin->paths), path);
		path->len = ft_lstlen(path->list);
	}
	rebuild_old_paths(lemin);
}
