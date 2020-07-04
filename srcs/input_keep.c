/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_keep.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstokes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 21:52:36 by jstokes           #+#    #+#             */
/*   Updated: 2019/10/25 21:52:37 by jstokes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void	add_line_to_input(t_lemin *lemin, char **line, int fd)
{
	t_list	*new;

	if (!(new = lst_create(*line, ft_strlen(*line) + 1)))
	{
		ft_strdel(line);
		clean_n_error(lemin, NULL, fd);
	}
	lst_push_back(&(lemin->input), new);
	*line = NULL;
}

void	print_input(t_lemin *lemin)
{
	t_list	*lst;

	lst = lemin->input;
	while (lst)
	{
		ft_printf("%s\n", lst->content);
		lst = lst->next;
	}
	ft_printf("\n");
	ft_lstdelstr(&(lemin->input));
}
