/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_sign.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstokes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 21:21:24 by jstokes           #+#    #+#             */
/*   Updated: 2019/10/26 21:21:25 by jstokes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/visual.h"

SDL_Texture		*create_sign(t_vis *vis, char *str, SDL_Color color)
{
	SDL_Surface	*surface;
	SDL_Texture	*texture;

	if (!(surface = TTF_RenderText_Solid(vis->font, str, color)))
		free_n_close(vis);
	if (!(texture = SDL_CreateTextureFromSurface(vis->renderer, surface)))
	{
		SDL_FreeSurface(surface);
		free_n_close(vis);
	}
	SDL_FreeSurface(surface);
	return (texture);
}
