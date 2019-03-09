/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_plusminus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpelat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/13 18:50:20 by hpelat            #+#    #+#             */
/*   Updated: 2017/02/13 18:50:22 by hpelat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"

void	ft_plusminus(t_b *b, t_flags flags)
{
	if (flags.pl == 1)
	{
		ft_buffill(b, "+");
		b->len += 1;
	}
	else if (flags.min == 1)
	{
		ft_buffill(b, "-");
		b->len += 1;
	}
}
