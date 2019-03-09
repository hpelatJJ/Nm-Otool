/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_whichconv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpelat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 13:16:49 by hpelat            #+#    #+#             */
/*   Updated: 2017/02/07 13:16:51 by hpelat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int		ft_whichconv(va_list ap, t_b *b, char *format, t_ptf *ptf)
{
	int		len;
	int		k;

	len = 1;
	k = 0;
	ptf->c = ft_findc(format, &len);
	if (ptf->c == '\0')
		return (len);
	while (ptf->c != g_tab[k].c && g_tab[k].c != 0)
		k++;
	g_tab[k].ptr(ap, b, format + 1);
	return (len);
}
