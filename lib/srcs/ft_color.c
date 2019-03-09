/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpelat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 18:52:14 by hpelat            #+#    #+#             */
/*   Updated: 2017/02/10 18:52:16 by hpelat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"

void	ft_color(va_list ap, t_b *b, char *format)
{
	char	*rec;

	(void)format;
	b->error = 0;
	rec = va_arg(ap, char*);
	ft_buffill(b, rec);
}
