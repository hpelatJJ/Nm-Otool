/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpelat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 15:59:03 by hpelat            #+#    #+#             */
/*   Updated: 2019/02/07 15:59:04 by hpelat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_OTOOL_H
# define FT_OTOOL_H

# include "../lib/includes/libftprintf.h"
# include <sys/mman.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <mach-o/fat.h>
# include <mach-o/ranlib.h>
# include <ar.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <string.h>

typedef struct		s_otl
{
	void			*ptr;
	unsigned int	magic;
	size_t			size;
	size_t			sc;
	char			*name;
}					t_otl;

void				handle_little_endian_32(t_otl otl);
void				handle_little_endian_64(t_otl otl);
void				handle_big_endian_32(t_otl otl);
void				handle_big_endian_64(t_otl otl);
void				handle_fat(t_otl otl);
void				handle_arch(t_otl otl);
int					get_return_value(int new_value);
int					check_addr(t_otl otl, void *addr);
uint32_t			bl32(uint32_t b);
uint64_t			bl64(uint64_t b);
void				get_sec_nbr_little(struct load_command *lc,
					size_t *section_count, int arch);
void				get_sec_nbr_big(struct load_command *lc,
					size_t *section_count, int arch);
int					scmp(const char *s1, const char *s2);
int					sncmp(const char *s1, const char *s2, size_t size);
void				*ft_memcpy(void *dst, const void *src, size_t n);

#endif
