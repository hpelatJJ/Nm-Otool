/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_space.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpelat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 15:17:52 by hpelat            #+#    #+#             */
/*   Updated: 2017/02/15 15:17:53 by hpelat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"

void	ft_space(t_b *b, char *str, t_flags flags, long int nbr)
{
	if (ft_strchr(str, ' ') && flags.pl == 0 && nbr > -1)
	{
		ft_buffill(b, " ");
		b->len += 1;
	}
}
