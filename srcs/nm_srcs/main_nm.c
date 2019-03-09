/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_nm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpelat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 15:58:06 by hpelat            #+#    #+#             */
/*   Updated: 2019/03/04 14:16:56 by hpelat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_nm.h>

static void			handler_choice(t_nm nm, int lf)
{
	if (nm.magic == MH_MAGIC || nm.magic == MH_MAGIC_64 || nm.magic == MH_CIGAM
	|| nm.magic == MH_CIGAM_64)
	{
		if (lf)
			ft_printf("\n%s:\n", nm.name);
		if (nm.magic == MH_MAGIC)
			handle_little_endian_32(nm);
		else if (nm.magic == MH_MAGIC_64)
			handle_little_endian_64(nm);
		else if (nm.magic == MH_CIGAM)
			handle_big_endian_32(nm);
		else if (nm.magic == MH_CIGAM_64)
			handle_big_endian_64(nm);
	}
	else if (nm.magic == FAT_CIGAM || nm.magic == FAT_CIGAM_64
	|| nm.magic == FAT_MAGIC || nm.magic == FAT_MAGIC_64)
		handle_fat(nm);
	else if (!(sncmp(nm.ptr, ARMAG, SARMAG)))
		handle_arch(nm);
	else
		fd_printf(2,
		"ft_nm: %s The file was not recognized as a valid object file\n",
		nm.name);
}

static void			ft_nm(char *name, int fd, struct stat st, int lf)
{
	void			*ptr;
	t_nm			nm;

	if ((ptr = mmap(0, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0))
	== MAP_FAILED)
	{
		fd_printf(2, "ft_nm: mmap failed.\n");
		get_return_value(EXIT_FAILURE);
		return ;
	}
	nm.ptr = ptr;
	nm.size = st.st_size;
	nm.magic = *(unsigned int*)ptr;
	nm.name = name;
	handler_choice(nm, lf);
	if (munmap(ptr, st.st_size) == -1)
	{
		fd_printf(2, "ft_nm: munmap failed.\n");
		get_return_value(EXIT_FAILURE);
	}
	ptr = NULL;
}

static void			loop(int fd, char *file, int ac, int i)
{
	struct stat		st;

	fd = open(file, O_RDONLY);
	fstat(fd, &st);
	if (S_ISDIR(st.st_mode))
	{
		fd_printf(2, "ft_nm: %s: Is a directory.\n", file);
		get_return_value(EXIT_FAILURE);
	}
	else if (!(S_IROTH & st.st_mode))
	{
		fd_printf(2, "ft_nm: %s: Permission denied.\n", file);
		get_return_value(EXIT_FAILURE);
	}
	else
		ft_nm(file, fd, st, (ac > 2 ? i : 0));
	close(fd);
}

int					main(int ac, char **av)
{
	int				fd;
	int				i;
	struct stat		st;

	if (ac < 2)
	{
		if ((fd = open("a.out", O_RDONLY)) == -1)
		{
			fd_printf(2, "ft_nm: a.out: Permission denied.\n");
			return (get_return_value(EXIT_FAILURE));
		}
		fstat(fd, &st);
		if (S_ISDIR(st.st_mode))
		{
			fd_printf(2, "ft_nm: a.out: Is a directory.\n");
			get_return_value(EXIT_FAILURE);
		}
		ft_nm("a.out", fd, st, 0);
		close(fd);
	}
	i = 0;
	while (++i < ac)
		loop(fd, av[i], ac, i);
	return (get_return_value(0));
}
