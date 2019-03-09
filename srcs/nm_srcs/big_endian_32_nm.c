/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_endian_32_nm.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpelat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 19:33:18 by hpelat            #+#    #+#             */
/*   Updated: 2019/02/11 19:33:19 by hpelat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_nm.h>

static struct nlist				*get_sym_tab(t_nm nm, struct load_command *lc)
{
	unsigned int				i;
	struct symtab_command		*sym;
	struct nlist				*sym_tab;

	sym = (struct symtab_command*)lc;
	if ((i = -1) && check_addr(nm, nm.ptr + bl32(sym->symoff)))
		return (get_return_value(EXIT_FAILURE) ? NULL : NULL);
	if (check_addr(nm, nm.ptr + bl32(sym->symoff) + (bl32(sym->nsyms)
	* sizeof(struct nlist)) + sizeof(int)))
		return (get_return_value(EXIT_FAILURE) ? NULL : NULL);
	if (!(sym_tab = (struct nlist*)malloc(bl32(sym->nsyms) * sizeof(*sym_tab))))
		return (get_return_value(EXIT_FAILURE) ? NULL : NULL);
	ft_memcpy(sym_tab, nm.ptr + bl32(sym->symoff), bl32(sym->nsyms)
	* sizeof(*sym_tab));
	while (++i < bl32(sym->nsyms))
		sym_tab = sort_big_32(nm, sym, sym_tab);
	return (sym_tab);
}

static int						get_sec_tab(t_nm nm, struct load_command *lc,
								struct nlist *sym_tab,
								struct section **sec_tab)
{
	static unsigned int			i = 0;
	unsigned int				k;
	struct segment_command		*seg;
	struct section				*sec;

	k = -1;
	seg = (struct segment_command*)lc;
	sec = (void*)lc + sizeof(struct segment_command);
	while (++k < bl32(seg->nsects))
	{
		if (check_addr(nm, (void*)sec))
		{
			i = 0;
			free(sym_tab);
			free(sec_tab);
			return (get_return_value(EXIT_FAILURE));
		}
		sec_tab[i] = sec;
		sec += 1;
		i++;
	}
	if (i == nm.sc)
		i = 0;
	return (EXIT_SUCCESS);
}

static int						print(t_nm nm, struct symtab_command *sym,
								struct nlist *sym_tab,
								struct section **sec_tab)
{
	unsigned int				i;
	char						type;
	void						*str_tab;

	i = -1;
	str_tab = nm.ptr + bl32(sym->stroff);
	while (++i < bl32(sym->nsyms))
	{
		if (!(sym_tab[i].n_type & N_STAB))
		{
			get_type_32(nm, sym_tab[i], sec_tab, &type);
			if (sym_tab[i].n_value || type == 'T' || type == 't'
			|| type == 'A' || type == 'a')
				ft_printf("%08lx %c ", bl32(sym_tab[i].n_value), type);
			else
				ft_printf("%8c %c ", ' ', type);
			print_name(nm, str_tab + bl32(sym_tab[i].n_un.n_strx));
		}
	}
	free(sym_tab);
	free(sec_tab);
	return (0);
}

static int						prepare(t_nm nm, struct mach_header *header,
								struct nlist *sym_tab)
{
	unsigned int				i;
	struct load_command			*lc;
	struct symtab_command		*sym;
	struct section				**sec_tab;

	i = -1;
	lc = nm.ptr + sizeof(struct mach_header);
	sec_tab = (struct section**)malloc(nm.sc
	* sizeof(struct section*));
	while (++i < bl32(header->ncmds))
	{
		if (bl32(lc->cmd) == LC_SYMTAB)
			sym = (struct symtab_command*)lc;
		if (bl32(lc->cmd) == LC_SEGMENT)
			if (get_sec_tab(nm, lc, sym_tab, sec_tab))
				return (get_return_value(EXIT_FAILURE));
		lc = (void*)lc + bl32(lc->cmdsize);
	}
	return (sym ? print(nm, sym, sym_tab, sec_tab) : f32(NULL, sec_tab));
}

int								handle_big_endian_32(t_nm nm)
{
	unsigned int				i;
	struct mach_header			*header;
	struct load_command			*lc;
	struct nlist				*sym_tab;

	i = -1;
	nm.sc = 0;
	header = (struct mach_header *)nm.ptr;
	lc = nm.ptr + sizeof(struct mach_header);
	while (++i < bl32(header->ncmds))
	{
		if (check_addr(nm, (void*)lc))
			return (get_return_value(EXIT_FAILURE));
		if (bl32(lc->cmd) == LC_SYMTAB)
			if (!(sym_tab = get_sym_tab(nm, lc)))
				return (get_return_value(EXIT_FAILURE));
		if (bl32(lc->cmd) == LC_SEGMENT)
			get_sec_nbr_big(lc, &(nm.sc), 32);
		lc = (void*)lc + bl32(lc->cmdsize);
	}
	return (prepare(nm, header, sym_tab));
}
