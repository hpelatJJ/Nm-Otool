/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base_ulong_nm.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpelat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/11 15:56:05 by hpelat            #+#    #+#             */
/*   Updated: 2017/02/11 15:56:06 by hpelat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"

static int		ft_baselen(unsigned long int n, int base)
{
	int		len;

	len = 1;
	while (n != 0)
	{
		len++;
		n /= base;
	}
	return (len);
}

void			ft_itoa_base_ulong_nm(char **rec, unsigned long int n, int base)
{
	char	result[1024];
	char	*str;
	int		len;
	int		i;

	len = ft_baselen(n, base);
	i = 2;
	str = "0123456789abcdefghijklmnopqrstuvwxyz";
	while (n != 0)
	{
		result[len - i] = str[(n % base)];
		n /= base;
		i++;
	}
	result[len - 1] = 0;
	*rec = (result[0] == 0 ? "0\0" : result);
}
