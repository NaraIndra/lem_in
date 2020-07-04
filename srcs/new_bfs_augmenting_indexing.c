/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_bfs_augmenting_indexing.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstokes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 22:37:02 by jstokes           #+#    #+#             */
/*   Updated: 2019/10/25 22:37:03 by jstokes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

char	move_back(t_lemin *lemin, void *tmp_name, t_cont *tmp_cont, int j)
{
	t_cont	*prev_cont;

	prev_cont = hm_find(lemin->map, tmp_cont->parent);
	if (tmp_cont->kid && !prev_cont->kid &&
		(lst_find_elem(tmp_cont->list, lemin->start->content) || j == 1))
	{
		lst_move_from_to(&(prev_cont->list),
			&(prev_cont->deleted_bfs_augm_index), tmp_name);
		lst_move_from_to(&(tmp_cont->list),
			&(tmp_cont->deleted_bfs_augm_index), tmp_cont->parent);
		flush_levels_visits(lemin);
		new_bfs_augmenting_indexing(lemin);
		return (0);
	}
	if (tmp_cont->kid && prev_cont->kid && ft_lstlen(tmp_cont->list) == 1)
	{
		tmp_cont->visited = 0;
		return (move_back(lemin, tmp_cont->parent, prev_cont, 1));
	}
	return (1);
}

char	deal_with_list(t_lemin *lemin, t_list **queue,
									void *tmp_name, t_cont *tmp_cont)
{
	t_list	*tmp_list;
	t_cont	*tmp_list_cont;

	tmp_list = tmp_cont->list;
	while (tmp_list)
	{
		if (tmp_list->content == lemin->start->content)
		{
			return (move_back(lemin, tmp_name, tmp_cont, 0));
			tmp_list = tmp_list->next;
			continue ;
		}
		tmp_list_cont = hm_find(lemin->map, tmp_list->content);
		if (tmp_list_cont->visited == 0)
		{
			tmp_list_cont = hm_find(lemin->map, tmp_list->content);
			tmp_list_cont->visited = 1;
			if (!lst_push_back_void(queue, tmp_list->content))
				return (0);
			tmp_list_cont->parent = tmp_name;
			tmp_list_cont->bfs_lev = tmp_cont->bfs_lev + 1;
		}
		tmp_list = tmp_list->next;
	}
	return (1);
}

char	analize_tmp_list(t_lemin *lemin, t_list **queue,
									void *tmp_name, t_cont *tmp_cont)
{
	t_cont	*tmp_list_cont;

	tmp_list_cont = hm_find(lemin->map, tmp_cont->parent);
	if (tmp_list_cont && tmp_cont->kid && !tmp_list_cont->kid)
	{
		if (tmp_cont->kid == lemin->start->content)
			return (move_back(lemin, tmp_name, tmp_cont, 0));
		tmp_list_cont = hm_find(lemin->map, tmp_cont->kid);
		if (tmp_list_cont->visited == 0 ||
				tmp_cont->kid == lemin->start->content)
		{
			tmp_list_cont = hm_find(lemin->map, tmp_cont->kid);
			tmp_list_cont->visited = 1;
			if (!lst_push_back_void(queue, tmp_cont->kid))
				clean_n_error(lemin, NULL, 0);
			tmp_list_cont->parent = tmp_name;
			tmp_list_cont->bfs_lev = tmp_cont->bfs_lev + 1;
		}
		return (1);
	}
	return (deal_with_list(lemin, queue, tmp_name, tmp_cont));
}

char	new_bfs_augmenting_indexing(t_lemin *lemin)
{
	t_list	*tmp;
	t_cont	*cont;
	t_list	*queue;
	void	*tmp_name;

	queue = NULL;
	lst_p_b_v_pr(&(queue), lemin->start->content, lemin);
	hm_find(lemin->map, lemin->start->content)->visited = 1;
	while (queue)
	{
		tmp = lst_pop_front(&queue);
		tmp_name = tmp->content;
		lst_del(&(tmp));
		cont = hm_find(lemin->map, tmp_name);
		if (cont->list)
			if (analize_tmp_list(lemin, &queue, tmp_name, cont) < 1)
			{
				lst_del(&queue);
				return (0);
			}
	}
	return (1);
}
