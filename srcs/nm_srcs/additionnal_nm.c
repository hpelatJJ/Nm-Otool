/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additionnal_nm.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpelat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 19:31:37 by hpelat            #+#    #+#             */
/*   Updated: 2019/02/11 19:31:38 by hpelat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_nm.h>

void				print_name(t_nm nm, char *name)
{
	size_t			size;
	size_t			end;

	size = -1;
	if (check_addr(nm, name))
	{
		ft_printf("bad string index\n");
		return ;
	}
	end = (nm.ptr + nm.size) - (void*)name;
	while (++size < end && name[size])
		;
	write(1, name, size);
	write(1, "\n", 1);
}

int					check_addr(t_nm nm, void *addr)
{
	if (nm.ptr <= addr && (nm.ptr + nm.size) >= addr)
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

void				get_type_32(t_nm nm, struct nlist sym_tab,
					struct section **sec_tab, char *type)
{
	if ((sym_tab.n_type & N_TYPE) == N_UNDF)
	{
		if (sym_tab.n_value)
			*type = (sym_tab.n_type & N_EXT ? 'C' : '?');
		else
			*type = (sym_tab.n_type & N_EXT ? 'U' : 'u');
	}
	else if ((sym_tab.n_type & N_TYPE) == N_ABS)
		*type = (sym_tab.n_type & N_EXT ? 'A' : 'a');
	else if ((sym_tab.n_type & N_TYPE) == N_INDR)
		*type = (sym_tab.n_type & N_EXT ? 'I' : 'i');
	else if ((sym_tab.n_type & N_TYPE) == N_SECT)
		*type = get_section_type_32(nm, sec_tab, sym_tab);
	else
		*type = '?';
	(void)nm;
}

void				get_type_64(t_nm nm, struct nlist_64 sym_tab,
					struct section_64 **sec_tab, char *type)
{
	if ((sym_tab.n_type & N_TYPE) == N_UNDF)
	{
		if (sym_tab.n_value)
			*type = (sym_tab.n_type & N_EXT ? 'C' : '?');
		else
			*type = (sym_tab.n_type & N_EXT ? 'U' : 'u');
	}
	else if ((sym_tab.n_type & N_TYPE) == N_ABS)
		*type = (sym_tab.n_type & N_EXT ? 'A' : 'a');
	else if ((sym_tab.n_type & N_TYPE) == N_INDR)
		*type = (sym_tab.n_type & N_EXT ? 'I' : 'i');
	else if ((sym_tab.n_type & N_TYPE) == N_SECT)
		*type = get_section_type_64(nm, sec_tab, sym_tab);
	else
		*type = '?';
	(void)nm;
}
