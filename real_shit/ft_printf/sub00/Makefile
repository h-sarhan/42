# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hsarhan <hassanAsarhan@outlook.com>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/29 21:51:32 by hsarhan           #+#    #+#              #
#    Updated: 2022/05/26 16:20:16 by hsarhan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = conversions/conversion.c conversions/print_str_conversions.c \
	   conversions/print_num_conversions.c count_digits.c ft_printf.c \
	   print_utils.c print_hex.c

OBJS := $(SRCS:%.c=%.o)

NAME = libftprintf.a
MUSTAFA_FLAGS = -Werror -Wall -Wextra
LIBFT = libft/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	ar -rc $(NAME) $(OBJS)
	ranlib $(NAME)

$(LIBFT):
	make -s -C libft libft.a

%.o: %.c
	cc $(MUSTAFA_FLAGS) -c $^ -o $@

norm:
	norminette $(SRCS)

clean:
	rm -f $(OBJS)
	make -s -C libft clean

test: $(LIBFT) $(NAME)
	cc -Wextra -Wall tests.c $(LIBFT) $(NAME) -o tests
#	./tests real > expected_out
#	./tests mine > my_out
#	diff expected_out my_out
#	./tests

fclean: clean
	rm -f $(NAME) expected_out my_out tests
	make -s -C libft fclean 

re: fclean $(NAME)
	
