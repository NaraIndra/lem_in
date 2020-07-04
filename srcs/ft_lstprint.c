/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstokes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 14:10:51 by jstokes           #+#    #+#             */
/*   Updated: 2019/10/14 14:10:53 by jstokes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void	ft_lstprint(t_list *lst)
{
	while (lst)
	{
		ft_printf("%s ", lst->content);
		lst = lst->next;
	}
	ft_printf("\n");
}
