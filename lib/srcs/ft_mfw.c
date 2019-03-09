/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mfw.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpelat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/13 14:22:35 by hpelat            #+#    #+#             */
/*   Updated: 2017/02/13 14:22:37 by hpelat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"

int		ft_mfw(char *str)
{
	long int	i;
	long int	nb;

	i = 0;
	nb = 0;
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]) != 0 && str[i - 1] != '.' && str[i] != '0')
		{
			nb = ft_atoi(&str[i]);
			break ;
		}
		i += 1;
	}
	return (nb);
}
