# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/15 13:49:07 by hsarhan           #+#    #+#              #
#    Updated: 2022/06/16 11:00:53 by hsarhan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT_SRCS := $(wildcard libft/*.c)
PRINTF_SRCS := $(wildcard printf/*.c)
SRCS = pipex.c utils.c

LIBFT_OBJS := $(LIBFT_SRCS:%.c=%.o)
PRINTF_OBJS := $(PRINTF_SRCS:%.c=%.o)
OBJS := $(SRCS:%.c=%.o)

CC = gcc
# CFLAGS = -Werror -Wextra -Wall
CFLAGS = -g3
NAME = pipex

all: $(NAME)

$(NAME):  $(PRINTF_OBJS) $(LIBFT_OBJS) $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

%.o : %.c
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm -f $(OBJS) $(LIBFT_OBJS) $(PRINTF_OBJS)

fclean: clean
	rm -f $(NAME)
	
re: fclean $(NAME)
