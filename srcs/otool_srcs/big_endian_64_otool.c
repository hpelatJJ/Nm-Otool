/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_endian_64_otool.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpelat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 19:38:36 by hpelat            #+#    #+#             */
/*   Updated: 2019/02/11 19:38:37 by hpelat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_otool.h>

static int						get_sec_tab(t_otl otl, struct load_command *lc,
								struct section_64 **sec_tab)
{
	static unsigned int			i = 0;
	unsigned int				k;
	struct segment_command_64	*seg;
	struct section_64			*sec;

	k = -1;
	seg = (struct segment_command_64*)lc;
	sec = (void*)lc + sizeof(struct segment_command_64);
	while (++k < bl32(seg->nsects))
	{
		if (check_addr(otl, (void*)sec))
		{
			i = 0;
			free(sec_tab);
			exit(get_return_value(EXIT_FAILURE));
		}
		sec_tab[i] = sec;
		sec += 1;
		i++;
	}
	if (i == otl.sc)
		i = 0;
	return (EXIT_SUCCESS);
}

static void						print(t_otl otl, struct section_64 **sec_tab)
{
	unsigned int				i;
	uint32_t					k;

	i = -1;
	while (++i < otl.sc)
	{
		if (!scmp(sec_tab[i]->segname, SEG_TEXT)
		&& !scmp(sec_tab[i]->sectname, SECT_TEXT))
		{
			k = -1;
			ft_printf("Contents of (%s,%s) section", sec_tab[i]->segname,
			sec_tab[i]->sectname);
			while (++k < bl64(sec_tab[i]->size))
			{
				if (!(k % 16))
					ft_printf("\n%016lx\t", bl64(sec_tab[i]->addr) + k);
				ft_printf("%02x ", *((unsigned char*)otl.ptr
				+ bl32(sec_tab[i]->offset) + k));
			}
			ft_printf("\n");
		}
	}
	free(sec_tab);
}

static void						prepare(t_otl otl,
								struct mach_header_64 *header)
{
	unsigned int				i;
	struct load_command			*lc;
	struct section_64			**sec_tab;

	i = -1;
	lc = otl.ptr + sizeof(struct mach_header_64);
	sec_tab = (struct section_64**)malloc(otl.sc
	* sizeof(struct section_64*));
	while (++i < bl32(header->ncmds))
	{
		if (bl32(lc->cmd) == LC_SEGMENT_64)
			if (get_sec_tab(otl, lc, sec_tab))
				return ;
		lc = (void*)lc + bl32(lc->cmdsize);
	}
	print(otl, sec_tab);
}

void							handle_big_endian_64(t_otl otl)
{
	unsigned int				i;
	struct mach_header_64		*header;
	struct load_command			*lc;

	i = -1;
	otl.sc = 0;
	header = (struct mach_header_64 *)otl.ptr;
	lc = otl.ptr + sizeof(struct mach_header_64);
	while (++i < bl32(header->ncmds))
	{
		if (check_addr(otl, (void*)lc))
			exit(get_return_value(EXIT_FAILURE));
		if (bl32(lc->cmd) == LC_SEGMENT_64)
			get_sec_nbr_big(lc, &(otl.sc), 64);
		lc = (void*)lc + bl32(lc->cmdsize);
	}
	prepare(otl, header);
}
