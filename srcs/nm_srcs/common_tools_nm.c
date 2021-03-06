/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_tools_nm.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpelat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 14:30:21 by hpelat            #+#    #+#             */
/*   Updated: 2019/02/12 14:30:25 by hpelat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_nm.h>

int			scmp(const char *s1, const char *s2)
{
	if (!s1)
		return (s2 ? 1 : 0);
	if (!s2)
		return (-1);
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

int			sncmp(const char *s1, const char *s2, size_t size)
{
	if (!s1)
		return (s2 ? 1 : 0);
	if (!s2)
		return (-1);
	while (*s1 && *s2 && --size)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

void		*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*str;
	char	*desti;

	i = 0;
	desti = (char*)dst;
	str = (char*)src;
	while (i < n)
	{
		desti[i] = str[i];
		i++;
	}
	return (desti);
}
