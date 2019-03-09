/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat_otool.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpelat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 19:40:16 by hpelat            #+#    #+#             */
/*   Updated: 2019/02/11 19:40:17 by hpelat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_otool.h>

static int					check_archive_type(t_otl otl, uint64_t offset,
							unsigned int magic, void *ptr)
{
	struct ar_hdr			*arch;

	arch = ptr + SARMAG;
	arch = (void*)arch + sizeof(struct ar_hdr) + ft_atoi(arch->ar_size);
	otl.magic = *(unsigned int*)((void*)arch + sizeof(*arch)
	+ ft_atoi(arch->ar_name + 3));
	if (otl.magic == MH_MAGIC_64)
	{
		otl.size = otl.size - (((void*)otl.ptr + offset) - otl.ptr);
		otl.ptr = ptr;
		otl.magic = magic;
		handle_arch(otl);
		return (0);
	}
	return (1);
}

static int					check_arch(t_otl otl, struct fat_arch *fat)
{
	uint64_t				offset;
	uint64_t				align;
	unsigned int			magic;
	void					*ptr;

	offset = bl32(fat->offset);
	align = bl32(fat->align);
	offset = ((offset + align) & ~align);
	if (check_addr(otl, (ptr = otl.ptr + offset) + sizeof(int)))
		exit(EXIT_FAILURE);
	magic = *(unsigned int*)ptr;
	if (magic == MH_MAGIC_64)
	{
		otl.size = otl.size - (((void*)otl.ptr + offset) - otl.ptr);
		otl.ptr = ptr;
		otl.magic = magic;
		ft_printf("%s:\n", otl.name);
		handle_little_endian_64(otl);
		return (0);
	}
	else if (!sncmp(ptr, ARMAG, SARMAG))
		return (check_archive_type(otl, offset, magic, ptr));
	return (1);
}

static void					get_arch(t_otl otl, struct fat_arch *fat,
							uint64_t offset, char arn)
{
	uint64_t				align;

	align = bl32(fat->align);
	offset = ((offset + align) & ~align);
	otl.size = otl.size - (((void*)otl.ptr + offset) - otl.ptr);
	if (check_addr(otl, (otl.ptr = otl.ptr + offset) + sizeof(int)))
		exit(EXIT_FAILURE);
	if ((otl.magic = *(unsigned int*)otl.ptr) == MH_MAGIC)
	{
		arn ? ft_printf("%s:\n", otl.name)
		: ft_printf("%s (architecture i386):\n", otl.name);
		handle_little_endian_32(otl);
	}
	else if (otl.magic == MH_MAGIC_64)
		handle_little_endian_64(otl);
	else if (otl.magic == MH_CIGAM)
	{
		arn ? ft_printf("%s:\n", otl.name)
		: ft_printf("%s (architecture ppc):\n", otl.name);
		handle_big_endian_32(otl);
	}
	else if (otl.magic == MH_CIGAM_64)
		handle_big_endian_64(otl);
	else if (!(sncmp(otl.ptr, ARMAG, SARMAG)))
		handle_arch(otl);
}

void						handle_fat(t_otl otl)
{
	struct fat_header		*f_header;
	struct fat_arch			*fat;
	uint32_t				nfa;
	char					arn;

	arn = 0;
	f_header = (struct fat_header*)otl.ptr;
	fat = otl.ptr + sizeof(struct fat_header);
	nfa = bl32(f_header->nfat_arch);
	while (nfa--)
	{
		if (check_addr(otl, fat + sizeof(*fat)) || !check_arch(otl, fat))
			exit(EXIT_FAILURE);
		fat++;
	}
	fat = otl.ptr + sizeof(struct fat_header);
	if ((nfa = bl32(f_header->nfat_arch)) == 1)
		arn = 1;
	while (nfa--)
	{
		get_arch(otl, fat, bl32(fat->offset), arn);
		fat++;
	}
}
