/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplitdel.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstokes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 13:58:48 by jstokes           #+#    #+#             */
/*   Updated: 2019/10/03 13:58:51 by jstokes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void	ft_strsplitdel(char ***arr)
{
	int		j;

	if (arr && *arr)
	{
		j = 0;
		while (*(*arr + j))
		{
			free(*(*arr + j));
			*(*arr + j) = NULL;
			j++;
		}
		free(*arr);
		*arr = NULL;
	}
}
