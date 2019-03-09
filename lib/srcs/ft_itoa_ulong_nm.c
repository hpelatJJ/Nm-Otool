/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_ulong_nm.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpelat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/11 15:57:28 by hpelat            #+#    #+#             */
/*   Updated: 2017/02/11 15:57:32 by hpelat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"

void	ft_itoa_ulong_nm(char **rec, unsigned long int n)
{
	unsigned long int	mem;
	int					len;
	char				str[1024];

	mem = n;
	len = 1;
	while (mem /= 10)
		len++;
	str[len--] = '\0';
	str[len--] = '0' + n % 10;
	while (n /= 10)
		str[len--] = '0' + n % 10;
	*rec = str;
}
