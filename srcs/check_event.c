/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_event.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstokes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 21:30:41 by jstokes           #+#    #+#             */
/*   Updated: 2019/10/26 21:30:46 by jstokes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/visual.h"

void	check_event(t_lemin *lemin, t_vis *vis)
{
	SDL_Event	event;

	while (SDL_PollEvent(&event))
	{
		if (vis && (event.type == SDL_QUIT ||
			event.key.keysym.scancode == SDL_SCANCODE_Q ||
			event.key.keysym.scancode == SDL_SCANCODE_ESCAPE))
			vis->close = 1;
		if (vis && lemin && !vis->ants_move &&
			event.key.keysym.scancode == SDL_SCANCODE_N &&
			vis->move < (int)lemin->moves_num - 1)
			vis->ants_move = 1;
		if (vis && lemin && !vis->ants_move &&
			event.key.keysym.scancode == SDL_SCANCODE_R)
		{
			init_ants_location(lemin);
			vis->move = -1;
		}
	}
}
