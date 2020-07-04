/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstokes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 17:44:05 by jstokes           #+#    #+#             */
/*   Updated: 2019/10/09 17:44:07 by jstokes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

t_lemin		*init_lemin(int fd)
{
	t_lemin	*lemin;

	if (!(lemin = (t_lemin *)malloc(sizeof(t_lemin))))
	{
		close(fd);
		print_error();
	}
	lemin->map = NULL;
	lemin->start = NULL;
	lemin->end = NULL;
	lemin->list = NULL;
	lemin->deleted_rooms = NULL;
	lemin->ants = 0;
	lemin->end_fl = 0;
	lemin->rooms = 0;
	lemin->start_fl = 0;
	lemin->tmp_bfs_lev = NULL;
	lemin->next_bfs_lev = NULL;
	lemin->paths = NULL;
	lemin->input = NULL;
	lemin->best_paths = NULL;
	lemin->paths_num = NULL;
	lemin->moves_num = -1;
	lemin->for_ants_moves = NULL;
	return (lemin);
}

int			check_str(char *str, int j, int num)
{
	int		k;
	int		tmp;
	int		ord;

	k = 1;
	tmp = num;
	ord = 1;
	while (tmp / 10)
	{
		k++;
		ord *= 10;
		tmp /= 10;
	}
	tmp = (num < 0 && str[0] == '-' && j > 0) ? (-1) : (1);
	while (str[j] && k-- > 0)
	{
		if (str[j] != (num / ord) * tmp + '0')
			return (0);
		j++;
		num = num % ord;
		ord /= 10;
	}
	if (str[j] != '\0' || k > 0)
		return (0);
	return (1);
}

int			check_link(t_list *lst, char *name)
{
	while (lst)
	{
		if (name && ft_strcmp(lst->content, name) == 0)
			return (0);
		lst = lst->next;
	}
	return (1);
}
