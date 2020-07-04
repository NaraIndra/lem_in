/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_del.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstokes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 15:47:18 by jstokes           #+#    #+#             */
/*   Updated: 2019/10/27 15:47:19 by jstokes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		hm_del(t_hash_map **map)
{
	t_hash_map		*map_n;
	size_t			i;

	if (!map || !(*map))
		return ;
	map_n = *map;
	i = 0;
	while (i < map_n->arr_size)
	{
		if (map_n->data[i])
			ft_keystr_avl_del(&(map_n->data[i]));
		i++;
	}
	if (map_n->data)
		free(map_n->data);
	map_n->data = NULL;
	free(map_n);
	*map = NULL;
}
