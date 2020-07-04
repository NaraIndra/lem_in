/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_solution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstokes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 15:04:14 by jstokes           #+#    #+#             */
/*   Updated: 2019/10/26 15:04:15 by jstokes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

t_list	**get_paths(t_lemin *lemin, int *arr)
{
	t_list	**ants_paths;
	t_path	*path;
	int		k;
	int		j;

	j = -1;
	if (!(ants_paths = (t_list **)malloc(sizeof(t_list *) * lemin->ants)))
		clean_n_error(lemin, NULL, 0);
	while (++j < lemin->ants)
	{
		path = lemin->best_paths;
		k = 0;
		while (++k < arr[j])
			path = path->next;
		*(ants_paths + j) = path->list;
	}
	return (ants_paths);
}

void	print_line(t_list **ants_paths, int i, t_lemin *lemin, int *arr)
{
	int		j;

	j = -1;
	while (++j < lemin->ants)
	{
		if (arr[j + lemin->ants] > i)
			break ;
		if (ants_paths[j] && j + 1 < lemin->ants &&
			arr[j + lemin->ants + 1] <= i)
			ft_printf("L%d-%s ", j + 1, ants_paths[j]->content);
		else if (ants_paths[j] && (j + 1 == lemin->ants
			|| arr[j + lemin->ants + 1] > i))
			ft_printf("L%d-%s", j + 1, ants_paths[j]->content);
		if (ants_paths[j])
			ants_paths[j] = ants_paths[j]->next;
	}
	ft_printf("\n");
}

void	print_solution(t_lemin *lemin)
{
	int		i;
	int		*arr;
	t_list	**ants_paths;

	i = -1;
	arr = lemin->for_ants_moves;
	while (++i < lemin->ants)
		arr[i + lemin->ants] -= get_path_len(lemin->best_paths, arr[i]);
	ants_paths = get_paths(lemin, arr);
	i = -1;
	while (++i < lemin->moves_num)
		print_line(ants_paths, i, lemin, arr);
	free(ants_paths);
}
