/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base_long_nm.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpelat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 17:23:26 by hpelat            #+#    #+#             */
/*   Updated: 2017/02/12 17:23:27 by hpelat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"

static int	ft_baselen(long int n, int base)
{
	int		len;

	len = 1;
	while (n /= base)
		len++;
	return (len);
}

void		ft_itoa_base_long_nm(char **rec, long int n, int base)
{
	char	result[1024];
	char	*str;
	int		len;
	int		i;

	len = ft_baselen(n, base);
	i = 1;
	if (base != 10)
	{
		str = "0123456789abcdefghijklmnopqrstuvwxyz";
		while (n != 0)
		{
			result[len - i] = str[(n % base)];
			n /= base;
			i++;
		}
		result[len] = '\0';
		*rec = (result[0] == 0 ? "0\0" : result);
	}
	else
		ft_itoa_long_nm(rec, n);
}
