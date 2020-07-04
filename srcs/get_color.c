/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstokes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 21:11:47 by jstokes           #+#    #+#             */
/*   Updated: 2019/10/26 21:11:49 by jstokes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/visual.h"

Uint32		color_to_uint(int red, int green, int blue, int alpha)
{
	SDL_Color	color;

	color.r = (Uint8)red;
	color.g = (Uint8)green;
	color.b = (Uint8)blue;
	color.a = (Uint8)alpha;
	return ((color.a << 0) | (color.r << 24) |
				(color.g << 16) | (color.b << 8));
}

SDL_Color	get_color(int red, int green, int blue, int alpha)
{
	SDL_Color	color;

	color.r = (Uint8)red;
	color.g = (Uint8)green;
	color.b = (Uint8)blue;
	color.a = (Uint8)alpha;
	return (color);
}
