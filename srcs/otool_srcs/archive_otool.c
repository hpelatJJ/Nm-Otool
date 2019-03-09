/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   archive_otool.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpelat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 19:40:37 by hpelat            #+#    #+#             */
/*   Updated: 2019/02/11 19:40:44 by hpelat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_otool.h>

static void			which_arch(t_otl otl, struct ar_hdr *arch)
{
	if (otl.magic == MH_MAGIC || otl.magic == MH_MAGIC_64)
	{
		ft_printf("%s(%s):\n", otl.name, (void*)arch + sizeof(*arch));
		otl.magic == MH_MAGIC ? handle_little_endian_32(otl) :
		handle_little_endian_64(otl);
	}
	else if (otl.magic == MH_CIGAM || otl.magic == MH_CIGAM_64)
	{
		ft_printf("%s(%s):\n", otl.name, (void*)arch + sizeof(*arch));
		otl.magic == MH_MAGIC ? handle_big_endian_32(otl) :
		handle_big_endian_64(otl);
	}
}

void				handle_arch(t_otl otl)
{
	struct ar_hdr	*arch;
	void			*ptr;

	arch = otl.ptr + SARMAG;
	ft_printf("Archive : %s\n", otl.name);
	while (!sncmp(arch->ar_fmag, ARFMAG, 2))
	{
		ptr = (void*)arch + sizeof(struct ar_hdr)
		+ ft_atoi(arch->ar_name + 3);
		if (check_addr(otl, ptr))
			exit(EXIT_FAILURE);
		otl.size = otl.size - (((void*)arch + sizeof(struct ar_hdr)
		+ ft_atoi(arch->ar_name + 3)) - otl.ptr);
		otl.ptr = ptr;
		otl.magic = *(unsigned int*)otl.ptr;
		which_arch(otl, arch);
		arch = (void*)arch + sizeof(struct ar_hdr) + ft_atoi(arch->ar_size);
	}
}
