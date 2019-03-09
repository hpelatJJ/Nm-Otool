/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additionnal_little_otool.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpelat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 19:42:09 by hpelat            #+#    #+#             */
/*   Updated: 2019/02/11 19:42:10 by hpelat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_otool.h>

void							get_sec_nbr_little(struct load_command *lc,
								size_t *section_count, int arch)
{
	struct segment_command		*seg_32;
	struct segment_command_64	*seg_64;

	if (arch == 32)
	{
		seg_32 = (struct segment_command*)lc;
		*section_count += seg_32->nsects;
	}
	else if (arch == 64)
	{
		seg_64 = (struct segment_command_64*)lc;
		*section_count += seg_64->nsects;
	}
}
