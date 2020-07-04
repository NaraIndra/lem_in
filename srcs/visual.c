/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstokes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 21:04:01 by jstokes           #+#    #+#             */
/*   Updated: 2019/10/26 21:04:02 by jstokes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/visual.h"

int		main(int argc, char **argv)
{
	t_vis		*vis;
	t_lemin		*lemin;

	if (argc == 1 && argv && *argv)
	{
		if (!(lemin = read_from_fd(0, 1)))
			print_error();
		vis = create_vis();
		compute_shift(vis, lemin);
		init_vis(vis);
		draw(lemin, vis);
		clean_lemin(&lemin);
		vis_clean(&vis);
	}
	else
		ft_putendl(VIS_USAGE);
	return (0);
}
