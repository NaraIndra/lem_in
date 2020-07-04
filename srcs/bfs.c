/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstygg <mstygg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 21:16:28 by jstokes           #+#    #+#             */
/*   Updated: 2019/10/19 15:33:43 by mstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void	add_keys_to_next_lev(t_lemin *lemin, void *key, t_list **next_lev)
{
	t_list	*new_lst;
	t_list	*lst;

	lst = hm_find(lemin->map, key)->list;
	while (lst)
	{
		if (hm_find(lemin->map, lst->content)->bfs_lev < 0)
		{
			if (!(new_lst = ft_lstnew(lst->content,
								ft_strlen(lst->content) + 1)))
			{
				ft_lstdelstr(next_lev);
				clean_n_error(lemin, NULL, 0);
			}
			ft_lstaddend(next_lev, new_lst);
		}
		lst = lst->next;
	}
}

void	all_other_levels(t_lemin *lemin, t_list *next_lev)
{
	t_list	*tmp_lev;
	t_list	*tmp;
	int		i;

	i = 2;
	tmp_lev = next_lev;
	next_lev = NULL;
	while (tmp_lev)
	{
		tmp = tmp_lev;
		while (tmp)
		{
			if (hm_find(lemin->map, tmp->content)->bfs_lev < 0)
			{
				hm_find(lemin->map, tmp->content)->bfs_lev = i;
				add_keys_to_next_lev(lemin, tmp->content, &next_lev);
			}
			tmp = tmp->next;
		}
		ft_lstdelstr(&tmp_lev);
		tmp_lev = next_lev;
		next_lev = 0;
		i++;
	}
}

void	check_end(t_lemin *lemin)
{
	t_list	*lst;
	t_cont	*cont;

	cont = hm_find(lemin->map, lemin->end->content);
	if (!(cont->list))
		clean_n_error(lemin, NULL, 0);
	lst = cont->list;
	while (lst)
	{
		if (hm_find(lemin->map, lst->content)->bfs_lev > -1)
			return ;
		lst = lst->next;
	}
	clean_n_error(lemin, NULL, 0);
}

void	bfs_indexing(t_lemin *lemin)
{
	t_list	*tmp_lev;
	t_list	*next_lev;
	t_cont	*cont;

	cont = hm_find(lemin->map, lemin->start->content);
	cont->bfs_lev = 0;
	next_lev = NULL;
	hm_find(lemin->map, lemin->end->content)->bfs_lev = 2147483647;
	tmp_lev = cont->list;
	while (tmp_lev)
	{
		if (hm_find(lemin->map, tmp_lev->content)->bfs_lev < 0)
		{
			hm_find(lemin->map, tmp_lev->content)->bfs_lev = 1;
			add_keys_to_next_lev(lemin, tmp_lev->content, &next_lev);
		}
		tmp_lev = tmp_lev->next;
	}
	all_other_levels(lemin, next_lev);
	check_end(lemin);
}
