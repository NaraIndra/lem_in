/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstokes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 21:30:03 by jstokes           #+#    #+#             */
/*   Updated: 2019/10/26 21:30:04 by jstokes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/visual.h"

void	init_vis(t_vis *vis)
{
	SDL_Color	color;

	color = get_color(0, 30, 255, 200);
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
		free_n_close(vis);
	vis->window = create_window(vis);
	vis->renderer = create_renderer(vis);
	if (TTF_Init() != 0 ||
		(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG ||
		!(vis->font = TTF_OpenFont("font/Pacifico.ttf", 40)))
		free_n_close(vis);
	vis->background = create_texture(vis, "images/background2.png");
	if (!(vis->backgr_dims = create_rect(0, 0, WIDTH, WIDTH)))
		free_n_close(vis);
	vis->start_end_rooms = create_texture(vis, "images/start_end_room.png");
	vis->other_rooms = create_texture(vis, "images/other_rooms.png");
	vis->ant = create_texture(vis, "images/ant.png");
	vis->reload = create_sign(vis, "R - Reload", color);
	vis->next = create_sign(vis, "N - Next", color);
}
