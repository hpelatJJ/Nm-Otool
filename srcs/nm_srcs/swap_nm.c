/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_nm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpelat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 17:18:47 by hpelat            #+#    #+#             */
/*   Updated: 2019/02/15 17:18:48 by hpelat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_nm.h>

void					swap_32(struct nlist **sym_tab, unsigned int k,
						int swap)
{
	struct nlist		tmp;

	if (swap)
	{
		tmp = (*sym_tab)[k];
		(*sym_tab)[k] = (*sym_tab)[k + 1];
		(*sym_tab)[k + 1] = tmp;
	}
}

void					swap_64(struct nlist_64 **sym_tab, unsigned int k,
						int swap)
{
	struct nlist_64		tmp;

	if (swap)
	{
		tmp = (*sym_tab)[k];
		(*sym_tab)[k] = (*sym_tab)[k + 1];
		(*sym_tab)[k + 1] = tmp;
	}
}

char					get_section_type_32(t_nm nm, struct section **sec_tab,
						struct nlist sym_tab)
{
	if (check_addr(nm, sec_tab[sym_tab.n_sect - 1]))
		return ((sym_tab.n_type & N_EXT ? 'S' : 's'));
	if (!(scmp(sec_tab[sym_tab.n_sect - 1]->sectname,
	SECT_TEXT)))
		return ((sym_tab.n_type & N_EXT ? 'T' : 't'));
	else if (!(scmp(sec_tab[sym_tab.n_sect - 1]->sectname,
	SECT_DATA)))
		return ((sym_tab.n_type & N_EXT ? 'D' : 'd'));
	else if (!(scmp(sec_tab[sym_tab.n_sect - 1]->sectname,
	SECT_BSS)))
		return ((sym_tab.n_type & N_EXT ? 'B' : 'b'));
	else
		return ((sym_tab.n_type & N_EXT ? 'S' : 's'));
}

char					get_section_type_64(t_nm nm,
						struct section_64 **sec_tab, struct nlist_64 sym_tab)
{
	if (check_addr(nm, sec_tab[sym_tab.n_sect - 1]))
		return ((sym_tab.n_type & N_EXT ? 'S' : 's'));
	if (!(scmp(sec_tab[sym_tab.n_sect - 1]->sectname,
	SECT_TEXT)))
		return ((sym_tab.n_type & N_EXT ? 'T' : 't'));
	else if (!(scmp(sec_tab[sym_tab.n_sect - 1]->sectname,
	SECT_DATA)))
		return ((sym_tab.n_type & N_EXT ? 'D' : 'd'));
	else if (!(scmp(sec_tab[sym_tab.n_sect - 1]->sectname,
	SECT_BSS)))
		return ((sym_tab.n_type & N_EXT ? 'B' : 'b'));
	else
		return ((sym_tab.n_type & N_EXT ? 'S' : 's'));
}
