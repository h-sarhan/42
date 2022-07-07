# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/25 20:40:06 by hsarhan           #+#    #+#              #
#    Updated: 2022/07/07 20:57:09 by hsarhan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# CFLAGS = -Wall -Wextra -Ofast -g3 -fsanitize=address,undefined -fno-omit-frame-pointer -fno-optimize-sibling-calls
CFLAGS = -Wall -Wextra -Ofast -g3
CC = cc

NAME = mlx/fdf
LIBFT = libft.a
PRINTF = libftprintf.a
GNL = libgnl.a

# TODO: REMOVE WILDCARDS LATER
SRCS = fdf.c draw_line.c hextoi.c colors.c read_ppm.c error_handling.c map.c
LIBFT_SRCS := $(wildcard libft/*.c)
PRINTF_SRCS := $(wildcard printf/*.c)
GNL_SRCS := $(wildcard get_next_line/*.c)

OBJS := $(SRCS:%.c=%.o)
LIBFT_OBJS := $(LIBFT_SRCS:%.c=%.o)
PRINTF_OBJS := $(PRINTF_SRCS:%.c=%.o)
GNL_OBJS := $(GNL_SRCS:%.c=%.o)
MLX = mlx/libmlx.dylib

all: $(NAME)

$(NAME): $(MLX) $(GNL) $(LIBFT) $(PRINTF) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(GNL) $(LIBFT) $(PRINTF) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $@

$(LIBFT): $(LIBFT_OBJS)
	ar -rcs $@ $^


# TODO: REMOVE THIS BEFORE SUBMITTING
# upscale: $(MLX) $(GNL) $(LIBFT) $(PRINTF) upscale.o 
# 	$(CC) $(CFLAGS) upscale.o  $(GNL) $(LIBFT) $(PRINTF) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $@

$(PRINTF): $(PRINTF_OBJS)
	ar -rcs $@ $^

$(GNL): $(GNL_OBJS)
	ar -rcs $@ $^

$(MLX):
	make -C mlx

%.o: %.c
	$(CC) $(CFLAGS) -c -Imlx $< -o $@

norm:
	norminette $(LIBFT_SRCS) $(PRINTF_SRCS) $(GNL_SRCS) $(SRCS) libft/libft.h printf/ft_printf.h get_next_line/get_next_line.h

clean:
	rm -f $(OBJS) $(LIBFT_OBJS) $(PRINTF_OBJS) $(GNL_OBJS) $(LIBFT) $(PRINTF) $(GNL) upscale.o
	make -C mlx clean

fclean: clean
	rm -f $(NAME) upscale

re: fclean $(NAME)