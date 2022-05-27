# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hsarhan <hassanAsarhan@outlook.com>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/29 21:51:32 by hsarhan           #+#    #+#              #
#    Updated: 2022/05/26 18:48:09 by hsarhan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = conversion.c print_str_conversions.c \
	   print_num_conversions.c count_digits.c ft_printf.c \
	   print_utils.c print_hex.c

OBJS := $(SRCS:%.c=%.o)

NAME = libftprintf.a
MUSTAFA_FLAGS = -Werror -Wall -Wextra
LIBFT = libft/libft.a
LIBFT_SRCS = ft_strchr.c ft_split.c ft_strtrim.c ft_bzero.c ft_strnstr.c ft_strmapi.c ft_isprint.c ft_atoi.c ft_strdup.c \
			   ft_tolower.c ft_toupper.c ft_substr.c ft_striteri.c ft_memchr.c ft_putnbr_fd.c ft_strlcpy.c ft_itoa.c \
			   ft_memset.c ft_calloc.c ft_strlen.c ft_putchar_fd.c ft_isascii.c ft_strlcat.c ft_putendl_fd.c ft_memcmp.c \
			   ft_isdigit.c ft_strrchr.c ft_putstr_fd.c ft_isalpha.c ft_strncmp.c ft_isalnum.c ft_memcpy.c ft_memmove.c \
			   ft_strjoin.c
LIBFT_SRCS := $(addprefix libft/, $(LIBFT_SRCS))

LIBFT_OBJS := $(LIBFT_SRCS:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	ar -rc $(NAME) $(OBJS) $(LIBFT_OBJS)
	ranlib $(NAME)

$(LIBFT):
	make -s -C libft libft.a

%.o: %.c
	cc $(MUSTAFA_FLAGS) -c $^ -o $@

norm:
	norminette $(SRCS)

bonus: $(NAME)

clean:
	rm -f $(OBJS)
	make -s -C libft clean

test: $(LIBFT_OBJS) $(NAME)
	cc -Wextra -Wall tests.c $(LIBFT_OBJS) $(NAME) -o tests
	bash shell_tests.sh

fclean: clean
	rm -f $(NAME) expected actual tests
	make -s -C libft fclean 

re: fclean $(NAME)
	
