/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstokes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 21:25:30 by jstokes           #+#    #+#             */
/*   Updated: 2019/10/26 21:25:31 by jstokes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/visual.h"

SDL_Window	*create_window(t_vis *vis)
{
	SDL_Window	*window;

	window = SDL_CreateWindow("Lem-in", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
	if (!window)
		free_n_close(vis);
	return (window);
}
