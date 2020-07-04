/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_shift.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstokes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 21:29:33 by jstokes           #+#    #+#             */
/*   Updated: 2019/10/26 21:29:36 by jstokes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/visual.h"

/*
**	n[0] = x_min
**	n[1] = y_min
**	n[2] = x_max
**	n[3] = y_max
*/

void	compute_shift(t_vis *vis, t_lemin *lemin)
{
	int		n[4];
	t_list	*lst;

	n[0] = MAX_INT;
	n[1] = MAX_INT;
	n[2] = MIN_INT;
	n[3] = MIN_INT;
	lst = lemin->list;
	while (lst)
	{
		n[0] = ft_nummin(n[0], lst->x);
		n[1] = ft_nummin(n[1], lst->y);
		n[2] = ft_nummax(n[2], lst->x);
		n[3] = ft_nummax(n[3], lst->y);
		lst = lst->next;
	}
	vis->x_shift = (WIDTH - (ft_numabs(n[2] - n[0]) + ROOM_SIZE)) / 2 - n[0];
	vis->y_shift = (HEIGHT - (ft_numabs(n[3] - n[1]) + ROOM_SIZE)) / 2 - n[1];
	if (vis->x_shift + n[0] < 0 || vis->y_shift + n[1] < 0)
		free_n_close(vis);
}
