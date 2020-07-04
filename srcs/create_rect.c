/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_rect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstokes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 21:27:13 by jstokes           #+#    #+#             */
/*   Updated: 2019/10/26 21:27:34 by jstokes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/visual.h"

SDL_Rect	*create_rect(int x, int y, int w, int h)
{
	SDL_Rect	*rect;

	if (!(rect = (SDL_Rect *)malloc(sizeof(SDL_Rect))))
		return (NULL);
	rect->x = x;
	rect->y = y;
	rect->w = w;
	rect->h = h;
	return (rect);
}
