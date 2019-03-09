.PHONY: all clean fclean name re

NAME= ft_nm

OTOOL= ft_otool

CC= gcc

CFLAGS= -Wall -Wextra -Werror

NM_PATH= srcs/nm_srcs/

OTL_PATH= srcs/otool_srcs/

HPATH= inc/

NM_OPATH= nm_objs/

OTL_OPATH= otool_objs/

HFILES= inc/ft_nm.h \
		inc/ft_otool.h \
		lib/includes/libftprintf.h

INC= $(addprefix -I , $(HPATH))

L= lib/libftprintf.a

NM_FILES= main_nm.c \
		  little_endian_32_nm.c \
		  little_endian_64_nm.c \
		  big_endian_32_nm.c \
		  big_endian_64_nm.c \
		  fat_nm.c \
		  archive_nm.c \
		  additionnal_nm.c \
		  additionnal_little_nm.c \
		  additionnal_big_nm.c \
		  common_tools_nm.c \
		  swap_nm.c

OTL_FILES= main_otool.c \
		   little_endian_32_otool.c \
		   little_endian_64_otool.c \
		   big_endian_32_otool.c \
		   big_endian_64_otool.c \
		   fat_otool.c \
		   archive_otool.c \
		   additionnal_otool.c \
		   additionnal_little_otool.c \
		   additionnal_big_otool.c \
		   common_tools_otool.c

NM_COBJ= $(addprefix $(NM_OPATH), $(NM_OFILES))

OTL_COBJ= $(addprefix $(OTL_OPATH), $(OTL_OFILES))

NM_OFILES= $(NM_FILES:.c=.o)

OTL_OFILES= $(OTL_FILES:.c=.o)

all: PRINTF $(NAME) $(OTOOL)

PRINTF:
	make -C lib
	mkdir -p $(NM_OPATH)
	mkdir -p $(OTL_OPATH)

$(NAME): $(NM_COBJ)
	$(CC) $(CFLAGS) $(L) $(NM_COBJ) $(INC) -o $(NAME)

$(OTOOL): $(OTL_COBJ)
	$(CC) $(CFLAGS) $(L) $(OTL_COBJ) $(INC) -o $(OTOOL)

$(NM_OPATH)%.o: $(NM_PATH)%.c $(HFILES)
	$(CC) $(CFLAGS) $(INC) $< -c -o $@

$(OTL_OPATH)%.o: $(OTL_PATH)%.c $(HFILES)
	$(CC) $(CFLAGS) $(INC) $< -c -o $@

clean:
	$(MAKE) -C lib/ clean
	rm -rf $(NM_OPATH) $(OTL_OPATH)

fclean: clean
	$(MAKE) -C lib/ fclean
	rm -rf $(NM_OPATH) $(OTL_OPATH)
	rm -rf $(NAME)
	rm -rf $(OTOOL)

re: fclean all
