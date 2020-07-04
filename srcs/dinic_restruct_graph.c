/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinic_restruct_graph.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstygg <mstygg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 22:29:04 by mstygg            #+#    #+#             */
/*   Updated: 2019/10/22 15:05:41 by mstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void	do_0case(t_list **queue,
				t_lemin *lemin, void *tmp, t_list *tmp_adj_list)
{
	t_cont	*cont;

	cont = hm_find(lemin->map, tmp_adj_list->content);
	cont->visited = 1;
	cont->parent = tmp;
	cont->bfs_lev = hm_find(lemin->map, tmp)->bfs_lev + 1;
	lst_p_b_v_pr(queue, tmp_adj_list->content, lemin);
}

int		bfs_index_layers_basic(t_lemin *lemin)
{
	t_list		*queue;
	t_list		*tmp_adj_list;
	t_cont		*cont;
	char		*tmp;

	queue = NULL;
	tmp = lemin->start->content;
	lst_p_b_v_pr(&queue, lemin->start->content, lemin);
	hm_find(lemin->map, lemin->start->content)->visited = 1;
	while (ft_lstlen(queue))
	{
		tmp = lst_pop_front_void(&queue);
		tmp_adj_list = hm_find(lemin->map, tmp)->list;
		while (tmp_adj_list)
		{
			cont = hm_find(lemin->map, tmp_adj_list->content);
			if (cont->visited == 0)
				do_0case(&queue, lemin, tmp, tmp_adj_list);
			tmp_adj_list = tmp_adj_list->next;
		}
	}
	return (0);
}

void	another_0case(t_cont *cont_j,
				t_lemin *lemin, t_list *i_adj_list, t_list **queue)
{
	cont_j->visited = 1;
	bfs_erase_orient(lemin, i_adj_list->content);
	lst_p_b_v_pr(queue, i_adj_list->content, lemin);
}

void	bfs_orientate(t_lemin *lemin)
{
	t_list		*queue;
	t_list		*i_adj_list;
	t_cont		*cont_i;
	t_cont		*cont_j;
	char		*tmp;

	queue = NULL;
	flush_visits(lemin);
	lst_p_b_v_pr(&queue, lemin->start->content, lemin);
	hm_find(lemin->map, lemin->start->content)->visited = 1;
	while (queue)
	{
		tmp = lst_pop_front_void(&queue);
		cont_i = hm_find(lemin->map, tmp);
		i_adj_list = cont_i->list;
		while (i_adj_list)
		{
			cont_j = hm_find(lemin->map, i_adj_list->content);
			if (cont_j->visited == 0)
				another_0case(cont_j, lemin, i_adj_list, &queue);
			i_adj_list = i_adj_list->next;
		}
	}
}

void	bfs_erase_orient(t_lemin *lemin, void *cont_i_name)
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
		if (cont_i->bfs_lev > cont_j->bfs_lev)
			lst_move_from_to(&(cont_i->list),
				&(cont_i->deleted_orient), i_list->content);
		else if (cont_j->bfs_lev > cont_i->bfs_lev)
			lst_move_from_to(&(cont_j->list),
				&(cont_j->deleted_orient), i_list->content);
		i_list = next;
	}
}
