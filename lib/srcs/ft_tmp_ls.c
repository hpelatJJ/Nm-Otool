/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tmp_ls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpelat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 18:23:04 by hpelat            #+#    #+#             */
/*   Updated: 2017/02/16 18:23:05 by hpelat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"

void	ft_tmp_ls(t_b *b, char *str, wchar_t *rec)
{
	int		i;
	char	*tmp;

	i = 0;
	if (ft_strchr(str, '.'))
		tmp = "";
	else if (rec == NULL)
	{
		tmp = "(null)";
		b->len += 6;
		ft_buffill(b, tmp);
	}
	else
		while (rec[i] != '\0')
		{
			tmp = ft_get_wchar(b, rec[i]);
			ft_buffill(b, tmp);
			i += 1;
		}
}
