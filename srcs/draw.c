/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstokes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 21:12:11 by jstokes           #+#    #+#             */
/*   Updated: 2019/10/26 21:12:14 by jstokes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/visual.h"

void	draw_links(t_lemin *lemin, t_vis *vis)
{
	t_list	*lst;
	t_list	*tmp;
	t_cont	*cont;
	t_cont	*tmpcont;

	lst = lemin->list;
	while (lst)
	{
		cont = hm_find(lemin->map, lst->content);
		tmp = cont->list;
		while (tmp)
		{
			tmpcont = hm_find(lemin->map, tmp->content);
			thickLineColor(vis->renderer,
				cont->x + ROOM_SIZE / 2 + vis->x_shift,
				cont->y + ROOM_SIZE / 2 + vis->y_shift,
				tmpcont->x + ROOM_SIZE / 2 + vis->x_shift,
				tmpcont->y + ROOM_SIZE / 2 + vis->y_shift,
				5, color_to_uint(100, 111, 50, 255));
			tmp = tmp->next;
		}
		lst = lst->next;
	}
}

void	draw_rooms(t_lemin *lemin, t_vis *vis)
{
	t_list		*lst;
	SDL_Rect	rect;

	lst = lemin->list;
	rect.w = ROOM_SIZE;
	rect.h = ROOM_SIZE;
	while (lst)
	{
		rect.x = lst->x + vis->x_shift;
		rect.y = lst->y + vis->y_shift;
		if (lst != lemin->start && lst != lemin->end)
			SDL_RenderCopy(vis->renderer, vis->other_rooms, NULL, &rect);
		else
			SDL_RenderCopy(vis->renderer, vis->start_end_rooms, NULL, &rect);
		lst = lst->next;
	}
}

void	draw_signs(t_vis *vis)
{
	SDL_Rect	rrect;
	SDL_Rect	nrect;

	SDL_QueryTexture(vis->reload, NULL, NULL, &rrect.w, &rrect.h);
	rrect.x = 50;
	rrect.y = 30;
	SDL_QueryTexture(vis->next, NULL, NULL, &nrect.w, &nrect.h);
	nrect.x = 50;
	nrect.y = 100;
	if (vis->ants_move)
		SDL_SetTextureAlphaMod(vis->reload, 100);
	else
		SDL_SetTextureAlphaMod(vis->reload, 255);
	SDL_RenderCopy(vis->renderer, vis->reload, NULL, &rrect);
	if (vis->ants_move)
		SDL_SetTextureAlphaMod(vis->next, 100);
	else
		SDL_SetTextureAlphaMod(vis->next, 255);
	SDL_RenderCopy(vis->renderer, vis->next, NULL, &nrect);
}

void	draw(t_lemin *lemin, t_vis *vis)
{
	double	num;

	num = 0.005;
	while (!(vis->close))
	{
		SDL_RenderClear(vis->renderer);
		SDL_RenderCopy(vis->renderer, vis->background, NULL, vis->backgr_dims);
		draw_links(lemin, vis);
		draw_rooms(lemin, vis);
		draw_ants(lemin, vis, num);
		draw_signs(vis);
		SDL_RenderPresent(vis->renderer);
		if (vis->ants_move && num < 1)
			num += 0.005;
		else if (vis->ants_move)
		{
			vis->ants_move = 0;
			num = 0.005;
			update_ants_location(lemin, vis);
			(vis->move)++;
		}
		check_event(lemin, vis);
	}
}
