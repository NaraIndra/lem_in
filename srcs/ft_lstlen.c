/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstokes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 14:09:14 by jstokes           #+#    #+#             */
/*   Updated: 2019/10/03 14:09:15 by jstokes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

size_t	ft_lstlen(t_list *alst)
{
	size_t	len;

	if (!alst)
		return (0);
	len = 0;
	while (alst)
	{
		alst = alst->next;
		len++;
	}
	return (len);
}
