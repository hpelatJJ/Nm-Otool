/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additionnal_big_otool.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpelat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 19:42:39 by hpelat            #+#    #+#             */
/*   Updated: 2019/02/11 19:42:40 by hpelat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_otool.h>

void							get_sec_nbr_big(struct load_command *lc,
								size_t *section_count, int arch)
{
	struct segment_command		*seg_32;
	struct segment_command_64	*seg_64;

	if (arch == 32)
	{
		seg_32 = (struct segment_command*)lc;
		*section_count += bl32(seg_32->nsects);
	}
	else if (arch == 64)
	{
		seg_64 = (struct segment_command_64*)lc;
		*section_count += bl32(seg_64->nsects);
	}
}

uint32_t						bl32(uint32_t b)
{
	b = ((b & 0x0000FFFF) << 16) | ((b & 0xFFFF0000) >> 16);
	b = ((b & 0x00FF00FF) << 8) | ((b & 0xFF00FF00) >> 8);
	return (b);
}

uint64_t						bl64(uint64_t b)
{
	b = ((b & 0x00000000FFFFFFFF) << 32) | ((b & 0xFFFFFFFF00000000) >> 32);
	b = ((b & 0x0000FFFF0000FFFF) << 16) | ((b & 0xFFFF0000FFFF0000) >> 16);
	b = ((b & 0x00FF00FF00FF00FF) << 8) | ((b & 0xFF00FF00FF00FF00) >> 8);
	return (b);
}
