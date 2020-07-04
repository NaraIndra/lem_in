/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_moves.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstokes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 23:09:51 by jstokes           #+#    #+#             */
/*   Updated: 2019/10/25 23:09:52 by jstokes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void	process_ant_n_move(t_lemin *lemin, char *elem, size_t j)
{
	t_list	*new;
	int		num;
	int		i;

	i = 0;
	num = ft_atoi(elem + 1);
	while (elem[i] && elem[i] != '-')
		i++;
	if (!elem[i])
		clean_n_error(lemin, NULL, 0);
	i++;
	if (!(new = ft_lstnew(elem + i, ft_strlen(elem + i) + 1)))
		clean_n_error(lemin, NULL, 0);
	new->x = (int)j;
	ft_lstaddend(lemin->moves + num - 1, new);
}

void	init_moves(t_lemin *lemin)
{
	t_list	**moves;
	t_list	**moves_start;
	t_list	*start;
	int		i;

	if (!(moves = (t_list **)malloc(sizeof(t_list *) * lemin->ants)))
		clean_n_error(lemin, NULL, 0);
	if (!(moves_start = (t_list **)malloc(sizeof(t_list *) * lemin->ants)))
		clean_n_error(lemin, NULL, 0);
	i = -1;
	while (++i < lemin->ants)
	{
		if (!(start = ft_lstnew(lemin->start->content,
			ft_strlen(lemin->start->content) + 1)))
			clean_n_error(lemin, NULL, 0);
		*(moves + i) = start;
		*(moves_start + i) = start;
	}
	lemin->moves = moves;
	lemin->moves_start = moves_start;
}

void	init_start_move(t_list **moves, int ants)
{
	int		i;
	t_list	*tmp;

	i = -1;
	while (++i < ants)
	{
		tmp = *(moves + i);
		tmp->x = tmp->next->x - 1;
	}
}

void	get_moves(t_lemin *lemin)
{
	size_t	i;
	int		j;
	char	**tmp;
	char	*line;

	ft_lstdelstr(&(lemin->input));
	i = 0;
	init_moves(lemin);
	while (get_next_line(0, &line) > 0)
	{
		tmp = ft_strsplitest(line);
		ft_strdel(&line);
		j = 0;
		while (*(tmp + j))
		{
			process_ant_n_move(lemin, *(tmp + j), i);
			j++;
		}
		ft_strsplitdel(&tmp);
		i++;
	}
	lemin->moves_num = i;
	init_start_move(lemin->moves, lemin->ants);
}
