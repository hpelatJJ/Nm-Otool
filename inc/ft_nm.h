/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpelat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 15:28:35 by hpelat            #+#    #+#             */
/*   Updated: 2019/01/28 15:28:36 by hpelat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
# define FT_NM_H

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

typedef struct		s_nm
{
	void			*ptr;
	unsigned int	magic;
	size_t			size;
	size_t			sc;
	char			*name;
}					t_nm;

int					handle_little_endian_32(t_nm nm);
int					handle_little_endian_64(t_nm nm);
int					handle_big_endian_32(t_nm nm);
int					handle_big_endian_64(t_nm nm);
void				handle_fat(t_nm nm);
void				handle_arch(t_nm nm);
int					get_return_value(int new_value);
int					check_addr(t_nm nm, void *addr);
uint32_t			bl32(uint32_t b);
uint64_t			bl64(uint64_t b);
void				get_sec_nbr_big(struct load_command *lc,
					size_t *section_count, int arch);
void				get_sec_nbr_little(struct load_command *lc,
					size_t *section_count, int arch);
void				get_type_32(t_nm nm, struct nlist sym_tab,
					struct section **sec_tab, char *type);
void				get_type_64(t_nm nm, struct nlist_64 sym_tab,
					struct section_64 **sec_tab, char *type);
struct nlist		*sort_little_32(t_nm nm,
					struct symtab_command *sym,
					struct nlist *sym_tab);
struct nlist_64		*sort_little_64(t_nm nm,
					struct symtab_command *sym,
					struct nlist_64 *sym_tab);
struct nlist		*sort_big_32(t_nm nm,
					struct symtab_command *sym,
					struct nlist *sym_tab);
struct nlist_64		*sort_big_64(t_nm nm,
					struct symtab_command *sym,
					struct nlist_64 *sym_tab);
void				swap_32(struct nlist **sym_tab, unsigned int k, int swap);
void				swap_64(struct nlist_64 **sym_tab, unsigned int k,
					int swap);
int					first_check_for_big_32(t_nm nm,
					struct symtab_command *sym,
					struct nlist *sym_tab, unsigned int k);
int					first_check_for_big_64(t_nm nm,
					struct symtab_command *sym,
					struct nlist_64 *sym_tab, unsigned int k);
char				get_section_type_32(t_nm nm, struct section **sec_tab,
					struct nlist sym_tab);
char				get_section_type_64(t_nm nm,
					struct section_64 **sec_tab, struct nlist_64 sym_tab);
int					f32(struct nlist *sym_tab, struct section **sec_tab);
int					f64(struct nlist_64 *sym_tab, struct section_64 **sec_tab);
void				print_name(t_nm nm, char *name);
int					scmp(const char *s1, const char *s2);
int					sncmp(const char *s1, const char *s2, size_t size);
void				*ft_memcpy(void *dst, const void *src, size_t n);

#endif
