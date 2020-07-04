/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_funcs1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstokes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 22:55:20 by jstokes           #+#    #+#             */
/*   Updated: 2019/10/25 22:55:22 by jstokes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

t_list		*lst_create(void *content, size_t content_size)
{
	t_list	*new;

	if (!content || content_size < 1 ||
		!(new = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	new->content = content;
	new->content_size = content_size;
	new->last = NULL;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_list		*lst_push_front(t_list **lst, t_list *tmp)
{
	if (!lst || !tmp)
		return (NULL);
	else if (!(*lst))
	{
		tmp->next = NULL;
		tmp->prev = NULL;
		tmp->last = tmp;
		*lst = tmp;
	}
	else
	{
		tmp->prev = NULL;
		tmp->next = *lst;
		(*lst)->prev = tmp;
		tmp->last = (*lst)->last;
		(*lst)->last = NULL;
		(*lst) = tmp;
	}
	return (*lst);
}

t_list		*lst_push_back(t_list **lst, t_list *tmp)
{
	if (!lst || !tmp)
		return (NULL);
	else if (!(*lst))
	{
		*lst = tmp;
		tmp->next = NULL;
		tmp->prev = NULL;
		tmp->last = tmp;
	}
	else
	{
		(*lst)->last->next = tmp;
		tmp->prev = (*lst)->last;
		tmp->next = NULL;
		tmp->last = NULL;
		(*lst)->last = tmp;
	}
	return (*lst);
}

t_list		*lst_pop_front(t_list **lst)
{
	t_list	*tmp;
	t_list	*next;

	if (!lst || !(*lst))
		return (NULL);
	if ((*lst)->last == (*lst))
	{
		tmp = *lst;
		tmp->last = NULL;
		*lst = NULL;
		return (tmp);
	}
	tmp = *lst;
	next = tmp->next;
	next->last = tmp->last;
	next->prev = NULL;
	tmp->next = NULL;
	tmp->last = NULL;
	*lst = next;
	return (tmp);
}

t_list		*lst_pop_back(t_list **lst)
{
	t_list	*tmp;

	if (!lst || !(*lst))
		return (NULL);
	if ((*lst)->last == *lst)
	{
		tmp = (*lst);
		tmp->last = NULL;
		*lst = NULL;
		return (tmp);
	}
	tmp = (*lst)->last;
	(*lst)->last = tmp->prev;
	tmp->prev->next = NULL;
	tmp->prev = NULL;
	return (tmp);
}
