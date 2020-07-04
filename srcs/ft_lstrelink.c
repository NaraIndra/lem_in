/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstrelink.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstokes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 14:11:07 by jstokes           #+#    #+#             */
/*   Updated: 2019/10/14 14:11:08 by jstokes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

t_list	*ft_lstrelink(t_list *prev, t_list *tmp)
{
	if (!prev || !tmp || prev->next != tmp)
		return (NULL);
	prev->next = tmp->next;
	tmp->next = NULL;
	return (tmp);
}
