/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_order.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpelat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/13 15:21:16 by hpelat            #+#    #+#             */
/*   Updated: 2017/02/13 15:21:17 by hpelat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"

void	ft_order_d(t_b *b, t_flags flags, char *str, char *rec)
{
	if (flags.zer == 1)
		ft_plusminus(b, flags);
	if (flags.mfw > 0)
		if (!ft_strchr(str, '-'))
			ft_do_mfw(b, flags);
	if (flags.zer == 0)
		ft_plusminus(b, flags);
	if (flags.pr > 0)
		ft_do_prec(b, &flags, str);
	ft_buffill(b, rec);
	if (flags.mfw > 0)
		if (ft_strchr(str, '-'))
			ft_do_mfw(b, flags);
}
