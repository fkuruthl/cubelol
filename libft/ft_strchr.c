/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inkahar <inkahar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 11:02:37 by inkahar           #+#    #+#             */
/*   Updated: 2024/12/15 12:55:39 by inkahar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	* ft_strchr(const char *s, int c)
{
	const char		*p;
	unsigned char	ch;

	if (!s)
		return (NULL);
	p = s;
	ch = c;
	while (*p != '\0')
	{
		if (*p == ch)
		{
			return ((char *)p);
		}
		p++;
	}
	if (ch == '\0')
	{
		return ((char *)p);
	}
	return (NULL);
}
