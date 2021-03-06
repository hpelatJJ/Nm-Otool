/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wstrlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpelat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/14 14:38:25 by hpelat            #+#    #+#             */
/*   Updated: 2017/02/14 14:38:26 by hpelat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"

static size_t	ft_wcharlen(wchar_t wchar)
{
	unsigned int	c;
	int				bits;

	c = 2147483648;
	bits = 32;
	while ((c & wchar) == 0)
	{
		bits--;
		c = c >> 1;
	}
	if (bits > 7 && bits <= 11)
		return (2);
	if (bits > 11 && bits <= 16)
		return (3);
	if (bits > 16)
		return (4);
	return (1);
}

size_t			ft_wstrlen(wchar_t *wstr)
{
	int		i;
	int		wlen;

	i = -1;
	wlen = 0;
	while (wstr[++i])
		wlen += ft_wcharlen(wstr[i]);
	return (wlen);
}
