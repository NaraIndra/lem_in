/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinic_build_network.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstygg <mstygg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 23:06:29 by mstygg            #+#    #+#             */
/*   Updated: 2019/10/22 14:56:19 by mstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void	dinic_build_residual_network(t_lemin *lemin, int net_state)
{
	flush_levels_visits(lemin);
	if (net_state == NET_IS_OPEN)
		bfs_index_layers_basic(lemin);
	bfs_del_layers(lemin);
	bfs_orientate(lemin);
}
