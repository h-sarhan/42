# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/25 20:40:06 by hsarhan           #+#    #+#              #
#    Updated: 2022/06/27 15:51:05 by hsarhan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Wextra -g3
CC = gcc

NAME = fdf
LIBFT = libft.a
PRINTF = libftprintf.a
GNL = libgnl.a
MLX = mlx_linux/libmlx_Linux.a

# TODO: REMOVE WILDCARDS LATER
SRCS = read_map.c
LIBFT_SRCS := $(wildcard libft/*.c)
PRINTF_SRCS := $(wildcard printf/*.c)
GNL_SRCS := $(wildcard get_next_line/*.c)

OBJS := $(SRCS:%.c=%.o)
LIBFT_OBJS := $(LIBFT_SRCS:%.c=%.o)
PRINTF_OBJS := $(PRINTF_SRCS:%.c=%.o)
GNL_OBJS := $(GNL_SRCS:%.c=%.o)
MLX_FLAGS = -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
all: $(NAME)

$(NAME): $(OBJS)  $(GNL) $(PRINTF)  $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJS) $(GNL) $(PRINTF) $(LIBFT) $(MLX_FLAGS) -o $@

$(LIBFT): $(LIBFT_OBJS)
	ar -rcs $@ $^

$(PRINTF): $(PRINTF_OBJS)
	ar -rcs $@ $^

$(GNL): $(GNL_OBJS)
	ar -rcs $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -I/usr/include -Imlx_linux -O3 -c $< -o $@

$(MLX):
	make -C mlx_linux

norm:
	norminette $(LIBFT_SRCS) $(PRINTF_SRCS) $(GNL_SRCS) $(SRCS) libft/libft.h printf/ft_printf.h get_next_line/get_next_line.h

clean:
	rm -f $(OBJS) $(LIBFT_OBJS) $(PRINTF_OBJS) $(GNL_OBJS) $(LIBFT) $(PRINTF) $(GNL)
	make -C mlx_linux clean

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)
