/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinic_find_paths.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstokes <jstokes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 14:58:59 by mstygg            #+#    #+#             */
/*   Updated: 2019/10/27 22:31:47 by jstokes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

int		deal_with_tmp_adj(t_lemin *lemin, t_list *tmp_adj_list,
									void *tmp, t_list **queue)
{
	t_cont	*cont;

	cont = hm_find(lemin->map, tmp_adj_list->content);
	if (cont->visited == 0)
	{
		cont->visited = 1;
		cont->parent = tmp;
		lst_p_b_v_pr(queue, tmp_adj_list->content, lemin);
		if (tmp_adj_list->content == lemin->end->content)
			return (1);
	}
	return (0);
}

int		bfs_shortest(t_lemin *lemin)
{
	t_list	*queue;
	t_list	*tmp_adj_list;
	char	*tmp;

	queue = NULL;
	tmp = lemin->start->content;
	lst_p_b_v_pr(&queue, lemin->start->content, lemin);
	flush_visits(lemin);
	hm_find(lemin->map, lemin->start->content)->visited = 1;
	while (ft_lstlen(queue))
	{
		tmp = lst_pop_front_void(&queue);
		tmp_adj_list = hm_find(lemin->map, tmp)->list;
		while (tmp_adj_list && !(hm_find(lemin->map, tmp)->kid))
		{
			if (deal_with_tmp_adj(lemin,
					tmp_adj_list, tmp, &queue) == 1)
			{
				lst_del(&queue);
				return (1);
			}
			tmp_adj_list = tmp_adj_list->next;
		}
	}
	return (0);
}

int		overflow_alert(t_lemin *lemin, void *testing_vertice_name)
{
	t_cont	*source_vertice;
	t_cont	*test_vertice;

	test_vertice = hm_find(lemin->map, testing_vertice_name);
	source_vertice = hm_find(lemin->map, test_vertice->parent);
	if (testing_vertice_name == lemin->start->content
	|| !test_vertice->kid || (test_vertice->kid && (source_vertice->kid)))
		return (0);
	else
		return (1);
}

int		cons_tmp_adj_list(t_lemin *lemin,
				t_list **queue, t_list *tmp_adj_list, void *tmp)
{
	t_cont	*cont;

	cont = hm_find(lemin->map, tmp_adj_list->content);
	if (cont->visited == 0)
	{
		if (tmp_adj_list->content == lemin->end->content)
		{
			hm_find(lemin->map, lemin->end->content)->parent = tmp;
			return (1);
		}
		if (!overflow_alert(lemin, tmp))
		{
			cont->visited = 1;
			cont->parent = tmp;
			lst_p_b_v_pr(queue, tmp_adj_list->content, lemin);
		}
		else
		{
			hm_find(lemin->map, hm_find(lemin->map, tmp)->kid)->visited = 1;
			hm_find(lemin->map, hm_find(lemin->map, tmp)->kid)->parent = tmp;
			lst_p_b_v_pr(queue, hm_find(lemin->map, tmp)->kid, lemin);
			return (2);
		}
	}
	return (0);
}

int		bfs_augmenting(t_lemin *lemin)
{
	int		j;
	t_list	*queue;
	t_list	*tmp_adj_list;
	char	*tmp;

	queue = NULL;
	lst_p_b_v_pr(&queue, lemin->start->content, lemin);
	hm_find(lemin->map, lemin->start->content)->visited = 1;
	while (queue)
	{
		tmp = lst_pop_front_void(&queue);
		tmp_adj_list = hm_find(lemin->map, tmp)->list;
		while (tmp_adj_list)
		{
			if ((j = cons_tmp_adj_list(lemin, &queue, tmp_adj_list, tmp)) == 1)
			{
				lst_del(&queue);
				return (1);
			}
			if (j == 2)
				break ;
			tmp_adj_list = tmp_adj_list->next;
		}
	}
	return (0);
}
