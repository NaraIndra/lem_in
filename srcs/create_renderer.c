/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_renderer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstokes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 21:26:30 by jstokes           #+#    #+#             */
/*   Updated: 2019/10/26 21:26:35 by jstokes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/visual.h"

SDL_Renderer	*create_renderer(t_vis *vis)
{
	SDL_Renderer	*renderer;

	renderer = SDL_CreateRenderer(vis->window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer)
		free_n_close(vis);
	return (renderer);
}
