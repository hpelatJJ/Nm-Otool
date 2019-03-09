/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additionnal_big_nm.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpelat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 19:31:59 by hpelat            #+#    #+#             */
/*   Updated: 2019/02/11 19:32:01 by hpelat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_nm.h>

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

struct nlist					*sort_big_32(t_nm nm,
								struct symtab_command *sym,
								struct nlist *sym_tab)
{
	unsigned int				k;
	int							swap;

	k = -1;
	while (++k < bl32(sym->nsyms) - 1)
	{
		swap = first_check_for_big_32(nm, sym, sym_tab, k);
		if (check_addr(nm, (nm.ptr + bl32(sym->stroff))
		+ bl32(sym_tab[k + 1].n_un.n_strx)))
			continue ;
		if (!swap && ((scmp((nm.ptr + bl32(sym->stroff))
		+ bl32(sym_tab[k].n_un.n_strx),
		(nm.ptr + bl32(sym->stroff)) + bl32(sym_tab[k + 1].n_un.n_strx)) > 0)
		|| ((scmp((nm.ptr + bl32(sym->stroff)) + bl32(sym_tab[k].n_un.n_strx),
		(nm.ptr + bl32(sym->stroff)) + bl32(sym_tab[k + 1].n_un.n_strx)) == 0)
		&& (sym_tab[k].n_value > sym_tab[k + 1].n_value))))
			swap = 1;
		swap_32(&sym_tab, k, swap);
	}
	return (sym_tab);
}

struct nlist_64					*sort_big_64(t_nm nm,
								struct symtab_command *sym,
								struct nlist_64 *sym_tab)
{
	unsigned int				k;
	int							swap;

	k = -1;
	while (++k < bl32(sym->nsyms) - 1)
	{
		swap = first_check_for_big_64(nm, sym, sym_tab, k);
		if (check_addr(nm, (nm.ptr + bl32(sym->stroff))
		+ bl32(sym_tab[k + 1].n_un.n_strx)))
			continue ;
		if (!swap && ((scmp((nm.ptr + bl32(sym->stroff))
		+ bl32(sym_tab[k].n_un.n_strx),
		(nm.ptr + bl32(sym->stroff)) + bl32(sym_tab[k + 1].n_un.n_strx)) > 0)
		|| ((scmp((nm.ptr + bl32(sym->stroff)) + bl32(sym_tab[k].n_un.n_strx),
		(nm.ptr + bl32(sym->stroff)) + bl32(sym_tab[k + 1].n_un.n_strx)) == 0)
		&& (sym_tab[k].n_value > sym_tab[k + 1].n_value))))
			swap = 1;
		swap_64(&sym_tab, k, swap);
	}
	return (sym_tab);
}
