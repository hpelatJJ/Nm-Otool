/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   archive_nm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpelat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 19:32:53 by hpelat            #+#    #+#             */
/*   Updated: 2019/02/11 19:32:55 by hpelat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_nm.h>

static void			which_arch(t_nm nm, struct ar_hdr *arch)
{
	if (nm.magic == MH_MAGIC || nm.magic == MH_MAGIC_64)
	{
		ft_printf("\n%s(%s):\n", nm.name, (void*)arch + sizeof(*arch));
		nm.magic == MH_MAGIC ? handle_little_endian_32(nm) :
		handle_little_endian_64(nm);
	}
	else if (nm.magic == MH_CIGAM || nm.magic == MH_CIGAM_64)
	{
		ft_printf("\n%s(%s):\n", nm.name, (void*)arch + sizeof(*arch));
		nm.magic == MH_MAGIC ? handle_big_endian_32(nm) :
		handle_big_endian_64(nm);
	}
}

void				handle_arch(t_nm nm)
{
	struct ar_hdr	*arch;
	void			*ptr;

	arch = nm.ptr + SARMAG;
	while (!sncmp(arch->ar_fmag, ARFMAG, 2))
	{
		ptr = (void*)arch + sizeof(struct ar_hdr)
		+ ft_atoi(arch->ar_name + 3);
		if (check_addr(nm, ptr))
			return ;
		nm.size = nm.size - (((void*)arch + sizeof(struct ar_hdr)
		+ ft_atoi(arch->ar_name + 3)) - nm.ptr);
		nm.ptr = ptr;
		nm.magic = *(unsigned int*)nm.ptr;
		which_arch(nm, arch);
		arch = (void*)arch + sizeof(struct ar_hdr) + ft_atoi(arch->ar_size);
	}
}

int					f32(struct nlist *sym_tab, struct section **sec_tab)
{
	if (sym_tab)
		free(sym_tab);
	if (sec_tab)
		free(sec_tab);
	return (EXIT_FAILURE);
}

int					f64(struct nlist_64 *sym_tab, struct section_64 **sec_tab)
{
	if (sym_tab)
		free(sym_tab);
	if (sec_tab)
		free(sec_tab);
	return (EXIT_FAILURE);
}
