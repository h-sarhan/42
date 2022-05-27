# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/29 21:51:32 by hsarhan           #+#    #+#              #
#    Updated: 2022/05/27 21:15:08 by hsarhan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = conversion.c print_str_conversions.c \
	   print_num_conversions.c count_digits.c ft_printf.c \
	   print_utils.c print_numeric.c

OBJS := $(SRCS:%.c=%.o)

NAME = libftprintf.a
MUSTAFA_FLAGS = -Werror -Wall -Wextra
LIBFT_SRCS = ft_strchr.c ft_substr.c ft_putchar_fd.c ft_strlen.c ft_isdigit.c \
			 ft_atoi.c ft_putnbr_fd.c ft_putstr_fd.c ft_strlcpy.c ft_strncmp.c

LIBFT_SRCS := $(addprefix libft_funcs/, $(LIBFT_SRCS))

LIBFT_OBJS := $(LIBFT_SRCS:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_OBJS)
	ar -rc $(NAME) $(OBJS) $(LIBFT_OBJS)
	ranlib $(NAME)

%.o: %.c
	cc $(MUSTAFA_FLAGS) -c $^ -o $@

norm:
	norminette $(SRCS) ft_printf.h $(LIBFT_SRCS)

bonus: $(NAME)

clean:
	rm -f $(OBJS) $(LIBFT_OBJS)

fclean: clean
	rm -f $(NAME) expected actual tests

re: fclean $(NAME)
	
