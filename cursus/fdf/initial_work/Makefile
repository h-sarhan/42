# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/25 20:40:06 by hsarhan           #+#    #+#              #
#    Updated: 2022/06/25 21:01:16 by hsarhan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Werror -Wextra -g3
CC = gcc

NAME = fdf
LIBFT = libft.a
PRINTF = libftprintf.a
GNL = libgnl.a

# TODO: REMOVE WILDCARDS LATER
SRCS = read_map.c
LIBFT_SRCS := $(wildcard libft/*.c)
PRINTF_SRCS := $(wildcard printf/*.c)
GNL_SRCS := $(wildcard get_next_line/*.c)

OBJS := $(SRCS:%.c=%.o)
LIBFT_OBJS := $(LIBFT_SRCS:%.c=%.o)
PRINTF_OBJS := $(PRINTF_SRCS:%.c=%.o)
GNL_OBJS := $(GNL_SRCS:%.c=%.o)


all: $(NAME)

$(NAME):  $(OBJS)  $(PRINTF) $(GNL) $(LIBFT)
	$(CC) $(CFLAGS) $^ -o $@

$(LIBFT): $(LIBFT_OBJS)
	ar -rcs $@ $^

$(PRINTF): $(PRINTF_OBJS)
	ar -rcs $@ $^

$(GNL): $(GNL_OBJS)
	ar -rcs $@ $^

norm:
	norminette $(LIBFT_SRCS) $(PRINTF_SRCS) $(GNL_SRCS) $(SRCS) libft/libft.h printf/ft_printf.h get_next_line/get_next_line.h

clean:
	rm -f $(OBJS) $(LIBFT_OBJS) $(PRINTF_OBJS) $(GNL_OBJS) $(LIBFT) $(PRINTF) $(GNL)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)