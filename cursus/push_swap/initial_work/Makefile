# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/25 20:40:06 by hsarhan           #+#    #+#              #
#    Updated: 2022/07/14 05:49:22 by hsarhan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Wextra
CC = cc

NAME = push_swap
LIBFT = libft.a
PRINTF = libftprintf.a

SRCS =	doubly_linked_list/dll.c doubly_linked_list/dll2.c doubly_linked_list/dll3.c \
		stack/swap.c stack/push.c

LIBFT_SRCS = ft_strchr.c ft_split.c ft_strtrim.c ft_bzero.c ft_strnstr.c ft_strmapi.c ft_isprint.c ft_atoi.c ft_strdup.c \
			ft_tolower.c ft_toupper.c ft_substr.c ft_striteri.c ft_memchr.c ft_putnbr_fd.c ft_strlcpy.c ft_itoa.c \
			ft_memset.c ft_calloc.c ft_strlen.c ft_putchar_fd.c ft_isascii.c ft_strlcat.c ft_putendl_fd.c ft_memcmp.c \
			ft_isdigit.c ft_strrchr.c ft_putstr_fd.c ft_isalpha.c ft_strncmp.c ft_isalnum.c ft_memcpy.c ft_memmove.c \
			ft_strjoin.c ft_lstadd_front_bonus.c ft_lstmap_bonus.c ft_lstnew_bonus.c ft_lstclear_bonus.c \
			ft_lstadd_back_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c ft_lstdelone_bonus.c \
			ft_lstiter_bonus.c
LIBFT_SRCS := $(addprefix libft/, $(LIBFT_SRCS))		   

PRINTF_SRCS = conversion.c print_str_conversions.c \
			print_num_conversions.c count_digits.c ft_printf.c \
			print_utils.c print_numeric.c
PRINTF_SRCS := $(addprefix printf/, $(PRINTF_SRCS))		   

OBJS := $(SRCS:%.c=%.o)
LIBFT_OBJS := $(LIBFT_SRCS:%.c=%.o)
PRINTF_OBJS := $(PRINTF_SRCS:%.c=%.o)

all: $(NAME)

$(NAME): $(LIBFT) $(PRINTF) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS)  $(LIBFT) $(PRINTF) -o $@

$(LIBFT): $(LIBFT_OBJS)
	ar -rcs $@ $^

$(PRINTF): $(PRINTF_OBJS)
	ar -rcs $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

norm:
	norminette $(LIBFT_SRCS) $(PRINTF_SRCS) $(SRCS) libft/libft.h printf/ft_printf.h push_swap.h

clean:
	rm -f $(OBJS) $(LIBFT_OBJS) $(PRINTF_OBJS) $(LIBFT) $(PRINTF)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)