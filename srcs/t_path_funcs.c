/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_path_funcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstokes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 14:12:39 by jstokes           #+#    #+#             */
/*   Updated: 2019/10/14 14:12:40 by jstokes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void	path_add_end(t_path **paths, t_path *path)
{
	t_path	*tmp;

	if (!paths || !path)
		return ;
	if (!(*paths))
		*paths = path;
	else
	{
		tmp = *paths;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = path;
	}
}

void	add_new_path(t_lemin *lemin)
{
	void	*name;
	t_path	*path;
	t_cont	*cont;

	name = lemin->end->content;
	cont = hm_find(lemin->map, name);
	if (!(cont->parent))
		return ;
	if (!(path = new_path()))
		clean_n_error(lemin, NULL, 0);
	path_add_end(&(lemin->paths), path);
	if (!lst_push_back_void(&(path->list), lemin->end->content))
		clean_n_error(lemin, NULL, 0);
	while (cont->parent != lemin->start->content)
	{
		name = cont->parent;
		if (!lst_push_front_void(&(path->list), name))
			clean_n_error(lemin, NULL, 0);
		cont = hm_find(lemin->map, name);
	}
	path->len = ft_lstlen(path->list);
}

void	del_path(t_path **path)
{
	if (path && *path)
	{
		if ((*path)->next)
			del_path(&((*path)->next));
		lst_del(&((*path)->list));
		free(*path);
		*path = NULL;
	}
}

t_path	*new_path(void)
{
	t_path	*path;

	if (!(path = (t_path *)malloc(sizeof(t_path))))
		return (NULL);
	path->len = 0;
	path->list = NULL;
	path->next = NULL;
	return (path);
}

int		get_path_len(t_path *paths, int i)
{
	int		j;

	j = 0;
	while (++j < i)
		paths = paths->next;
	return ((int)paths->len);
}
