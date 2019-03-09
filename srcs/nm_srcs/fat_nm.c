/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat_nm.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpelat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 19:33:58 by hpelat            #+#    #+#             */
/*   Updated: 2019/02/11 19:33:59 by hpelat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_nm.h>

static int					check_archive_type(t_nm nm, uint64_t offset,
							unsigned int magic, void *ptr)
{
	struct ar_hdr			*arch;

	arch = ptr + SARMAG;
	arch = (void*)arch + sizeof(struct ar_hdr) + ft_atoi(arch->ar_size);
	nm.magic = *(unsigned int*)((void*)arch + sizeof(*arch)
	+ ft_atoi(arch->ar_name + 3));
	if (nm.magic == MH_MAGIC_64)
	{
		nm.size = nm.size - (((void*)nm.ptr + offset) - nm.ptr);
		nm.ptr = ptr;
		nm.magic = magic;
		handle_arch(nm);
		return (0);
	}
	return (1);
}

static int					check_arch(t_nm nm, struct fat_arch *fat)
{
	uint64_t				offset;
	uint64_t				align;
	unsigned int			magic;
	void					*ptr;

	offset = bl32(fat->offset);
	align = bl32(fat->align);
	offset = ((offset + align) & ~align);
	if (check_addr(nm, (ptr = nm.ptr + offset) + sizeof(int)))
		return (0);
	magic = *(unsigned int*)ptr;
	if (magic == MH_MAGIC_64)
	{
		nm.size = nm.size - (((void*)nm.ptr + offset) - nm.ptr);
		nm.ptr = ptr;
		nm.magic = magic;
		handle_little_endian_64(nm);
		return (0);
	}
	else if (!(sncmp(ptr, ARMAG, SARMAG)))
		return (check_archive_type(nm, offset, magic, ptr));
	return (1);
}

static void					get_arch(t_nm nm, struct fat_arch *fat,
							uint64_t offset, char arn)
{
	uint64_t				align;

	align = bl32(fat->align);
	offset = ((offset + align) & ~align);
	nm.size = nm.size - (((void*)nm.ptr + offset) - nm.ptr);
	if (check_addr(nm, (nm.ptr = nm.ptr + offset) + sizeof(int)))
		return ;
	if ((nm.magic = *(unsigned int*)nm.ptr) == MH_MAGIC)
	{
		arn ? ft_printf("%s:\n", nm.name)
		: ft_printf("%s (for architecture i386):\n", nm.name);
		handle_little_endian_32(nm);
	}
	else if (nm.magic == MH_MAGIC_64)
		handle_little_endian_64(nm);
	else if (nm.magic == MH_CIGAM)
	{
		arn ? ft_printf("%s:\n", nm.name)
		: ft_printf("%s (for architecture ppc):\n", nm.name);
		handle_big_endian_32(nm);
	}
	else if (nm.magic == MH_CIGAM_64)
		handle_big_endian_64(nm);
	else if (!(sncmp(nm.ptr, ARMAG, SARMAG)))
		handle_arch(nm);
}

void						handle_fat(t_nm nm)
{
	struct fat_header		*f_header;
	struct fat_arch			*fat;
	uint32_t				nfa;
	char					arn;

	arn = 0;
	f_header = (struct fat_header*)nm.ptr;
	fat = nm.ptr + sizeof(struct fat_header);
	nfa = bl32(f_header->nfat_arch);
	while (nfa--)
	{
		if (check_addr(nm, fat + sizeof(*fat)) || !check_arch(nm, fat))
			return ;
		fat++;
	}
	fat = nm.ptr + sizeof(struct fat_header);
	if ((nfa = bl32(f_header->nfat_arch)) == 1)
		arn = 1;
	while (nfa--)
	{
		arn ? 0 : ft_printf("\n");
		get_arch(nm, fat, bl32(fat->offset), arn);
		fat++;
	}
}
