/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_avl_del.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstygg <mstygg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 14:33:59 by mstygg            #+#    #+#             */
/*   Updated: 2019/10/26 16:54:06 by mstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void					ft_keystr_avl_del(t_keystr_avl_t **root_or)
{
	t_keystr_avl_t		*root;

	if (!root_or || !(*root_or))
		return ;
	root = *root_or;
	if (root)
	{
		if (root->left)
			ft_keystr_avl_del(&((*root_or)->left));
		if (root->right)
			ft_keystr_avl_del(&((*root_or)->right));
		if (root->pair)
			free(root->pair);
		if (root)
			free(root);
	}
	*root_or = NULL;
}
