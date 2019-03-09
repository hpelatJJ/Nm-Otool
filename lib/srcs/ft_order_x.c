/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_order_x.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpelat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/13 19:13:17 by hpelat            #+#    #+#             */
/*   Updated: 2017/02/13 19:13:18 by hpelat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"

void	ft_order_x(t_b *b, t_flags flags, char *str, char *rec)
{
	if (flags.zer == 1 && flags.diez == 2 && flags.nbr == 1)
	{
		(ft_strchr(str, 'X') ? ft_buffill(b, "0X") : ft_buffill(b, "0x"));
		b->len += 2;
	}
	if (flags.mfw > 0)
		if (!ft_strchr(str, '-'))
			ft_do_mfw(b, flags);
	if (flags.pr > 0)
		ft_do_prec(b, &flags, str);
	if (flags.zer == 0 && flags.diez == 2 && flags.nbr == 1)
	{
		(ft_strchr(str, 'X') ? ft_buffill(b, "0X") : ft_buffill(b, "0x"));
		b->len += 2;
	}
	ft_buffill(b, rec);
	if (flags.mfw > 0)
		if (ft_strchr(str, '-'))
			ft_do_mfw(b, flags);
}
