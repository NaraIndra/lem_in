/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis_clean.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstokes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 21:04:43 by jstokes           #+#    #+#             */
/*   Updated: 2019/10/26 21:04:45 by jstokes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/visual.h"

void	destroy_texture(SDL_Texture *text)
{
	if (text)
		SDL_DestroyTexture(text);
}

void	vis_clean(t_vis **vis)
{
	if (vis && *vis)
	{
		destroy_texture((*vis)->next);
		destroy_texture((*vis)->reload);
		destroy_texture((*vis)->ant);
		destroy_texture((*vis)->other_rooms);
		destroy_texture((*vis)->start_end_rooms);
		free((*vis)->backgr_dims);
		destroy_texture((*vis)->background);
		TTF_CloseFont((*vis)->font);
		if ((*vis)->renderer)
			SDL_DestroyRenderer((*vis)->renderer);
		if ((*vis)->window)
			SDL_DestroyWindow((*vis)->window);
		TTF_Quit();
		IMG_Quit();
		SDL_Quit();
		free(*vis);
		*vis = NULL;
	}
}

void	free_n_close(t_vis *vis)
{
	if (vis)
		vis_clean(&vis);
	print_error();
}
