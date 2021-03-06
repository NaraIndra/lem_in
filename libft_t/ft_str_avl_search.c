/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_avl_search.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstygg <mstygg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 21:23:27 by mstygg            #+#    #+#             */
/*   Updated: 2019/10/26 16:57:30 by mstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_keystr_avl_t	*ft_keystr_avl_search(t_keystr_avl_t *p, void *key)
{
	if (p)
		while (p)
		{
			if (CMP(p->pair->key, key) < 0)
				p = p->right;
			else if (CMP(p->pair->key, key) > 0)
				p = p->left;
			else
				return (p);
		}
	return (NULL);
}
