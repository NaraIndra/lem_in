/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_funcs2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstokes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 22:55:25 by jstokes           #+#    #+#             */
/*   Updated: 2019/10/25 22:55:26 by jstokes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

t_list	*lst_relink(t_list *tmp)
{
	t_list	*prev;
	t_list	*next;

	prev = tmp->prev;
	next = tmp->next;
	prev->next = next;
	next->prev = prev;
	tmp->next = NULL;
	tmp->prev = NULL;
	return (tmp);
}

t_list	*lst_find_elem(t_list *src, void *name)
{
	t_list	*tmp;

	if (!name || !src)
		return (NULL);
	tmp = src;
	while (tmp)
	{
		if (tmp->content == name)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void	lst_move_from_to(t_list **src, t_list **dst, void *name)
{
	t_list	*tmp;

	if (!src || !dst || !name)
		return ;
	tmp = lst_find_elem(*dst, name);
	if (tmp)
		return ;
	tmp = lst_find_elem(*src, name);
	if (!tmp)
		return ;
	if (!(tmp->prev))
		tmp = lst_pop_front(src);
	else if (!(tmp->next))
		tmp = lst_pop_back(src);
	else
		tmp = lst_relink(tmp);
	lst_push_back(dst, tmp);
}

void	lst_del(t_list **lst)
{
	if (lst && *lst)
	{
		lst_del(&((*lst)->next));
		free(*lst);
		*lst = NULL;
	}
}

void	lst_move_all_from_to(t_list **src, t_list **dst)
{
	t_list	*tmp;

	tmp = lst_pop_front(src);
	while (tmp)
	{
		lst_push_back(dst, tmp);
		tmp = lst_pop_front(src);
	}
}
