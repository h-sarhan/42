# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hsarhan <hassanAsarhan@outlook.com>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/29 21:51:32 by hsarhan           #+#    #+#              #
#    Updated: 2022/05/20 20:24:41 by hsarhan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = count_digits.c ft_printf.c conversions.c

OBJS := $(SRCS:%.c=%.o)

NAME = libftprintf.a
MUSTAFA_FLAGS = -Werror -Wall -Wextra
LIBFT = libft/libft.a

all: $(NAME)

$(NAME): $(OBJS)
	ar -rc $(NAME) $(OBJS)
	ranlib $(NAME)

$(LIBFT):
	make -s -C libft libft.a

%.o: %.c
	cc $(MUSTAFA_FLAGS) -c $^ 

norm:
	norminette

clean:
	rm -f $(OBJS)
	make -s -C libft clean

test: $(LIBFT) $(NAME)
	cc -Wextra -Wall tests.c $(LIBFT) $(NAME) -o tests
	./tests real > expected_out
	./tests mine > my_out
	diff expected_out my_out

fclean: clean
	rm -f $(NAME) expected_out my_out
	make -s -C libft fclean 

re: fclean $(NAME)
	
