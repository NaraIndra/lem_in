/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants_location.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstokes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 21:32:42 by jstokes           #+#    #+#             */
/*   Updated: 2019/10/26 21:32:44 by jstokes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/visual.h"

void	init_ants_location(t_lemin *lemin)
{
	int		i;

	i = -1;
	while (++i < lemin->ants)
		*(lemin->moves + i) = *(lemin->moves_start + i);
}

void	update_ants_location(t_lemin *lemin, t_vis *vis)
{
	int		i;

	i = -1;
	while (++i < lemin->ants)
	{
		if ((*(lemin->moves + i))->next &&
				(*(lemin->moves + i))->x <= vis->move)
			*(lemin->moves + i) = (*(lemin->moves + i))->next;
	}
}
