# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/25 20:40:06 by hsarhan           #+#    #+#              #
#    Updated: 2022/07/08 20:32:39 by hsarhan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# CFLAGS = -Wall -Wextra -Ofast -g3 -fsanitize=address,undefined -fno-omit-frame-pointer -fno-optimize-sibling-calls
CFLAGS = -Wall -Wextra -O3
CC = cc

NAME = fdf
LIBFT = libft.a
PRINTF = libftprintf.a
GNL = libgnl.a

# TODO: REMOVE WILDCARDS LATER
SRCS = fdf.c draw_line.c hextoi.c colors.c read_ppm.c error_handling.c map.c colors2.c rotation.c projection.c window_management.c keyboard_input.c
LIBFT_SRCS := $(wildcard libft/*.c)
PRINTF_SRCS := $(wildcard printf/*.c)
GNL_SRCS := $(wildcard get_next_line/*.c)

OBJS := $(SRCS:%.c=%.o)
LIBFT_OBJS := $(LIBFT_SRCS:%.c=%.o)
PRINTF_OBJS := $(PRINTF_SRCS:%.c=%.o)
GNL_OBJS := $(GNL_SRCS:%.c=%.o)
MLX = libmlx.dylib

all: $(NAME)

$(NAME): $(MLX) $(GNL) $(LIBFT) $(PRINTF) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(GNL) $(LIBFT) $(PRINTF) -L. -lmlx -framework OpenGL -framework AppKit -o $@

$(LIBFT): $(LIBFT_OBJS)
	ar -rcs $@ $^

$(PRINTF): $(PRINTF_OBJS)
	ar -rcs $@ $^

$(GNL): $(GNL_OBJS)
	ar -rcs $@ $^

$(MLX):
	make -C mlx
	mv ./mlx/libmlx.dylib .

%.o: %.c
	$(CC) $(CFLAGS) -c -Imlx $< -o $@

norm:
	norminette $(LIBFT_SRCS) $(PRINTF_SRCS) $(GNL_SRCS) $(SRCS) libft/libft.h printf/ft_printf.h get_next_line/get_next_line.h fdf.h

clean:
	rm -f $(OBJS) $(LIBFT_OBJS) $(PRINTF_OBJS) $(GNL_OBJS) $(LIBFT) $(PRINTF) $(GNL) upscale.o
	make -C mlx clean

fclean: clean
	rm -f $(NAME) upscale libmlx.dylib

re: fclean $(NAME)