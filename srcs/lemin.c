/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstokes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 20:42:27 by jstokes           #+#    #+#             */
/*   Updated: 2019/10/25 20:42:29 by jstokes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

int		main(int argc, char **argv)
{
	t_lemin	*lemin;

	lemin = NULL;
	if (argc > 2)
		print_usage();
	else if (argc == 2)
		lemin = read_from_file(*(argv + 1));
	else
		lemin = read_from_fd(0, 0);
	work_with_map(lemin);
	print_input(lemin);
	print_solution(lemin);
	clean_lemin(&lemin);
	return (0);
}
