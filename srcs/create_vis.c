/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_vis.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstokes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 21:25:46 by jstokes           #+#    #+#             */
/*   Updated: 2019/10/26 21:25:47 by jstokes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/visual.h"

t_vis	*create_vis(void)
{
	t_vis	*vis;

	if (!(vis = (t_vis *)malloc(sizeof(t_vis))))
		free_n_close(vis);
	vis->window = NULL;
	vis->renderer = NULL;
	vis->font = NULL;
	vis->background = NULL;
	vis->backgr_dims = NULL;
	vis->start_end_rooms = NULL;
	vis->other_rooms = NULL;
	vis->ant = NULL;
	vis->reload = NULL;
	vis->next = NULL;
	vis->close = 0;
	vis->ants_move = 0;
	vis->x_shift = 0;
	vis->y_shift = 0;
	vis->move = -1;
	return (vis);
}
