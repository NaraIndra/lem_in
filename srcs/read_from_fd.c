/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_from_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstokes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 17:45:35 by jstokes           #+#    #+#             */
/*   Updated: 2019/10/09 17:45:36 by jstokes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

char		*check_for_com(t_lemin *lemin, int fd, char **line)
{
	char	*str;

	if (!line || !(*line))
		return (NULL);
	str = *line;
	while (*str == '#')
	{
		if (*(str + 1) == '#' &&
			(ft_strcmp(str + 2, "start") == 0 ||
				ft_strcmp(str + 2, "end") == 0))
		{
			ft_strdel(&str);
			return (NULL);
		}
		add_line_to_input(lemin, &str, fd);
		if (get_next_line(fd, &str) < 1)
			return (NULL);
	}
	return (str);
}

void		get_ants(t_lemin *lemin, int fd)
{
	int		i;
	char	*line;
	char	**tmp;

	line = NULL;
	if ((get_next_line(fd, &line)) < 1)
		clean_n_error(lemin, &line, fd);
	if (!(line = check_for_com(lemin, fd, &line)))
		clean_n_error(lemin, &line, fd);
	tmp = ft_strsplitest(line);
	if (!tmp || !(*tmp) || ((lemin->ants = ft_atoi(*tmp)) < 1))
		strspl_cl_n_err(tmp, lemin, &line, fd);
	i = 0;
	while (tmp && *(tmp + i))
		i++;
	if (i != 1)
		strspl_cl_n_err(tmp, lemin, NULL, fd);
	i = (**tmp == '+' || **tmp == '-') ? (1) : (0);
	if (!(check_str(line, i, lemin->ants)))
		strspl_cl_n_err(tmp, lemin, &line, fd);
	add_line_to_input(lemin, &line, fd);
	ft_strsplitdel(&tmp);
}

void		move_list_to_map(t_lemin *lemin, int fd, char **tmp)
{
	t_list		*list;
	t_cont		*cont;

	list = lemin->list;
	while (list)
	{
		if (!(cont = create_cont(list->x, list->y)))
			strspl_cl_n_err(tmp, lemin, NULL, fd);
		if (!hm_put(&(lemin->map), list->content, cont))
			strspl_cl_n_err(tmp, lemin, NULL, fd);
		list = list->next;
	}
}

t_lemin		*read_from_fd(int fd, int i)
{
	char		**tmp;
	t_lemin		*lemin;

	lemin = init_lemin(fd);
	get_ants(lemin, fd);
	tmp = get_rooms(lemin, fd);
	if (!tmp || !(*tmp) || !ft_strchr(*tmp, '-'))
		strspl_cl_n_err(tmp, lemin, NULL, fd);
	if (!lemin->start_fl || !lemin->end_fl ||
			lemin->start == lemin->end)
		strspl_cl_n_err(tmp, lemin, NULL, fd);
	lemin->rooms = ft_lstlen(lemin->list);
	if (!(lemin->map = createhashmap(lemin->rooms)))
		strspl_cl_n_err(tmp, lemin, NULL, fd);
	move_list_to_map(lemin, fd, tmp);
	get_connections(lemin, fd, tmp, i);
	if (i == 1)
		get_moves(lemin);
	if (fd > 0)
		close(fd);
	return (lemin);
}
