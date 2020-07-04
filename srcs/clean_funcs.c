/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstokes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 17:43:20 by jstokes           #+#    #+#             */
/*   Updated: 2019/10/09 17:43:22 by jstokes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void	check_other_things(t_lemin **lemin)
{
	if ((*lemin)->for_ants_moves)
		free((*lemin)->for_ants_moves);
}

void	clean_lemin(t_lemin **lemin)
{
	if (lemin && *lemin)
	{
		if ((*lemin)->map)
			clean_all_cont(*lemin);
		hm_del(&((*lemin)->map));
		if ((*lemin)->list)
			ft_lstdelstr(&((*lemin)->list));
		if ((*lemin)->tmp_bfs_lev)
			ft_lstdelstr(&((*lemin)->tmp_bfs_lev));
		if ((*lemin)->next_bfs_lev)
			ft_lstdelstr(&((*lemin)->next_bfs_lev));
		if ((*lemin)->input)
			ft_lstdelstr(&((*lemin)->input));
		if ((*lemin)->deleted_rooms)
			ft_lstdelstr(&((*lemin)->deleted_rooms));
		if ((*lemin)->paths)
			del_path(&((*lemin)->paths));
		if ((*lemin)->best_paths)
			del_path(&((*lemin)->best_paths));
		check_other_things(lemin);
		free(*lemin);
		*lemin = NULL;
	}
}

void	clean_n_error(t_lemin *lemin, char **mem, int fd)
{
	char	*line;

	if (mem && *mem)
	{
		free(*mem);
		*mem = NULL;
	}
	while (fd > 0 && get_next_line(fd, &line) > 0)
		ft_strdel(&line);
	if (fd > 0)
		close(fd);
	clean_lemin(&lemin);
	print_error();
}

void	strspl_cl_n_err(char **tmp, t_lemin *lemin, char **mem, int fd)
{
	ft_strsplitdel(&tmp);
	clean_n_error(lemin, mem, fd);
}

void	free_part(char ***tmp)
{
	if (!tmp && !(*tmp))
		return ;
	if (*(*tmp + 1))
		free(*(*tmp + 1));
	if (*(tmp + 2))
		free(*(*tmp + 2));
	free(*tmp);
	*tmp = NULL;
}
