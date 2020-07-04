/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_funcs3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstokes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 22:55:31 by jstokes           #+#    #+#             */
/*   Updated: 2019/10/25 22:55:32 by jstokes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

t_list	*lst_push_back_void(t_list **lst, void *name)
{
	t_list	*new;

	if (!(new = lst_create(name, ft_strlen(name) + 1)))
		return (NULL);
	lst_push_back(lst, new);
	return (*lst);
}

t_list	*lst_push_front_void(t_list **lst, void *name)
{
	t_list	*new;

	if (!(new = lst_create(name, ft_strlen(name) + 1)))
		return (NULL);
	lst_push_front(lst, new);
	return (*lst);
}

void	*lst_pop_front_void(t_list **lst)
{
	char	*name;
	t_list	*tmp;

	tmp = lst_pop_front(lst);
	name = tmp->content;
	lst_del(&tmp);
	return (name);
}

void	*lst_pop_back_void(t_list **lst)
{
	char	*name;
	t_list	*tmp;

	tmp = lst_pop_back(lst);
	name = tmp->content;
	lst_del(&tmp);
	return (name);
}

void	lst_p_b_v_pr(t_list **lst, void *name, t_lemin *lemin)
{
	if (!lst_push_back_void(lst, name))
		clean_n_error(lemin, NULL, 0);
}
