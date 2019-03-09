/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additionnal_little_nm.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpelat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 19:32:27 by hpelat            #+#    #+#             */
/*   Updated: 2019/02/11 19:32:28 by hpelat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_nm.h>

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

struct nlist					*sort_little_32(t_nm nm,
								struct symtab_command *sym,
								struct nlist *sym_tab)
{
	unsigned int				k;
	int							swap;

	k = -1;
	while (++k < sym->nsyms - 1 && !(swap = 0))
	{
		if (((check_addr(nm, (nm.ptr + sym->stroff) + sym_tab[k].n_un.n_strx))
		&& (check_addr(nm, (nm.ptr + sym->stroff)
		+ sym_tab[k + 1].n_un.n_strx)) && (sym_tab[k].n_value >
		sym_tab[k + 1].n_value)) || ((check_addr(nm, (nm.ptr + sym->stroff)
		+ sym_tab[k].n_un.n_strx)) && !check_addr(nm, (nm.ptr + sym->stroff)
		+ sym_tab[k + 1].n_un.n_strx)))
			swap = 1;
		if (check_addr(nm, (nm.ptr + sym->stroff) + sym_tab[k + 1].n_un.n_strx))
			continue ;
		if (!swap && ((scmp((nm.ptr + sym->stroff) + sym_tab[k].n_un.n_strx,
		(nm.ptr + sym->stroff) + sym_tab[k + 1].n_un.n_strx) > 0)
		|| ((scmp((nm.ptr + sym->stroff) + sym_tab[k].n_un.n_strx,
		(nm.ptr + sym->stroff) + sym_tab[k + 1].n_un.n_strx) == 0)
		&& (sym_tab[k].n_value > sym_tab[k + 1].n_value))))
			swap = 1;
		swap_32(&sym_tab, k, swap);
	}
	return (sym_tab);
}

struct nlist_64					*sort_little_64(t_nm nm,
								struct symtab_command *sym,
								struct nlist_64 *sym_tab)
{
	unsigned int				k;
	int							swap;

	k = -1;
	while (++k < sym->nsyms - 1 && !(swap = 0))
	{
		if (((check_addr(nm, (nm.ptr + sym->stroff) + sym_tab[k].n_un.n_strx))
		&& (check_addr(nm, (nm.ptr + sym->stroff)
		+ sym_tab[k + 1].n_un.n_strx)) && (sym_tab[k].n_value >
		sym_tab[k + 1].n_value)) || ((check_addr(nm, (nm.ptr + sym->stroff)
		+ sym_tab[k].n_un.n_strx)) && !check_addr(nm, (nm.ptr + sym->stroff)
		+ sym_tab[k + 1].n_un.n_strx)))
			swap = 1;
		if (check_addr(nm, (nm.ptr + sym->stroff) + sym_tab[k + 1].n_un.n_strx))
			continue ;
		if (!swap && ((scmp((nm.ptr + sym->stroff) + sym_tab[k].n_un.n_strx,
		(nm.ptr + sym->stroff) + sym_tab[k + 1].n_un.n_strx) > 0)
		|| ((scmp((nm.ptr + sym->stroff) + sym_tab[k].n_un.n_strx,
		(nm.ptr + sym->stroff) + sym_tab[k + 1].n_un.n_strx) == 0)
		&& (sym_tab[k].n_value > sym_tab[k + 1].n_value))))
			swap = 1;
		swap_64(&sym_tab, k, swap);
	}
	return (sym_tab);
}

int								first_check_for_big_32(t_nm nm,
								struct symtab_command *sym,
								struct nlist *sym_tab, unsigned int k)
{
	if (((check_addr(nm, (nm.ptr + bl32(sym->stroff))
	+ bl32(sym_tab[k].n_un.n_strx))) && (check_addr(nm, (nm.ptr
	+ bl32(sym->stroff)) + bl32(sym_tab[k + 1].n_un.n_strx)))
	&& (sym_tab[k].n_value > sym_tab[k + 1].n_value))
	|| ((check_addr(nm, (nm.ptr + bl32(sym->stroff))
	+ bl32(sym_tab[k].n_un.n_strx)))
	&& !check_addr(nm, (nm.ptr + bl32(sym->stroff))
	+ bl32(sym_tab[k + 1].n_un.n_strx))))
		return (1);
	return (0);
}

int								first_check_for_big_64(t_nm nm,
								struct symtab_command *sym,
								struct nlist_64 *sym_tab, unsigned int k)
{
	if (((check_addr(nm, (nm.ptr + bl32(sym->stroff))
	+ bl32(sym_tab[k].n_un.n_strx))) && (check_addr(nm, (nm.ptr
	+ bl32(sym->stroff)) + bl32(sym_tab[k + 1].n_un.n_strx)))
	&& (sym_tab[k].n_value > sym_tab[k + 1].n_value))
	|| ((check_addr(nm, (nm.ptr + bl32(sym->stroff))
	+ bl32(sym_tab[k].n_un.n_strx)))
	&& !check_addr(nm, (nm.ptr + bl32(sym->stroff))
	+ bl32(sym_tab[k + 1].n_un.n_strx))))
		return (1);
	return (0);
}
