/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additionnal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpelat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 17:26:14 by hpelat            #+#    #+#             */
/*   Updated: 2019/02/08 17:26:18 by hpelat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_otool.h>

int					check_addr(t_otl otl, void *addr)
{
	if (otl.ptr <= addr && (otl.ptr + otl.size) >= addr)
		return (0);
	return (1);
}

int					get_return_value(int new_value)
{
	static int		return_value = EXIT_SUCCESS;

	if (new_value)
		return_value = new_value;
	return (return_value);
}

void				get_type_32(struct nlist *sym_tab,
					unsigned int i, struct section **sec_tab,
					char *type)
{
	if ((sym_tab[i].n_type & N_TYPE) == N_UNDF)
	{
		if (sym_tab[i].n_value)
			*type = (sym_tab[i].n_type & N_EXT ? 'C' : 'c');
		else
			*type = (sym_tab[i].n_type & N_EXT ? 'U' : 'u');
	}
	else if ((sym_tab[i].n_type & N_TYPE) == N_ABS)
		*type = (sym_tab[i].n_type & N_EXT ? 'A' : 'a');
	else if ((sym_tab[i].n_type & N_TYPE) == N_INDR)
		*type = (sym_tab[i].n_type & N_EXT ? 'I' : 'i');
	else if ((sym_tab[i].n_type & N_TYPE) == N_SECT)
	{
		if (!(scmp(sec_tab[sym_tab[i].n_sect - 1]->sectname,
		SECT_TEXT)))
			*type = (sym_tab[i].n_type & N_EXT ? 'T' : 't');
		else if (!(scmp(sec_tab[sym_tab[i].n_sect - 1]->sectname,
		SECT_DATA)))
			*type = (sym_tab[i].n_type & N_EXT ? 'D' : 'd');
		else if (!(scmp(sec_tab[sym_tab[i].n_sect - 1]->sectname,
		SECT_BSS)))
			*type = (sym_tab[i].n_type & N_EXT ? 'B' : 'b');
		else
			*type = (sym_tab[i].n_type & N_EXT ? 'S' : 's');
	}
}

void				get_type_64(struct nlist_64 *sym_tab,
					unsigned int i, struct section_64 **sec_tab,
					char *type)
{
	if ((sym_tab[i].n_type & N_TYPE) == N_UNDF)
	{
		if (sym_tab[i].n_value)
			*type = (sym_tab[i].n_type & N_EXT ? 'C' : 'c');
		else
			*type = (sym_tab[i].n_type & N_EXT ? 'U' : 'u');
	}
	else if ((sym_tab[i].n_type & N_TYPE) == N_ABS)
		*type = (sym_tab[i].n_type & N_EXT ? 'A' : 'a');
	else if ((sym_tab[i].n_type & N_TYPE) == N_INDR)
		*type = (sym_tab[i].n_type & N_EXT ? 'I' : 'i');
	else if ((sym_tab[i].n_type & N_TYPE) == N_SECT)
	{
		if (!(scmp(sec_tab[sym_tab[i].n_sect - 1]->sectname,
		SECT_TEXT)))
			*type = (sym_tab[i].n_type & N_EXT ? 'T' : 't');
		else if (!(scmp(sec_tab[sym_tab[i].n_sect - 1]->sectname,
		SECT_DATA)))
			*type = (sym_tab[i].n_type & N_EXT ? 'D' : 'd');
		else if (!(scmp(sec_tab[sym_tab[i].n_sect - 1]->sectname,
		SECT_BSS)))
			*type = (sym_tab[i].n_type & N_EXT ? 'B' : 'b');
		else
			*type = (sym_tab[i].n_type & N_EXT ? 'S' : 's');
	}
}
