# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hsarhan <hassanAsarhan@outlook.com>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/29 21:51:32 by hsarhan           #+#    #+#              #
#    Updated: 2022/05/19 15:20:46 by hsarhan          ###   ########.fr        #
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
	gcc $(MUSTAFA_FLAGS) tests.c $(LIBFT) $(NAME) -o tests
	./tests real > real
	./tests mine > mine
	diff real mine

fclean: clean
	rm -f $(NAME)
	make -s -C libft fclean

re: fclean $(NAME)
	
