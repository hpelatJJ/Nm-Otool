/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_n.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpelat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 18:43:58 by hpelat            #+#    #+#             */
/*   Updated: 2017/02/10 18:44:00 by hpelat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"

void	ft_conv_n(va_list ap, t_b *b, char *format)
{
	int		*n;

	(void)format;
	b->error = 0;
	n = va_arg(ap, int*);
	*n = b->len;
}
