/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_with_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstokes <jstokes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 21:40:54 by jstokes           #+#    #+#             */
/*   Updated: 2019/10/27 22:26:56 by jstokes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

int		find_shortest_paths(t_lemin *lemin)
{
	while (TRUE)
	{
		flush_levels_visits(lemin);
		dinic_build_residual_network(lemin, 1);
		if (bfs_shortest(lemin) == 0)
			break ;
		add_new_path(lemin);
		if (compare_paths(lemin, 0) == 0)
		{
			lemin->best_paths = lemin->paths;
			lemin->paths = NULL;
			return (0);
		}
		reverse_path(lemin);
		return_oriented_edges(lemin);
	}
	return (1);
}

int		find_other_paths(t_lemin *lemin)
{
	while (TRUE)
	{
		flush_levels_visits(lemin);
		flush_visits(lemin);
		new_bfs_augmenting_indexing(lemin);
		flush_visits(lemin);
		if (bfs_augmenting(lemin) == 0)
			break ;
		flush_visits(lemin);
		augmenting_new_paths(lemin);
		if (compare_paths(lemin, 1) == 0)
			return (0);
		augmenting_reverse_paths(lemin);
		return_all_other_edges(lemin);
	}
	return (1);
}

void	work_with_map(t_lemin *lemin)
{
	int		j;

	bfs_indexing(lemin);
	delete_unuseful_rooms(lemin);
	j = delete_dead_ends(lemin);
	while (j > 0)
		j = delete_dead_ends(lemin);
	if (find_shortest_paths(lemin) == 0)
		return ;
	return_oriented_edges(lemin);
	return_shortest_paths(lemin);
	lemin->best_paths = lemin->paths;
	lemin->paths = NULL;
	find_other_paths(lemin);
}
