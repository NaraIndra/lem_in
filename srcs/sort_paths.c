/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstokes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 14:12:27 by jstokes           #+#    #+#             */
/*   Updated: 2019/10/14 14:12:28 by jstokes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

int		check_verts(t_lemin *lemin)
{
	t_path	*tmp;
	t_list	*lst;

	flush_visits(lemin);
	tmp = lemin->paths;
	while (tmp)
	{
		lst = tmp->list;
		while (lst)
		{
			hm_find(lemin->map, lst->content)->visited += 1;
			lst = lst->next;
		}
		tmp = tmp->next;
	}
	lst = lemin->list;
	while (lst)
	{
		if (hm_find(lemin->map, lst->content)->visited > 1
				&& lst->content != lemin->end->content)
			return (0);
		lst = lst->next;
	}
	return (1);
}

char	is_sorted(t_path *path)
{
	t_path	*tmp;

	if (!path || !(path->next))
		return (1);
	tmp = path;
	while (tmp->next)
	{
		if (tmp->len <= tmp->next->len)
			tmp = tmp->next;
		else
			return (0);
	}
	return (1);
}

void	swap_paths(t_path **paths, t_path **tmp)
{
	t_path	*next;
	t_path	*prev;

	if (*paths == *tmp)
	{
		next = (*tmp)->next->next;
		*paths = (*tmp)->next;
		(*paths)->next = (*tmp);
		(*tmp)->next = next;
		return ;
	}
	prev = *paths;
	while (prev->next != *tmp)
		prev = prev->next;
	next = (*tmp)->next->next;
	prev->next = (*tmp)->next;
	prev->next->next = (*tmp);
	(*tmp)->next = next;
}

void	sort_paths(t_path **path)
{
	t_path	*tmp;
	size_t	len;
	size_t	i;

	len = 0;
	tmp = *path;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	while (len > 0)
	{
		i = -1;
		tmp = *path;
		while (++i < len)
		{
			if (tmp->next && tmp->len > tmp->next->len)
				swap_paths(path, &tmp);
			else
				tmp = tmp->next;
		}
		len--;
	}
}
