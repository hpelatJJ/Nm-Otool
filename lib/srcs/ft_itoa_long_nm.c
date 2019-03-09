/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_long_nm.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpelat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 17:23:10 by hpelat            #+#    #+#             */
/*   Updated: 2017/02/12 17:23:12 by hpelat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"

static char		*ft_longmintoa(char *rec, long int n)
{
	int			i;
	char		*tmp;
	char		str[1024];

	i = -1;
	n = 0;
	tmp = "9223372036854775808";
	while (tmp[++i])
		str[i] = tmp[i];
	str[i] = 0;
	rec = str;
	return (rec);
}

void			ft_itoa_long_nm(char **rec, long int n)
{
	int			i;
	long int	mem;
	int			len;
	char		str[1024];

	mem = n;
	len = 1;
	i = -1;
	while (mem /= 10)
		len++;
	if (n == -9223372036854775807 - 1)
		*rec = ft_longmintoa(*rec, n);
	else
	{
		if (n < 0)
			n *= -1;
		str[0] = '-';
		str[len--] = '\0';
		str[len--] = '0' + n % 10;
		while (n /= 10)
			str[len--] = '0' + n % 10;
		*rec = str;
	}
}
