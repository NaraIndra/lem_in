/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rooms.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstygg <mstygg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 17:43:58 by jstokes           #+#    #+#             */
/*   Updated: 2019/10/21 22:40:25 by mstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

int			check_coors(int x, int y, t_list *list)
{
	while (list)
	{
		if (list->x == x && list->y == y)
			return (0);
		list = list->next;
	}
	return (1);
}

t_list		*analize_room(t_lemin *lemin, char **tmp, int fd)
{
	int		i;
	int		j;
	t_list	*list;

	i = 0;
	if (!tmp || !(*tmp) || **tmp == 'L')
		strspl_cl_n_err(tmp, lemin, NULL, fd);
	while (*(tmp + i))
		i++;
	if (i != 3 || ft_strchr(*tmp, '-') || !check_link(lemin->list, *tmp))
		strspl_cl_n_err(tmp, lemin, NULL, fd);
	i = (**(tmp + 1) == '+' || **(tmp + 1) == '-') ? (1) : (0);
	j = (**(tmp + 2) == '+' || **(tmp + 2) == '-') ? (1) : (0);
	if (!check_str(*(tmp + 1), i, ft_atoi(*(tmp + 1))) ||
		!check_str(*(tmp + 2), j, ft_atoi(*(tmp + 2))) ||
		!check_coors(ft_atoi(*(tmp + 1)), ft_atoi(*(tmp + 2)), lemin->list))
		strspl_cl_n_err(tmp, lemin, NULL, fd);
	if (!(list = lst_create(*tmp, ft_strlen(*tmp) + 1)))
		strspl_cl_n_err(tmp, lemin, NULL, fd);
	list->x = ft_atoi(*(tmp + 1));
	list->y = ft_atoi(*(tmp + 2));
	lst_push_back(&(lemin->list), list);
	return (list);
}

void		add_start_end(t_list *lst, int i, t_lemin *lemin)
{
	if (i == 1)
	{
		lemin->start = lst;
		lemin->start_fl = 1;
	}
	else
	{
		lemin->end = lst;
		lemin->end_fl = 1;
	}
}

void		analize_command(t_lemin *lemin, char **tmp, int fd)
{
	int		i;
	char	*line;

	if (!(*(tmp + 1)) &&
		(ft_strcmp(*tmp + 2, "start") == 0 || ft_strcmp(*tmp + 2, "end") == 0))
	{
		if ((ft_strcmp(*tmp + 2, "start") == 0 && lemin->start_fl) ||
			(ft_strcmp(*tmp + 2, "end") == 0 && lemin->end_fl))
			strspl_cl_n_err(tmp, lemin, NULL, fd);
		i = (ft_strcmp(*tmp + 2, "start") == 0) ? (1) : (2);
		ft_strsplitdel(&tmp);
		if (get_next_line(fd, &line) < 1)
			clean_n_error(lemin, &line, fd);
		tmp = ft_strsplitest(line);
		add_line_to_input(lemin, &line, fd);
		add_start_end(analize_room(lemin, tmp, fd), i, lemin);
		free_part(&tmp);
	}
	ft_strsplitdel(&tmp);
}

char		**get_rooms(t_lemin *lemin, int fd)
{
	char	**tmp;
	char	*line;

	line = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		tmp = ft_strsplitest(line);
		add_line_to_input(lemin, &line, fd);
		if (tmp && *tmp && **tmp == '#')
		{
			if (*(*tmp + 1) == '#')
				analize_command(lemin, tmp, fd);
			else
				ft_strsplitdel(&tmp);
		}
		else if (tmp && *tmp && !(*(tmp + 1)))
			return (tmp);
		else
		{
			analize_room(lemin, tmp, fd);
			free_part(&tmp);
		}
	}
	return (NULL);
}
