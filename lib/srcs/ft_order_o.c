/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_order_o.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpelat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/13 19:25:43 by hpelat            #+#    #+#             */
/*   Updated: 2017/02/13 19:25:45 by hpelat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"

void	ft_order_o(t_b *b, t_flags flags, char *str, char *rec)
{
	if (flags.zer == 1 && flags.diez == 1 && flags.nbr == 1)
	{
		ft_buffill(b, "0");
		b->len += 1;
	}
	if (flags.mfw > 0)
		if (!ft_strchr(str, '-'))
			ft_do_mfw(b, flags);
	if (flags.pr > 0)
		ft_do_prec(b, &flags, str);
	if (flags.zer == 0 && flags.diez == 1 && flags.pr < 1 && flags.nbr == 1)
	{
		ft_buffill(b, "0");
		b->len += 1;
	}
	ft_buffill(b, rec);
	if (flags.mfw > 0)
		if (ft_strchr(str, '-'))
			ft_do_mfw(b, flags);
}
