# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/15 13:49:07 by hsarhan           #+#    #+#              #
#    Updated: 2022/06/17 18:29:57 by hsarhan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT_SRCS =	ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c \
				ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c \
				ft_itoa.c ft_lstadd_back_bonus.c ft_lstadd_front_bonus.c ft_lstclear_bonus.c \
				ft_lstdelone_bonus.c ft_lstiter_bonus.c ft_lstlast_bonus.c ft_lstmap_bonus.c \
				ft_lstnew_bonus.c ft_lstsize_bonus.c ft_memchr.c ft_memcmp.c \
				ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c \
				ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c \
				ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c \
				ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c \
				ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c \
				ft_substr.c ft_tolower.c ft_toupper.c
				
LIBFT_SRCS := $(addprefix libft/, $(LIBFT_SRCS))

PRINTF_SRCS =  conversion.c count_digits.c ft_printf.c \
				print_num_conversions.c print_numeric.c print_str_conversions.c \
				print_utils.c
				
PRINTF_SRCS := $(addprefix printf/, $(PRINTF_SRCS))

SRCS = pipex.c utils.c error_handling.c

LIBFT_OBJS := $(LIBFT_SRCS:%.c=%.o)
PRINTF_OBJS := $(PRINTF_SRCS:%.c=%.o)
OBJS := $(SRCS:%.c=%.o)

LIBFT = libft.a
PRINTF = libftprintf.a

CC = gcc

# TODO: Remove this before submitting
CFLAGS = -Werror -Wextra -Wall -g3
# CFLAGS = -Werror -Wextra -Wall 
NAME = pipex

all: $(NAME)

$(NAME): $(OBJS) $(PRINTF) $(LIBFT)
	$(CC) $(CFLAGS) $^ -o $@

$(PRINTF): $(PRINTF_OBJS)
	@ar -rc $(PRINTF) $(PRINTF_OBJS)

$(LIBFT): $(LIBFT_OBJS)
	@ar -rc $(LIBFT) $(LIBFT_OBJS)

%.o : %.c
	$(CC) $(CFLAGS) -c $^ -o $@

norm:
	norminette $(SRCS) $(LIBFT_SRCS) $(PRINTF_SRCS)

clean:
	@rm -f $(OBJS) $(LIBFT_OBJS) $(PRINTF_OBJS)

fclean: clean
	@rm -f $(NAME) $(LIBFT) $(PRINTF)
	
re: fclean $(NAME)
