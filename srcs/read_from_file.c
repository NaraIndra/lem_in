/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_from_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstokes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 17:43:42 by jstokes           #+#    #+#             */
/*   Updated: 2019/10/09 17:43:43 by jstokes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

t_lemin	*read_from_file(char *str)
{
	char	buf[1];
	int		fd;

	fd = open(str, O_RDONLY);
	if (fd < 0 || read(fd, buf, 0) < 0)
		print_error();
	return (read_from_fd(fd, 0));
}
