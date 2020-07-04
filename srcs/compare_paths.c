/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare_paths.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstokes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 22:13:41 by jstokes           #+#    #+#             */
/*   Updated: 2019/10/25 22:13:42 by jstokes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

int		count_value(t_path *path, t_path *tmp)
{
	int		j;

	j = 0;
	while (path != tmp)
	{
		j += (int)(tmp->len - path->len);
		path = path->next;
	}
	return (j);
}

int		*determine_paths_num(t_lemin *lemin)
{
	t_path	*tmp;
	int		i;
	int		tmp_num;
	int		*path_nums;

	if (!(path_nums = (int *)malloc(sizeof(int) * 2 * lemin->ants)))
		clean_n_error(lemin, NULL, 0);
	i = lemin->ants;
	tmp = lemin->paths;
	tmp_num = 1;
	while (i > 0)
	{
		if (tmp && i > count_value(lemin->paths, tmp))
		{
			path_nums[lemin->ants - i] = tmp_num;
			i--;
			tmp_num++;
			tmp = tmp->next;
			continue ;
		}
		tmp = lemin->paths;
		tmp_num = 1;
	}
	return (path_nums);
}

int		count_moves(int *paths_num, t_lemin *lemin)
{
	int		j;
	int		k;

	j = -1;
	k = -1;
	while (++j < lemin->ants)
	{
		if (paths_num[j] == 1)
			k++;
		paths_num[j + lemin->ants] = k;
	}
	j = -1;
	while (++j < lemin->ants)
		paths_num[j + lemin->ants] +=
			get_path_len(lemin->paths, paths_num[j]);
	k = paths_num[lemin->ants];
	j = -1;
	while (++j < lemin->ants)
		k = (paths_num[lemin->ants + j] > k) ?
						(paths_num[lemin->ants + j]) : (k);
	return (k);
}

int		consider_this_case(t_lemin *lemin, int j, int *paths_num)
{
	t_path	*tmp;
	t_path	*prev;

	free(paths_num);
	if (j == 1)
	{
		del_path(&(lemin->paths));
		return (0);
	}
	tmp = lemin->paths;
	while (tmp && tmp->next)
		tmp = tmp->next;
	prev = lemin->paths;
	while (prev && prev->next != tmp)
		prev = prev->next;
	prev->next = NULL;
	del_path(&tmp);
	return (0);
}

int		compare_paths(t_lemin *lemin, int j)
{
	int		*paths_num;
	int		paths_moves_num;

	if (is_sorted(lemin->paths) == 0)
		sort_paths(&(lemin->paths));
	paths_num = determine_paths_num(lemin);
	paths_moves_num = count_moves(paths_num, lemin);
	if (lemin->moves_num < 0)
	{
		lemin->moves_num = paths_moves_num;
		lemin->for_ants_moves = paths_num;
		return (1);
	}
	if (paths_moves_num >= lemin->moves_num)
		return (consider_this_case(lemin, j, paths_num));
	lemin->moves_num = paths_moves_num;
	free(lemin->for_ants_moves);
	lemin->for_ants_moves = paths_num;
	if (j == 0)
		return (1);
	del_path(&(lemin->best_paths));
	lemin->best_paths = lemin->paths;
	lemin->paths = NULL;
	return (1);
}
