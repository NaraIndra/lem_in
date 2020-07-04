/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orientate_links.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstygg <mstygg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 14:11:51 by jstokes           #+#    #+#             */
/*   Updated: 2019/10/19 21:30:06 by mstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void	make_link_coming_n_del1(t_cont *cont, void *key, t_lemin *lemin)
{
	t_list	*tmp;

	tmp = cont->coming_links;
	while (tmp)
	{
		if (ft_strcmp(key, tmp->content) == 0)
			return ;
		tmp = tmp->next;
	}
	if (!(tmp = ft_lstnew(key, ft_strlen(key) + 1)))
		clean_n_error(lemin, NULL, 0);
	delete_link(cont, key);
	ft_lstadd(&(cont->coming_links), tmp);
}

void	make_link_coming_n_del2(t_cont *cont, void *key, t_lemin *lemin)
{
	t_list	*tmp;

	if (!(tmp = ft_lstnew(key, ft_strlen(key) + 1)))
		clean_n_error(lemin, NULL, 0);
	delete_link(cont, key);
	ft_lstadd(&(cont->coming_links), tmp);
}

void	orientate_links(t_lemin *lemin)
{
	t_list	*tmp;
	t_cont	*cont;
	t_list	*links;
	t_cont	*contlink;
	t_list	*next;

	tmp = lemin->list;
	while (tmp)
	{
		cont = hm_find(lemin->map, tmp->content);
		links = cont->list;
		while (links)
		{
			next = links->next;
			contlink = hm_find(lemin->map, links->content);
			if (cont->bfs_lev < contlink->bfs_lev)
				make_link_coming_n_del1(contlink, tmp->content, lemin);
			else
				make_link_coming_n_del2(cont, links->content, lemin);
			links = next;
		}
		tmp = tmp->next;
	}
}
