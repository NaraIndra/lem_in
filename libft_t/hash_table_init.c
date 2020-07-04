/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstygg <mstygg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 23:42:54 by mstygg            #+#    #+#             */
/*   Updated: 2019/10/26 16:22:04 by mstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

LL			hashcode(U_CHAR *str)
{
	ULL		hash;
	int		c;

	c = 0;
	hash = HASH_CONST;
	while ((c = (int)*str++))
		hash = ((hash << 5) + hash) ^ c;
	return (hash);
}

t_hash_map	*createhashmap(size_t vertices_num)
{
	t_hash_map		*new_map;
	size_t			i;

	i = 0;
	if (!(new_map = (t_hash_map *)malloc(sizeof(t_hash_map))))
		return (NULL);
	if (!(new_map->data =
		(t_keystr_avl_t **)malloc(vertices_num * sizeof(t_keystr_avl_t*))))
		return (NULL);
	while (i < vertices_num)
		new_map->data[i++] = NULL;
	new_map->arr_size = vertices_num;
	new_map->map_size = 0;
	return (new_map);
}

int			push_to_map(t_hash_map **map, t_pair *pair)
{
	LL				index;
	t_hash_map		*map_n;

	map_n = *map;
	index = hashcode((U_CHAR*)pair->key) % map_n->arr_size;
	if (!(map_n->data[index] = ft_keystr_avl_insert(map_n->data[index], pair)))
		return (0);
	++map_n->map_size;
	return (1);
}

int			hm_put(t_hash_map **map, void *key, t_cont *content)
{
	t_pair	*pair;

	pair = NULL;
	if (!(key))
		return (0);
	if (!(pair = malloc(sizeof(t_pair))))
		return (0);
	pair->key = key;
	pair->content = content;
	return (push_to_map(map, pair));
}

t_cont		*hm_find(t_hash_map *map, void *key)
{
	LL				index;
	t_keystr_avl_t	*avl_tmp;

	index = 0;
	if (!(key))
		return (NULL);
	index = hashcode((U_CHAR*)key) % map->arr_size;
	if (!(map->data[index]))
		return (NULL);
	avl_tmp = ft_keystr_avl_search(map->data[index], key);
	if (!(avl_tmp))
		return (NULL);
	return (avl_tmp->pair->content);
}
