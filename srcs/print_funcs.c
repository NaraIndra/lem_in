/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstokes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 17:45:05 by jstokes           #+#    #+#             */
/*   Updated: 2019/10/09 17:45:07 by jstokes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void	print_usage(void)
{
	ft_printf("usage: ./lem-in < file_name\n");
	ft_printf("       ./lem-in file_name\n");
	exit(0);
}

void	print_error(void)
{
	ft_printf("ERROR\n");
	exit(0);
}

void	print_rooms_n_links(t_lemin *lemin)
{
	t_cont	*cont;
	t_list	*tmp;
	t_list	*it;

	tmp = lemin->list;
	while (tmp)
	{
		cont = hm_find(lemin->map, tmp->content);
		it = cont->list;
		ft_printf("key = %s, bfs_lev = %d\n", tmp->content, cont->bfs_lev);
		ft_printf("kid = %s\n", cont->kid);
		ft_printf("cur_sour = %s\n", cont->parent);
		while (it)
		{
			ft_printf("connections out: %s\n", it->content);
			it = it->next;
		}
		ft_printf("\n");
		tmp = tmp->next;
	}
}

void	print_path(t_path *path)
{
	t_list	*lst;

	lst = path->list;
	while (lst)
	{
		ft_printf("%s ", lst->content);
		lst = lst->next;
	}
	ft_printf("\n");
}

void	print_all_paths(t_path *path)
{
	while (path)
	{
		print_path(path);
		path = path->next;
	}
}
