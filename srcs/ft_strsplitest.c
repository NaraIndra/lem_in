/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstokes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 22:46:30 by jstokes           #+#    #+#             */
/*   Updated: 2018/12/08 16:08:45 by jstokes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static size_t	str_num(char const *s)
{
	size_t	len;
	size_t	num;
	size_t	i;
	size_t	j;

	i = 0;
	num = 0;
	len = ft_strlen(s);
	while (i < len)
	{
		if (s[i] == ' ' || s[i] == '\t')
			i++;
		else
		{
			j = 0;
			while (s[i + j] != ' ' && s[i + j] != '\t' && s[i + j] != '\0')
				j++;
			if (j > 0)
				num++;
			i += j;
		}
	}
	return (num + 1);
}

static char		*next_str(char *s)
{
	char	*str;
	size_t	i;

	i = 0;
	while (s[i] != '\0' && s[i] != ' ' && s[i] != '\t')
		i++;
	if (!(str = (char *)malloc(i + 1)))
		return (NULL);
	str[i] = '\0';
	while (--i != 0)
		str[i] = s[i];
	str[i] = s[i];
	return (str);
}

static void		freearr(char **arr, size_t j)
{
	while (j != 0)
	{
		free(arr[j]);
		j--;
	}
	free(arr[j]);
	free(arr);
}

static char		**exit_func(char **starr, size_t j)
{
	char	*str;

	str = 0;
	starr[j] = str;
	return (starr);
}

char			**ft_strsplitest(char const *s)
{
	size_t	len;
	size_t	i;
	size_t	j;
	char	**starr;

	if (!s ||
		!(starr = (char **)malloc(sizeof(char *) * str_num(s))))
		return (NULL);
	i = -1;
	j = 0;
	len = ft_strlen(s);
	while (++i < len)
		if (s[i] != ' ' && s[i] != '\t')
		{
			starr[j] = next_str((char *)s + i);
			if (!starr[j])
			{
				freearr(starr, j - 1);
				return (NULL);
			}
			i += ft_strlen(starr[j]) - 1;
			j++;
		}
	return (exit_func(starr, j));
}
