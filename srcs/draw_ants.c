/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstokes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 21:15:35 by jstokes           #+#    #+#             */
/*   Updated: 2019/10/26 21:15:36 by jstokes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/visual.h"

int		put_size(SDL_Rect *rect)
{
	rect->w = ROOM_SIZE;
	rect->h = ROOM_SIZE;
	return (-1);
}

void	draw_ants(t_lemin *lemin, t_vis *vis, double num)
{
	int			i;
	t_list		*ant;
	SDL_Rect	rect;
	t_cont		*cont;
	t_cont		*next;

	i = put_size(&rect);
	while (++i < lemin->ants)
	{
		ant = *(lemin->moves + i);
		cont = hm_find(lemin->map, ant->content);
		if (ant->x != vis->move ||
			ft_strcmp(ant->content, lemin->end->content) == 0)
		{
			rect.x = cont->x + vis->x_shift;
			rect.y = cont->y + vis->y_shift;
		}
		if (ant->x == vis->move && ant->next)
		{
			next = hm_find(lemin->map, ant->next->content);
			rect.x = cont->x + vis->x_shift + (next->x - cont->x) * num;
			rect.y = cont->y + vis->y_shift + (next->y - cont->y) * num;
		}
		SDL_RenderCopy(vis->renderer, vis->ant, NULL, &rect);
	}
}
