/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstokes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 21:26:04 by jstokes           #+#    #+#             */
/*   Updated: 2019/10/26 21:26:06 by jstokes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/visual.h"

SDL_Texture		*create_texture(t_vis *vis, char *name)
{
	SDL_Surface		*surface;
	SDL_Texture		*texture;

	surface = IMG_Load(name);
	if (!surface)
		free_n_close(vis);
	texture = SDL_CreateTextureFromSurface(vis->renderer, surface);
	SDL_FreeSurface(surface);
	if (!texture)
		free_n_close(vis);
	return (texture);
}
