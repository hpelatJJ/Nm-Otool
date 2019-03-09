/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_otool.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpelat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 17:15:56 by hpelat            #+#    #+#             */
/*   Updated: 2019/02/08 17:15:58 by hpelat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_otool.h>

static void			handler_choice(t_otl otl)
{
	if (otl.magic == MH_MAGIC || otl.magic == MH_MAGIC_64)
	{
		ft_printf("%s:\n", otl.name);
		otl.magic == MH_MAGIC ? handle_little_endian_32(otl)
		: handle_little_endian_64(otl);
	}
	else if (otl.magic == MH_CIGAM)
		handle_big_endian_32(otl);
	else if (otl.magic == MH_CIGAM_64)
		handle_big_endian_64(otl);
	else if (otl.magic == FAT_CIGAM || otl.magic == FAT_CIGAM_64
	|| otl.magic == FAT_MAGIC || otl.magic == FAT_MAGIC_64)
		handle_fat(otl);
	else if (!(sncmp(otl.ptr, ARMAG, SARMAG)))
		handle_arch(otl);
	else
		fd_printf(1, "%s: is not an object file\n", otl.name);
}

static void			ft_otool(char *name, int fd, struct stat st)
{
	void			*ptr;
	t_otl			otl;

	if ((ptr = mmap(0, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0))
	== MAP_FAILED)
	{
		fd_printf(2, "ft_otool: mmap failed\n");
		exit(get_return_value(EXIT_FAILURE));
		return ;
	}
	otl.ptr = ptr;
	otl.size = st.st_size;
	otl.magic = *(unsigned int*)ptr;
	otl.name = name;
	handler_choice(otl);
	if (munmap(ptr, st.st_size) == -1)
	{
		fd_printf(2, "ft_otool: munmap failed\n");
		exit(get_return_value(EXIT_FAILURE));
	}
	ptr = NULL;
}

static void			loop(char *file)
{
	int				fd;
	struct stat		st;

	fd = open(file, O_RDONLY);
	fstat(fd, &st);
	if (S_ISDIR(st.st_mode))
	{
		fd_printf(2, "ft_otool: '%s': Is a directory\n", file);
		exit(get_return_value(EXIT_FAILURE));
	}
	else if (!(S_IROTH & st.st_mode))
	{
		fd_printf(2,
		"ft_otool: '%s': Permission denied\n", file);
		exit(get_return_value(EXIT_FAILURE));
	}
	else
		ft_otool(file, fd, st);
	close(fd);
}

int					main(int ac, char **av)
{
	int				i;

	if (ac < 2)
	{
		fd_printf(2, "error: ft_otool: at least on file must be specified\n");
		return (EXIT_FAILURE);
	}
	i = 0;
	while (++i < ac)
		loop(av[i]);
	return (get_return_value(0));
}
