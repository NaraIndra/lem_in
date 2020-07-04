/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_layers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstokes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 22:22:09 by jstokes           #+#    #+#             */
/*   Updated: 2019/10/26 22:22:10 by jstokes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void	consider_case0(t_cont *cont,
		t_lemin *lemin, t_list **queue, t_list *tmp_adj_list)
{
	cont->visited = 1;
	bfs_erase_layers(lemin, tmp_adj_list->content);
	lst_p_b_v_pr(queue, tmp_adj_list->content, lemin);
}

int		bfs_del_layers(t_lemin *lemin)
{
	t_list		*queue;
	t_list		*tmp_adj_list;
	t_cont		*cont;
	char		*tmp;

	queue = NULL;
	tmp = lemin->start->content;
	flush_visits(lemin);
	lst_p_b_v_pr(&queue, lemin->start->content, lemin);
	hm_find(lemin->map, lemin->start->content)->visited = 1;
	while (queue)
	{
		tmp = lst_pop_front_void(&queue);
		tmp_adj_list = hm_find(lemin->map, tmp)->list;
		while (tmp_adj_list)
		{
			cont = hm_find(lemin->map, tmp_adj_list->content);
			if (cont->visited == 0)
				consider_case0(cont,
								lemin, &queue, tmp_adj_list);
			tmp_adj_list = tmp_adj_list->next;
		}
	}
	return (0);
}

void	bfs_erase_layers(t_lemin *lemin, void *cont_i_name)
{
	t_list		*i_list;
	t_list		*next;
	t_cont		*cont_i;
	t_cont		*cont_j;

	cont_i = hm_find(lemin->map, cont_i_name);
	i_list = cont_i->list;
	next = NULL;
	while (i_list)
	{
		cont_j = hm_find(lemin->map, i_list->content);
		next = i_list->next;
		if (cont_i->bfs_lev == cont_j->bfs_lev)
		{
			lst_move_from_to(&(cont_i->list),
					&(cont_i->deleted_layers), i_list->content);
			lst_move_from_to(&(cont_j->list),
					&(cont_j->deleted_layers), cont_i_name);
		}
		i_list = next;
	}
}
