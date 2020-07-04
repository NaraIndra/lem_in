/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_connections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstygg <mstygg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 20:56:50 by jstokes           #+#    #+#             */
/*   Updated: 2019/10/21 22:57:51 by mstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void		find_name_n_replace(t_lemin *lemin, t_list *lst, char *name)
{
	t_list	*tmp;

	tmp = lemin->list;
	while (tmp)
	{
		if (ft_strcmp(tmp->content, name) == 0)
		{
			lst->content = tmp->content;
			return ;
		}
		tmp = tmp->next;
	}
}

void		add_connection(t_lemin *lemin, char **names, int fd)
{
	t_list	*new;
	t_cont	*cont;

	cont = hm_find(lemin->map, *(names + 1));
	if (!check_link(cont->list, *names) ||
		ft_strcmp(*(names), *(names + 1)) == 0)
		strspl_cl_n_err(names, lemin, NULL, fd);
	if (!(new = lst_create(*names, ft_strlen(*names) + 1)))
		strspl_cl_n_err(names, lemin, NULL, fd);
	find_name_n_replace(lemin, new, *names);
	lst_push_back(&(cont->list), new);
	cont = hm_find(lemin->map, *names);
	if (!(new = lst_create(*(names + 1), ft_strlen(*(names + 1)) + 1)))
		strspl_cl_n_err(names, lemin, NULL, fd);
	find_name_n_replace(lemin, new, *(names + 1));
	lst_push_back(&(cont->list), new);
}

void		analize_connection(t_lemin *lemin, int fd, char **tmp)
{
	size_t	i;
	char	**names;

	i = 0;
	if (!lemin || !tmp || !(*tmp) || !ft_strchr(*tmp, '-'))
		strspl_cl_n_err(tmp, lemin, NULL, fd);
	while (tmp && *(tmp + i))
		i++;
	if (i != 1)
		strspl_cl_n_err(tmp, lemin, NULL, fd);
	if (!(names = ft_strsplit(*tmp, '-')))
		strspl_cl_n_err(tmp, lemin, NULL, fd);
	ft_strsplitdel(&tmp);
	i = 0;
	while (*(names + i))
		i++;
	if (i != 2)
		strspl_cl_n_err(names, lemin, NULL, fd);
	if (check_link(lemin->list, *names) ||
		check_link(lemin->list, *(names + 1)))
		strspl_cl_n_err(names, lemin, NULL, fd);
	add_connection(lemin, names, fd);
	ft_strsplitdel(&names);
}

void		get_connections(t_lemin *lemin, int fd, char **tmp, int j)
{
	int		i;
	char	*line;

	analize_connection(lemin, fd, tmp);
	line = NULL;
	while ((i = get_next_line(fd, &line)) > 0)
	{
		if (line && j == 1 && ft_strcmp("", line) == 0)
			return (ft_strdel(&line));
		add_line_to_input(lemin, &line, fd);
		line = lemin->input->last->content;
		if (line && *line == '#' && *(line + 1) == '#')
			analize_command(lemin, ft_strsplitest(line), fd);
		else if (line && *line != '#')
		{
			tmp = ft_strsplitest(line);
			i = 0;
			while (tmp && *(tmp + i))
				i++;
			if (i != 1)
				strspl_cl_n_err(tmp, lemin, NULL, fd);
			analize_connection(lemin, fd, tmp);
		}
		line = NULL;
	}
}
