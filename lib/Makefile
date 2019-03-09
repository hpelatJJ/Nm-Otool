# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hpelat <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/25 15:46:03 by hpelat            #+#    #+#              #
#    Updated: 2017/02/07 11:28:18 by hpelat           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang
CFLAGS = -Wall -Wextra -Werror
ADDFLAG = -fsanitize=address


INCDIR = includes

NAME = libftprintf.a

SRC = srcs/ft_printf.c \
	  srcs/fd_printf.c \
	  srcs/ft_direct.c \
	  srcs/ft_whichconv.c \
	  srcs/ft_findc.c \
	  srcs/ft_conv_s.c \
	  srcs/ft_conv_ls.c \
	  srcs/ft_conv_p.c \
	  srcs/ft_conv_d.c \
	  srcs/ft_conv_o.c \
	  srcs/ft_conv_u.c \
	  srcs/ft_conv_x.c \
	  srcs/ft_conv_c.c \
	  srcs/ft_conv_lc.c \
	  srcs/ft_conv_b.c \
	  srcs/ft_conv_n.c \
	  srcs/ft_conv_r.c \
	  srcs/ft_color.c \
	  srcs/ft_reset.c \
	  srcs/ft_buffill.c \
	  srcs/ft_atoi.c \
	  srcs/ft_strlen.c \
	  srcs/ft_wstrlen.c \
	  srcs/ft_strchr.c \
	  srcs/ft_itoa_long_nm.c \
	  srcs/ft_itoa_ulong_nm.c \
	  srcs/ft_itoa_base_long_nm.c \
	  srcs/ft_itoa_base_ulong_nm.c \
	  srcs/ft_isdigit.c \
	  srcs/ft_mfw.c \
	  srcs/ft_do_mfw.c \
	  srcs/ft_precision.c \
	  srcs/ft_do_prec.c \
	  srcs/ft_order_p.c \
	  srcs/ft_order_d.c \
	  srcs/ft_order_o.c \
	  srcs/ft_order_u.c \
	  srcs/ft_order_x.c \
	  srcs/ft_order_b.c \
	  srcs/ft_plusminus.c \
	  srcs/ft_get_wchar.c \
	  srcs/ft_tmp_ls.c \
	  srcs/ft_space.c \
	  srcs/ft_maj.c


OBJ = $(SRC:.c=.o)


%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $^ -I$(INCDIR)

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

clean:
	@/bin/rm -f $(OBJ)
	@/bin/rm -f ./*.o

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all

dae: re
	@/bin/rm -f $(OBJ)
